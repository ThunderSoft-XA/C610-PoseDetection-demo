#include <iostream>

#include "RunSnpe/inference.hpp"

int point_pairs[24][2] = {{1, 0}, {1, 2}, {1, 5}, {2, 3}, {3, 4}, {5, 6}, {6, 7}, {0, 15}, {15, 17}, {0, 16}, \
                                            {16, 18}, {1, 8},{8, 9}, {9, 10}, {10, 11}, {11, 22}, {22, 23}, {11, 24},{8, 12},  \
                                            {12, 13}, {13, 14}, {14, 19}, {19, 20}, {14, 21}};


template <typename T>
void resultProToMat(cv::Mat src_mat,std::vector<T> inf_result,cv::Mat& result_mat){
    typename std::vector<T> result_vec = inf_result;
    int body_num = result_vec.size() / (25 * 3);
    std::cout << "detection body number : " << body_num << std::endl;
    for (int i = 0; i < body_num; i++) {
        typename std::vector<T>::const_iterator sub_first = result_vec.begin()  + 25 * 3 * i;
        typename std::vector<T>::const_iterator sub_last  = result_vec.begin() + 25 * 3 * (i + 1);
        typename std::vector<T> sub_result_vec(sub_first, sub_last);
        for (int line_num = 0; line_num < 24; line_num++) {
            cv::Point_<T> point;
            if(sub_result_vec[point_pairs[line_num][0] * 3 + 2] < 0.1 || sub_result_vec[point_pairs[line_num][1] * 3 + 2] < 0.1) {

            } else {
                cv::Scalar_<int> line_scalsr = cv::Scalar(rand()%255,rand()%255,rand()%255);
                cv::circle(src_mat,cv::Point_<T>(sub_result_vec[point_pairs[line_num][0] * 3],sub_result_vec[point_pairs[line_num][0] * 3 + 1]),0,line_scalsr,1);
                cv::circle(src_mat,cv::Point_<T>(sub_result_vec[point_pairs[line_num][1] * 3],sub_result_vec[point_pairs[line_num][1] * 3 + 1]),0,line_scalsr,1);
                cv::line(src_mat,cv::Point_<T>(sub_result_vec[point_pairs[line_num][0] * 3],sub_result_vec[point_pairs[line_num][0] * 3 + 1]),\
                    cv::Point_<T>(sub_result_vec[point_pairs[line_num][1] * 3],sub_result_vec[point_pairs[line_num][1] * 3 + 1]),\
                    line_scalsr,2);
            }
        }
        result_mat = src_mat.clone();
    }
}

template <typename T>
void getValidResult(std::vector<T>& _inf_result,std::vector<T>* _valid_result)
{
    float temp = 0.0f, prob = 0.0f;
    int x = 0, y =0;
    for (int i =0; i < 25; i++) {
        for (int j =0; j < 46; j++) {
            for (int z =0; z < 46; z++) {
                temp = _inf_result[j * 46 * 78 + z * 78 + i];
                if (temp > prob) {
                    x = z;
                    y = j;
                    prob = temp;
                }
            }
        }
        _valid_result->push_back(x * 368 / 46);
        _valid_result->push_back(y * 368 / 46);
        _valid_result->push_back(prob);
        std::cout << " valid result : (" << x * 368 / 46 << "," << y * 368 / 46 << "," << prob << ")" << std::endl;
        prob = 0.0f;
    }
    std::cout << "Extract valid data completed  !" << std::endl;
}


int main(int argc,char **argv)
{
    inference::snpe::Inference* snpe_inference = new inference::snpe::Inference(argv[1],inference::snpe::runtime_t::CPU,inference::snpe::DataFormat::NHWC);
    snpe_inference->Init(inference::snpe::runtime_t::CPU);
    cv::Mat src_mat = cv::imread("../../test.jpeg");
    cv::imshow("source mat",src_mat);
    cv::waitKey(0);
    std::vector<float> inference_result = snpe_inference->doInference<float>(src_mat);

    std::vector<float> valid_result;
    getValidResult<float>(inference_result,&valid_result);

    cv::Mat show_mat;
    cv::Mat final_mat;
    cv::resize(src_mat,show_mat,cv::Size(368,368));
    for (std::size_t i = 0; i < valid_result.size(); i++) {
        cv::circle(show_mat,cv::Point_<float>(valid_result[i*3],valid_result[i*3 + 1]),0,cv::Scalar(255,0,0),3);
    }
    resultProToMat<float>(show_mat,valid_result,final_mat);

    if(!final_mat.empty()) {
        cv::imwrite("snpe_test.jpg",final_mat);
    }

    return 0;
}