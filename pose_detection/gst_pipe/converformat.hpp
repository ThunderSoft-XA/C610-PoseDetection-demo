#ifndef CONVER_FORMAT_HPP
#define CONVER_FORMAT_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include "fastcv.h"

#define LOG(x) std::cerr

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

bool fastcvImgCalib(float32_t *_src,float32_t *_dest)
{
    float32_t param_set[] = {945.511,945.511,1545.17,1528.21,0.19948,0.0422889,0,0};
    fcvGeomUndistortPoint2x1f32(param_set,_src,_dest);
    return true;
}

void nv12ToRGB(unsigned int width , unsigned int height , unsigned char *yuyv , unsigned char *rgb)
{
const int nv_start = width * height ;
    unsigned int  i, j, index = 0, rgb_index = 0;
    unsigned char y, u, v;
    int r, g, b, nv_index = 0;
	
 
    for(i = 0; i <  height ; i++)
    {
		for(j = 0; j < width; j ++){
			//nv_index = (rgb_index / 2 - width / 2 * ((i + 1) / 2)) * 2;
			nv_index = i / 2  * width + j - j % 2;
 
			y = yuyv[rgb_index];
			v = yuyv[nv_start + nv_index ];
			u = yuyv[nv_start + nv_index + 1];
			
		
			r = y + (140 * (v-128))/100;  //r
			g = y - (34 * (u-128))/100 - (71 * (v-128))/100; //g
			b = y + (177 * (u-128))/100; //b
				
			if(r > 255)   r = 255;
			if(g > 255)   g = 255;
			if(b > 255)   b = 255;
       		if(r < 0)     r = 0;
			if(g < 0)     g = 0;
			if(b < 0)     b = 0;
			
			index = rgb_index % width + (height - i - 1) * width;
			rgb[index * 3+0] = b;
			rgb[index * 3+1] = g;
			rgb[index * 3+2] = r;
			rgb_index++;
		}
    }
}

void nv12ToBGR(unsigned int width, unsigned int height, unsigned char *yuyv,unsigned char *bgr) 
{
    const int nv_start = width * height;
    int i, j, index = 0, rgb_index = 0;
    unsigned char y, u, v;
    int r, g, b, nv_index = 0;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            //nv_index = (rgb_index / 2 - width / 2 * ((i + 1) / 2)) * 2;
            nv_index = i / 2 * width + j - j % 2;

            y = yuyv[rgb_index];
            v = yuyv[nv_start + nv_index];
            u = yuyv[nv_start + nv_index + 1];
//            u = yuyv[nv_start + nv_index ];
//            v = yuyv[nv_start + nv_index + 1];

            r = y + (140 * (v - 128)) / 100;  //r
            g = y - (34 * (u - 128)) / 100 - (71 * (v - 128)) / 100; //g
            b = y + (177 * (u - 128)) / 100; //b

            if (r > 255)
                r = 255;
            if (g > 255)
                g = 255;
            if (b > 255)
                b = 255;
            if (r < 0)
                r = 0;
            if (g < 0)
                g = 0;
            if (b < 0)
                b = 0;

            index = rgb_index % width + (height - i - 1) * width;
            bgr[index * 3 + 2] = r;
            bgr[index * 3 + 1] = g;
            bgr[index * 3 + 0] = b;
            rgb_index++;
        }
    }
}

#define clamp_g(x, minValue, maxValue) ((x) < (minValue) ? (minValue) : ((x) > (maxValue) ? (maxValue) : (x)))
int nv21ToBGR(unsigned int width,unsigned int height,unsigned char * srcYVU, unsigned char * destBGR)
{

    unsigned char * srcVU = srcYVU + width * height;

    unsigned char Y, U, V;
    int B, G, R;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Y = srcYVU[i * width + j];
            V = srcVU[(i / 2 * width / 2 + j / 2) * 2 + 0];
            U = srcVU[(i / 2 * width / 2 + j / 2) * 2 + 1];


            R = 1.164*(Y - 16) + 1.596*(V - 128);
            G = 1.164*(Y - 16) - 0.813*(V - 128) - 0.392*(U - 128);
            B = 1.164*(Y - 16) + 2.017*(U - 128);

            destBGR[(i * width + j) * 3 + 0] = clamp_g(B, 0, 255);
            destBGR[(i * width + j) * 3 + 1] = clamp_g(G, 0, 255);
            destBGR[(i * width + j) * 3 + 2] = clamp_g(R, 0, 255);


        }
    }
    return 0;
}

