#ifndef GST_PIPE_HPP
#define GST_PIPE_HPP
#include <iostream>
#include <memory>
#include <chrono>

#include <gst/gst.h>
#include <gst/app/app.h>
#include <opencv2/opencv.hpp>

#include "bufmanager.hpp"
#include "publicattr.h"

namespace gstpipe{

class GstPipe : public VideoAttr{
public :
    GstPipe(){}
    ~GstPipe(){}

    void Init() {
        this->setIndex(0);
        this->pipeline = gst_pipeline_new (this->getPipeName().c_str());

        frame_cache = std::make_shared<BufManager<GstSample> > ();
        error = NULL;
        if(this->pipe_name.empty()) {
            setPipeName("qmmf");
        }
        if(this->sink_name.empty()) {
            setSinkName("app_sink");
        }

        if(GstType::LOCAL == this->gst_type) {
            createPipeLine();
        } else if (GstType::CAMERA == this->gst_type) {
            createPipeLine();
        } else if (GstType::RTSP == this->gst_type) {
            createPipeLine();
        }
    }
    void runGst() {
        this->launchPipeLine(this->pipeline_str);

        this->handleAppsink();

        /* Run the pipeline for Start playing */
        if (GST_STATE_CHANGE_FAILURE == gst_element_set_state (this->pipeline, GST_STATE_PLAYING)) {
            g_printerr ("Unable to set the pipeline to the playing state.\n");
        }
        //clear pipeline buffer

        /* Putting a Message handler */
        this->gstbus = gst_pipeline_get_bus (GST_PIPELINE (this->pipeline));
        gst_bus_add_watch (this->gstbus, pipeBusCallback, reinterpret_cast<void *>(this));
        gst_object_unref (this->gstbus);

    }

    GstStateChangeReturn setPipeState(GstState _state);
    std::shared_ptr<GstSample> getGstSample(std::shared_ptr<GstSample>& dst);
    virtual void createPipeLine() = 0;
    virtual cv::Mat getFrameData(void* _pipe) = 0;

    void setPipeStr(string _str) {
        this->pipeline_str = _str;
    }

    string getPipeStr() {
        return this->pipeline_str;
    }

    void setPipeName(string _name) {
        this->pipe_name = _name;
    }
    string getPipeName(){
        return this->pipe_name;
    }

    void setSinkName(string _name) {
        this->sink_name = _name;
    }
    string getSinkName(){
        return this->sink_name;
    }

    void setGstType(GstType _type) {
        this->gst_type = _type;
    }
    GstType getGstType() {
        return this->gst_type;
    }

    void setHwDec(bool _hw) {
        this->hw_dec = _hw;
    }
    bool isHwDec() {
        return this->hw_dec;
    }

    void setNeedCalib(bool _need){
        this->need_calibration = _need;
    }
    bool getNeedCalib(){
        return this->need_calibration;
    }

protected :
    bool launchPipeLine(string _pipeline_str);
    void handleAppsink();
    
    static void onEOS(GstAppSink *appsink, void *user_data);
    static GstFlowReturn onPreroll(GstAppSink *appsink, void *user_data);
    static GstFlowReturn onBuffer(GstAppSink *appsink, void *user_data);
    static gboolean pipeBusCallback (GstBus *bus, GstMessage *message, gpointer data);

private :
    string pipeline_str;
    string pipe_name;
    string sink_name;
    GstType gst_type;
    bool hw_dec;
    bool need_calibration;

    GstElement *pipeline,*appsink;
    GstBus *gstbus;
    GError *error;

    static std::chrono::system_clock::time_point start_time; 

