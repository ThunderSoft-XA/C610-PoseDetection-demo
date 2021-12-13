#include <iostream>
#include <sstream>
#include "gstpipe.hpp"
#include <opencv2/opencv.hpp>

namespace gstpipe {

class GstLocal: public GstPipe
{
public:
    GstLocal(){}
    ~GstLocal();

    void createPipeLine();
    cv::Mat getFrameData(void* _pipe);
};

void GstLocal::createPipeLine()
{
    std::ostringstream cameraPath;
    cameraPath << "filesrc location=" << getPath() << " ! " << "qtdemux name=demux demux. ! queue ! h264parse ! ";
    if(isHwDec()) {
        //GstPipeline:pipeline0/GstOMXH264Dec-omxh264dec:omxh264dec-omxh264dec0: Could not initialize supporting library in 610
        cameraPath << "omx" << getDecodeType() << "dec " << " ! ";
    } else {
        cameraPath << "avdec_" << getDecodeType() << " ! ";
    }
    cameraPath << "videoscale ! video/x-raw,width=" << getWidth() << ",height=" << getHeight() << " ! appsink name=" << getSinkName() << " sync=false  max-lateness=0 max-buffers=1 drop=true";
    setPipeStr(cameraPath.str());
    std::cout << "local file Pipeline: " << getPipeStr() << std::endl;
}

cv::Mat GstLocal::getFrameData(void* _pipe)
{
    std::shared_ptr<GstSample> sample;
    GstPipe* pipe = reinterpret_cast<GstLocal*> (_pipe);

    pipe->getGstSample(sample);
    if(NULL == sample || NULL == sample.get()) {
        #ifdef DEBUG
                    std::cout << "the sample is null or invaild" << std::endl;
        #endif
        exit (-1);
    }

    GstCaps *sample_caps = gst_sample_get_caps(sample.get());
    if( sample_caps == NULL) {
        exit (-1);
    }
    gint sample_width,sample_height;

    GstStructure *structure = gst_caps_get_structure(sample_caps,0);
    gst_structure_get_int(structure,"width",&sample_width);
    gst_structure_get_int(structure,"height",&sample_height);

    GstBuffer *gst_buffer = gst_sample_get_buffer(sample.get());
    if (NULL == gst_buffer || !sample_width || !sample_height) {
        exit (-1);
    }
    cout <<"==sample width="<< sample_width <<",sample height = " << sample_height <<  endl;
    GstMapInfo sample_map;
    gst_buffer_map(gst_buffer,&sample_map,GST_MAP_READ);
    std::cout << "smaple map size: " << sample_map.size << std::endl;

    unsigned char *data_buffer = (unsigned char*)malloc(sizeof(unsigned char)*sample_map.size);
    cv::Mat sample_mat;
    if(data_buffer != nullptr) {
        memset(data_buffer,0x00, sample_map.size);
        memcpy(data_buffer, (guchar *)sample_map.data, sample_map.size);
        sample_mat = cv::Mat(sample_width, sample_height, CV_8UC3, data_buffer, 0);	
    }

    return sample_mat;
}


    
} // namespace gstpipe