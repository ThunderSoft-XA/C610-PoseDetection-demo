#include <iostream>
#include <sstream>
#include <opencv2/opencv.hpp>

#include "gstpipe.hpp"
#include "fastcv.h"

namespace gstpipe {

cv::Mat map1, map2;
const cv::Mat intrinsic_matrix_K = (cv::Mat_<double>(3,3) << 945.511,0,1545.17,0,945.511,1528.21,0,0,1);
const cv::Mat intrinsic_matrix_D = ( cv::Mat_<double> ( 8,1 ) << 0.19948,0.0422889,0,0,0.00202519,0.522254,0.0630432,0.011681);
const cv::Mat fish_matrix_D = ( cv::Mat_<double> ( 4,1 ) << 0.19948,0.0422889,0,0);


cv::Mat imageCalibration(cv::Mat _src_mat)
{
    // cv::Mat tmp_mat = cv::Mat(*this->data,CV_8UC4);
    cv::Mat UndistortImage,okay_mat;
    cv::resize(_src_mat,UndistortImage,cv::Size(1920,1080));
    cv::Size imageSize(_src_mat.cols, _src_mat.rows);
    cv::Mat R = cv::Mat::eye(3, 3, CV_32F);
    cv::Matx33d NewCameraMatrix;
    // cv::Mat calibration_mat = tmp_mat.reshape(4,this->data_info.height).clone();
    cv::fisheye::estimateNewCameraMatrixForUndistortRectify(intrinsic_matrix_K,fish_matrix_D,imageSize,R,NewCameraMatrix,0.0);
    // NewCameraMatrix = getOptimalNewCameraMatrix(intrinsic_matrix, D, imageSize, alpha, imageSize, 0);
    cv::fisheye::initUndistortRectifyMap(intrinsic_matrix_K, fish_matrix_D,R, NewCameraMatrix, imageSize, CV_16SC2, map1, map2);
    cv::remap(_src_mat, UndistortImage, map1, map2, cv::INTER_LINEAR,cv::BORDER_CONSTANT);
    cv::resize(UndistortImage,okay_mat,cv::Size(640,480));

    return okay_mat.clone();

}

class GstCamera: public GstPipe
{
public:
    GstCamera(){}
    ~GstCamera();

  void createPipeLine();
  cv::Mat getFrameData(void* _pipe);
};

void GstCamera::createPipeLine()
{
    std::ostringstream cameraPath;
    cameraPath << "qtiqmmfsrc af-mode=auto name="<< getPipeName();
    if(-1 == atoi(getPath().c_str())) {
        cameraPath << " ! ";
    } else {
        cameraPath << " camera=" << atoi(getPath().c_str()) << " " << getPipeName()<<".video_0 ! ";
    }
    cameraPath << "video/x-"<< getDecodeType() << ",format=" << getFormat() << ",width="<< getWidth() << ",height="<< getHeight() <<",framerate="<< getFramerate() <<"/1" << " ! ";
    if(isHwDec()) {
        cameraPath << getDecodeType() << "parse ! queue ! qtivdec ! qtivtransform ! video/x-raw,format=BGRA ! "; //qtivtransform rotate=90CW
    } else {
        cameraPath << "queue ! avdec_" << getDecodeType() <<" ! videoscale ! ";
    }
    cameraPath << "appsink name=" << getSinkName() << " sync=false  max-lateness=0 max-buffers=1 drop=true";
    setPipeStr(cameraPath.str());
    std::cout << "GST Pipeline: " << getPipeStr() << std::endl;
}

cv::Mat GstCamera::getFrameData(void* _pipe)
{
    printf("get gstreamer frame data\n");
    std::shared_ptr<GstSample> sample;
    GstCamera* pCam = reinterpret_cast<GstCamera *>(_pipe);

    pCam->getGstSample(sample);
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
        exit(-1);
    }
    cout <<"==sample width="<< sample_width <<",sample height = " << sample_height <<  endl;
    GstMapInfo sample_map;
    gst_buffer_map(gst_buffer,&sample_map,GST_MAP_READ);
    std::cout << "smaple map size: " << sample_map.size << std::endl;

    float32_t *data_buffer = (float32_t *)malloc(sizeof(float32_t)*sample_map.size);
    cv::Mat sample_mat;
    if(data_buffer != nullptr) {
        memset(data_buffer,0x00, sample_map.size);
        memcpy(data_buffer, (guchar *)sample_map.data, sample_map.size);
        if(pCam->getNeedCalib()) {
            float32_t param_set[] = {945.511,945.511,1545.17,1528.21,0.19948,0.0422889,0,0};
            fcvGeomUndistortPoint2x1f32(param_set,data_buffer,data_buffer);
        }
        sample_mat = cv::Mat(sample_width, sample_height, CV_32FC(sample_map.size/(sample_width * sample_height)), data_buffer, 0);	
    }
    free(data_buffer);
    //Avoiding memory leaks
    gst_buffer_unmap(gst_buffer, &sample_map);

    return sample_mat;
}
    
} // namespace gstpipe
