#ifndef GST_PIPE_FACTORY_HPP
#define GST_PIPE_FACTORY_HPP

#include <iostream>

#include "gstpipe.hpp"
#include "gstrtsp.hpp"
#include "gstlocal.hpp"
#include "gstcamera.hpp"

namespace gstpipe
{
class GstPipeFactory
{
public:
    ~GstPipeFactory();

    static GstPipeFactory* getInstance(){
        static GstPipeFactory factory;
        return &factory;
    }

    GstType getGstType(){
        return this->gst_type;
    }

    GstPipe* createPipeLine(GstType _type) {
        this->gst_type = _type;
        GstPipe* pipe_line;
        switch (_type) {
        case GstType::LOCAL:
            pipe_line = new GstLocal();
            break;
        case GstType::CAMERA:
            pipe_line = new GstCamera();
            break;
        case GstType::RTSP:
            pipe_line = new GstRtsp();
            break;
        }
        return pipe_line;
    }


private:
    /* data */
    GstPipeFactory(/* args */);

    GstType gst_type;

};

GstPipeFactory::GstPipeFactory(/* args */)
{
}

GstPipeFactory::~GstPipeFactory()
{
}



} // namespace gstpipe

#endif