    std::shared_ptr<gstpipe::BufManager<GstSample> > frame_cache;

};

std::chrono::system_clock::time_point GstPipe::start_time = std::chrono::system_clock::now(); 

void GstPipe::handleAppsink()
{
    /* get sink */
    this->appsink = gst_bin_get_by_name (GST_BIN (this->pipeline), this->getSinkName().c_str());
    std::cout << "appsink name = " << gst_object_get_name(GST_OBJECT(this->appsink)) << std::endl;

    /*set sink prop*/
    gst_app_sink_set_emit_signals((GstAppSink*)this->appsink, true);
    gst_app_sink_set_drop((GstAppSink*)this->appsink, true);
    gst_app_sink_set_max_buffers((GstAppSink*)this->appsink, 1);
    gst_base_sink_set_sync(GST_BASE_SINK(this->appsink),false);
    gst_base_sink_set_last_sample_enabled(GST_BASE_SINK(this->appsink), true);
    //gst_base_sink_set_drop_out_of_segment(GST_BASE_SINK(this->appsink), true);
    gst_base_sink_set_max_lateness(GST_BASE_SINK(this->appsink), 0);

    {//avoid goto check
        GstAppSinkCallbacks callbacks = { onEOS, onPreroll, onBuffer };
        gst_app_sink_set_callbacks (GST_APP_SINK(this->appsink), &callbacks, reinterpret_cast<void *>(this), NULL);
    }
}

bool GstPipe::launchPipeLine(string _pipeline_str)
{
    this->pipeline = gst_parse_launch(_pipeline_str.c_str(),&this->error);
    if (this->error != NULL) {
        printf ("could not construct pipeline: %s\n", error->message);
        g_clear_error (&error);
        goto exit;
    }
    return true;
exit:
    if(this->pipeline != NULL) {
        gst_element_set_state (this->pipeline, GST_STATE_NULL);
        gst_object_unref (this->pipeline);
        this->pipeline = NULL;
    }
    return false;
}

// onEOS
void GstPipe::onEOS(GstAppSink *appsink, void *user_data)
{
    // GstPipe *dec = reinterpret_cast<GstPipe *>(user_data);
    printf("gstreamer decoder onEOS\n");
}

// onPreroll
GstFlowReturn GstPipe::onPreroll(GstAppSink *appsink, void *user_data)
{
    printf("gstreamer decoder onPreroll\n");
    return GST_FLOW_OK;
}

static void deleterGstSample(GstSample* x) {
    //std::cout << "DELETER FUNCTION CALLED\n";
    if(x != NULL) {
        gst_sample_unref (x);
    }
}

// onBuffer
GstFlowReturn GstPipe::onBuffer(GstAppSink *appsink, void *user_data)
{
    GstPipe *dec = NULL;
    dec = reinterpret_cast<GstPipe *>(user_data);
    if(dec == NULL || appsink == NULL) {
        printf ("decode or appsink is null\n");
        return GST_FLOW_ERROR;
    }

    if(!dec->getIndex()) {
       start_time = std::chrono::system_clock::now();
    }

    GstSample* sample = gst_app_sink_pull_sample(appsink);
	// sample = gst_base_sink_get_last_sample(GST_BASE_SINK(appsink));
    if(sample == NULL) {
        printf ("pull sample is null\n");
        return GST_FLOW_ERROR;
    } else {
        dec->frame_cache->feed(std::shared_ptr<GstSample>(sample, deleterGstSample));
        dec->setIndex(dec->getIndex()+1);
    }

    return GST_FLOW_OK;
}

gboolean GstPipe::pipeBusCallback (GstBus *bus, GstMessage *message, gpointer data) 
{
    GstPipe *gst_camera = reinterpret_cast<GstPipe *>(data);
    switch (GST_MESSAGE_TYPE (message)) {
    case GST_MESSAGE_ERROR: {
        GError *err;
        gchar *debug;

        gst_message_parse_error (message, &err, &debug);
        g_print ("Error: %s\n", err->message);
        g_error_free (err);
        g_free (debug);

        gst_element_set_state(gst_camera->pipeline,GST_STATE_READY);
        break;
    }
    case GST_MESSAGE_EOS:
        /* end-of-stream */
        gst_element_set_state(gst_camera->pipeline,GST_STATE_NULL);
        break;
    default:
      /* unhandled message */
        break;
    }
    /* we want to be notified again the next time there is a message
    * on the bus, so returning TRUE (FALSE means we want to stop watching
    * for messages on the bus and our callback should not be called again)
    */
    return TRUE;
}

GstStateChangeReturn GstPipe::setPipeState(GstState _state)
{
    GstStateChangeReturn ret =  gst_element_set_state(this->pipeline, _state);
    if (GST_STATE_CHANGE_FAILURE == ret) {
        return ret;
    }

    return GstStateChangeReturn::GST_STATE_CHANGE_SUCCESS;
}

std::shared_ptr<GstSample> GstPipe::getGstSample(std::shared_ptr<GstSample>& dst)
{
    return (dst = frame_cache->fetch());
}

} // namespace gstpipe

#endif