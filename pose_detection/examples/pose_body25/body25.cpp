#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <thread>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/text_format.h>

#include "param_parse.hpp"

#include "gst_pipe/gstpipe.hpp"
#include "gst_pipe/gstpipefactory.hpp"
#include "pb_conf/gstreamer.pb.h"

#include "boadypacket.hpp"

#include "inference/snpe/RunSnpe/inference.hpp"

using namespace std;
using namespace gstpipe;
using namespace body;
using namespace inference;

using google::protobuf::io::FileInputStream;
using google::protobuf::io::FileOutputStream;
using google::protobuf::io::ZeroCopyInputStream;
using google::protobuf::io::CodedInputStream;
using google::protobuf::io::ZeroCopyOutputStream;
using google::protobuf::io::CodedOutputStream;
using google::protobuf::Message;

std::vector<gstpipe::GstPipe*> gst_pipe_vec;
inference::snpe::Inference *snpe_inference;
std::queue<body::BodyPacket<float>> body_packet_que;

void getDataFromSample() 
{
    std::cout << "enter get data from sample thread........" << std::endl; 
    for(;;) {
        if(gst_pipe_vec.empty()) {
            continue;
        }
        for(auto _pipe : gst_pipe_vec) {
            GstPipe* gst_pipe = _pipe;

            body::BodyPacket<float> body_packet;
            std::cout << "test getFrameData ..." << std::endl;
            cv::Mat tmp_mat = gst_pipe->getFrameData(gst_pipe);
            if(tmp_mat.empty()) {
                std::cout << "the mat is empty from getFrameData ..." << std::endl;
                continue;
            } else {
                std::cout << "Frame is valid from sample,will be fill to body packet queue" << std::endl;
                body_packet.setMat(std::make_shared<cv::Mat>(tmp_mat));
                body_packet_que.push(body_packet);
            }
        }
    }
}

void bodyInference()
{
    std::cout << "enter body inference thread........" << std::endl; 
    for(;;) {
        if(snpe_inference == nullptr) {
            continue;
        }
        if(body_packet_que.empty()) {
            continue;
        }

        for(;!body_packet_que.empty();) {
            cv::Mat src_mat = body_packet_que.front().getSrcMat();
            std::vector<float> snpe_result_vec = snpe_inference->doInference<float>(src_mat);
            body_packet_que.front().getValidResult(snpe_result_vec);
        }
    }
}

void preview(std::shared_ptr<cv::Mat> imgframe)
{
    cv::Mat showframe;
#if 1 
    cv::resize(*imgframe, showframe, cv::Size(1920,1080), 0, 0, cv::INTER_LINEAR);
    cv::imshow("sink", showframe);
    cv::waitKey(1);
#endif
    return ;
}

#define SSTR( x ) static_cast< std::ostringstream & >( \
( std::ostringstream() << std::dec << x ) ).str()

template <class T>
static void output_show(int _sub_num,cv::Size_<T> _sub_size)
{
    // Multichannel display block diagram segmentation calculation
    int num_w = sqrt(_sub_num);
    num_w = num_w + (pow(num_w, 2) < _sub_num ? 1 : 0);
    int num_h = _sub_num/num_w + (_sub_num%num_w > 0 ? 1 :0);
    cout << "nuw_w = " << num_w << ",num_h =" << num_h << endl;

    int width = _sub_size.width;
    int height = _sub_size.height;
    int show_left,show_top;

    for(;;) {
        if(gst_pipe_vec.empty()) {
            continue;
        }
        if(body_packet_que.empty()) {
            continue;
        } 

        if(body_packet_que.front().getInfState() == false) {
            continue;
        }
        std::cout << "Mat has been Inference from body packet" << std::endl;
        
        std::shared_ptr<cv::Mat> img_show_ptr;
        std::shared_ptr<cv::Mat> sub_imgframe_ptr;
        cv::Mat image_show(cv::Size(width*num_w, height*num_h), CV_8UC4);

        for(int i = 0; i < _sub_num; i++) {
            show_left = i % num_w * (width);
            show_top = i / num_w * (height);
            sub_imgframe_ptr = body_packet_que.front().getResultMat();
            sub_imgframe_ptr.get()->copyTo(image_show(cv::Rect(show_left,show_top,width,height)));
        }
        body_packet_que.pop();
        preview(std::make_shared<cv::Mat> (image_show));
    }
}

