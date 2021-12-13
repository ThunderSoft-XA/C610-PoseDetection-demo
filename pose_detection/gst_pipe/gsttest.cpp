#include <iostream>
#include <string>

#include "gstpipefactory.hpp"

std::chrono::system_clock::time_point gstpipe::GstPipe::start_time = std::chrono::system_clock::now();

int main(int argc, char **argv)
{
    gstpipe::GstType gsttype = gstpipe::GstType::RTSP;
    gstpipe::GstPipeFactory* pipe_factory = gstpipe::GstPipeFactory::getInstance();
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

    gst_pipe->Init();
    gst_pipe->runGst();

    return 0;
}