//hikvision yuv420p for yvu not yuv
void yuv420pToBGR24(int width, int height,unsigned char *data, unsigned char *bgr)
{
    int index = 0;
    unsigned char *ybase = data;
    unsigned char *vbase = &data[width * height ];
    unsigned char *ubase = &data[width * height * 5 / 4];
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            //YYYYYYYYUUVV
            u_char Y = ybase[x + y * width];
            u_char U = ubase[y / 2 * width / 2 + (x / 2)];
            u_char V = vbase[y / 2 * width / 2 + (x / 2)];
            bgr[index++] = Y + 1.402 * (V - 128); //R
            bgr[index++] = Y - 0.34413 * (U - 128) - 0.71414 * (V - 128); //G
            bgr[index++] = Y + 1.772 * (U - 128); //B
        }
    }
}

void yuv420pToBGR32(int width, int height,unsigned char *yuvBuffer_in, unsigned char *rgbBuffer_out)
{
    uchar *yuvBuffer = (uchar *)yuvBuffer_in;
    uchar *rgb32Buffer = (uchar *)rgbBuffer_out;

    int channels = 3;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int index = y * width + x;

            int indexY = y * width + x;
            int indexU = width * height + y / 2 * width / 2 + x / 2;
            int indexV = width * height + width * height / 4 + y / 2 * width / 2 + x / 2;

            uchar Y = yuvBuffer[indexY];
            uchar U = yuvBuffer[indexU];
            uchar V = yuvBuffer[indexV];
            
            int R = Y + 1.402 * (V - 128);
            int G = Y - 0.34413 * (U - 128) - 0.71414*(V - 128);
            int B = Y + 1.772*(U - 128);
            R = (R < 0) ? 0 : R;
            G = (G < 0) ? 0 : G;
            B = (B < 0) ? 0 : B;
            R = (R > 255) ? 255 : R;
            G = (G > 255) ? 255 : G;
            B = (B > 255) ? 255 : B;

            rgb32Buffer[(y*width + x)*channels + 2] = uchar(R);
            rgb32Buffer[(y*width + x)*channels + 1] = uchar(G);
            rgb32Buffer[(y*width + x)*channels + 0] = uchar(B);
        }
    }
}


void picToGray(cv::Mat camerFrame,cv::Mat &gray)
{
	//common PC 3 channel BGR,mobile phone 4 channel
	if (camerFrame.channels() == 3)
	{
		cv::cvtColor(camerFrame, gray, CV_BGR2GRAY);
	}
	else if (camerFrame.channels() == 4)
	{
		cv::cvtColor(camerFrame, gray, CV_BGRA2GRAY);
	}
	else
		gray = camerFrame;
}

std::vector<uint8_t> decodeMat(cv::Mat _src,int row_size) 
{
    int height = _src.rows;
    int width = _src.cols;
    int channels = _src.channels();
    uchar * input = _src.data;
    std::vector<uint8_t> output(height * width * channels);
    for (int i = 0; i < height; i++) {
        int src_pos;
        int dst_pos;

        for (int j = 0; j < width; j++) {
 
        src_pos = i * row_size + j * channels;

        dst_pos = (i * width + j) * channels;

        switch (channels) {
            case 1:
            output[dst_pos] = input[src_pos];
            break;
            case 3:
            // BGR -> RGB
            output[dst_pos] = input[src_pos + 2];
            output[dst_pos + 1] = input[src_pos + 1];
            output[dst_pos + 2] = input[src_pos];
            break;
            case 4:
            // BGRA -> RGBA
            output[dst_pos] = input[src_pos + 2];
            output[dst_pos + 1] = input[src_pos + 1];
            output[dst_pos + 2] = input[src_pos];
            output[dst_pos + 3] = input[src_pos + 3];
            break;
            default:
            LOG(FATAL) << "Unexpected number of channels: " << channels;
            break;
        }
        }
    }
    return output;
}

#endif