// Main function:  Reads the entire address book from a file and prints all
//   the information inside.
int main(int argc, char* argv[])
{
    // MulitGstCamera::GstEnvInit();
    gst_init (NULL, NULL);
    GMainLoop *main_loop = g_main_loop_new(NULL,false);

    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    parse::Parse parma_set = parse::parseArgs(argc,argv);

    if(parma_set.be_fill == false) {
        std::cout << "don`t parse required parma" << std::endl;
        parse::printHelp();
        return -1;
    }

    gstcfg::DataSourceSet data_source_set;

    {
        // Read the existing address book.
        int fd = open(parma_set.config_file.c_str(), O_RDONLY);
        FileInputStream* input = new FileInputStream(fd);
        if (!google::protobuf::TextFormat::Parse(input, &data_source_set)) {
        cerr << "Failed to parse gstreamer data source." << endl;
        delete input;
        close(fd);
        return -1;
        }
    }

    int stream_count = data_source_set.data_source_size();
    gstpipe::GstPipeFactory* pipe_factory = gstpipe::GstPipeFactory::getInstance();
    for (int i = 0; i < stream_count; i++) {
        const gstcfg::DataSource& data_source = data_source_set.data_source(i);
        gstpipe::GstType gsttype = (gstpipe::GstType)data_source.gst_type();
        gstpipe::GstPipe* gst_pipe;
        switch (gsttype) {
            case gstpipe::GstType::LOCAL:
                gst_pipe = pipe_factory->createPipeLine(gsttype);
                break;
            case gstpipe::GstType::CAMERA:
                gst_pipe = pipe_factory->createPipeLine(gsttype);
                break;
            case gstpipe::GstType::RTSP:
                gst_pipe = pipe_factory->createPipeLine(gsttype);
                break;
            default:
                break;
        }

        gst_pipe->setPipeName(data_source.gst_name());
        gst_pipe->setSinkName(data_source.sink_name());
        gst_pipe->setGstType((GstType)data_source.gst_type());
        gst_pipe->setWidth(data_source.data_info().width());
        gst_pipe->setHeight(data_source.data_info().height());
        gst_pipe->setDecodeType(data_source.data_info().decode());
        gst_pipe->setFormat(data_source.data_info().format());
        gst_pipe->setFramerate(data_source.data_info().framerate());
        gst_pipe->setPath(data_source.gst_path());
        gst_pipe->setNeedCalib(data_source.neeed_calib());
        gst_pipe->setHwDec(data_source.enable_ai());

        gst_pipe_vec.emplace_back(gst_pipe);
    }

    for(auto gst_pipe : gst_pipe_vec) {
        gst_pipe->Init();
        std::thread gst_thread([=]{
            gst_pipe->runGst();
        });
        gst_thread.join();
    }

    std::cout << "Runing gstreamer pipe ......" << std::endl;
    std:;cout << "Starting snpe runtime,model file : " << parma_set.model_file << std::endl;

    snpe_inference = new inference::snpe::Inference(parma_set.model_file,inference::snpe::runtime_t::GPU,
                                        inference::snpe::DataFormat::NHWC);
    snpe_inference->Init(inference::snpe::runtime_t::GPU);

    std::cout << "Snpe init runtime env finished ......" << std::endl;

    std::thread getDataThread(getDataFromSample);
    getDataThread.detach();

    std::thread snpeInferenceThread(bodyInference);
    snpeInferenceThread.detach();

    std::thread showThread(output_show<int>,stream_count,cv::Size2i(640,480));
    showThread.detach();

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    g_main_loop_run(main_loop);
    g_main_loop_unref(main_loop);

    return 0;
}