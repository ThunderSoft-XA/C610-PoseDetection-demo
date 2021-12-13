#ifndef PUBLIC_ATTR_H
#define PUBLIC_ATTR_H

#include <iostream>
#include <string>

#ifndef EXPORT_API
#define EXPORT_API __attribute__ ((visibility("default")))
#endif

using namespace std;

namespace gstpipe
{

#define DEBUG_FUNC() std::cout << __FILE__ << "=======" << __LINE__ << std::endl

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief  the local camera for C610 camera on board,gstreamer plugins is qti series
 *                 the rtsp for uri stream
 */
typedef enum _GstType {
    LOCAL = 0,
    CAMERA,
    RTSP
}GstType;

/**
 * @brief the pipeline`s last output to local file or tcp client or udp client
 *LOCAL_FILE will use filesink or multifilesink
 * TCP will use tcpsink,needing support for tool same like vlc etc...
 * UDP will udp sink
 * SCREEN will directly draw to screen by wayland and gtk
 */
typedef enum _CameraDest {
    LOCAL_FILE = 0,
    TCP,
    UDP,
    SCREEN
} CameraDest;

#ifdef __cplusplus
}
#endif

class FrameAttr
{
private:
    /**
     * @brief These data describe a frame info, some member varitiant isn`t necessary
     * 
     */
    int width;
    int height;
    int channels;
    string format;
    unsigned long index;
    std::string path;

public:
    FrameAttr(/* args */){ }
    ~FrameAttr(){ }

    void setWidth(int _frame_w) { 
        this->width = _frame_w;
    } 
    int getWidth() {
        return this->width;
    }

    void setHeight(int _frame_h) {
        this->height = _frame_h;
    }
    int getHeight() {
        return height;
    }

    void setChannels(int _frame_c) {
        this->height = _frame_c;
    }
    int getChannels() {
        return this->channels;
    }

    void setFormat(string _frame_format)
    {
        #define FORMATED 0
        this->format = _frame_format;
    }
    string getFormat()
    {
        return this->format;
    }

    void setIndex(unsigned long _frame_index) {
        this->index = _frame_index;
    }
    unsigned long getIndex() {
        return this->index;
    }

    void setPath(std::string _frame_path) {
        this->path = _frame_path;
    }
    std::string getPath() {
        return this->path;
    }
};

/**
 * @brief some key info only video
 * 
 */
class VideoAttr : public FrameAttr
{
private:
    /* data */
    string decode_type;
    int framerate;
public:
    VideoAttr(/* args */){ }
    ~VideoAttr(){ }

    void setDecodeType(string _video_d)
    {
        this->decode_type = _video_d;
    }
    string getDecodeType()
    {
        return this->decode_type;
    }

    void setFramerate(int _video_f) {
        this->framerate = _video_f;
    }
    int getFramerate() {
        return this->framerate;
    }

};

} // namespace c610gst

#endif // !__PUBLIC_ATTR_H__