#ifndef BODY_PACKET_H
#define BODY_PACKET_H

#include <iostream>
#include <vector>
#include <cstddef>
#include <typeinfo>
#include <mutex>
#include <ctime>
#include <semaphore.h>
#include <atomic>
#include <memory>
#include <list>

#include <opencv2/opencv.hpp>

namespace body {
template<typename T>
class BodyPacket {
public:
    BodyPacket() {
        *inf_finish = false;
        *have_mat = false;
    }
    ~BodyPacket() {}
    void setMat(std::shared_ptr<cv::Mat> _src_mat){
        if (nullptr == _src_mat.get()) {
            throw "ERROR: feed an empty buffer to BodyPacket";
        }
        swap_mtx->lock();
        src_mat = _src_mat;
        *have_mat = true;
		swap_mtx->unlock();
        return;
    }

    cv::Mat getSrcMat() {
        if(!*have_mat) {
            exit (-1);
        }
        return *this->src_mat.get();
    }

    std::shared_ptr<cv::Mat> getResultMat() {
        if (*inf_finish) {
            swap_mtx->lock();
            this->resultProToMat();
			*inf_finish = false;
            swap_mtx->unlock();
        }
        return this->result_mat;
    }

    bool getInfState() {
        return *inf_finish;
    }

    void getValidResult(std::vector<T>& _inf_result);

private:
    std::atomic<bool>* have_mat;
    std::atomic<bool>* inf_finish;
    std::mutex* swap_mtx;
    std::shared_ptr<cv::Mat> src_mat;
    std::shared_ptr<std::vector<T>> valid_result;

    std::shared_ptr<cv::Mat> result_mat;

    static int point_pairs[24][2];

    void resultProToMat();
};

template <typename T>
void BodyPacket<T>::resultProToMat(){
    typename std::vector<T> result_vec = *valid_result.get();
    int body_num = result_vec.size() / (25 * 3);
    std::cout << "detection body number : " << body_num << std::endl;
    for (int i = 0; i < body_num; i++) {
        typename std::vector<T>::const_iterator sub_first = result_vec.begin()  + 25 * 3 * i;
        typename std::vector<T>::const_iterator sub_last  = result_vec.begin() + 25 * 3 * (i + 1);
        typename std::vector<T> sub_result_vec(sub_first, sub_last);
        for (int line_num = 0; line_num < 24; line_num++) {
            if(sub_result_vec[point_pairs[line_num][0] * 3 + 2] < 0.1 || sub_result_vec[point_pairs[line_num][1] * 3 + 2] < 0.1) {

            } else {
                cv::Scalar_<int> line_scalsr = cv::Scalar(rand()%255,rand()%255,rand()%255);
                cv::circle(*src_mat.get(),cv::Point_<T>(sub_result_vec[point_pairs[line_num][0] * 3],sub_result_vec[point_pairs[line_num][0] * 3 + 1]),0,line_scalsr,1);
                cv::circle(*src_mat.get(),cv::Point_<T>(sub_result_vec[point_pairs[line_num][1] * 3],sub_result_vec[point_pairs[line_num][1] * 3 + 1]),0,line_scalsr,1);
                cv::line(*src_mat.get(),cv::Point_<T>(sub_result_vec[point_pairs[line_num][0] * 3],sub_result_vec[point_pairs[line_num][0] * 3 + 1]),\
                    cv::Point_<T>(sub_result_vec[point_pairs[line_num][1] * 3],sub_result_vec[point_pairs[line_num][1] * 3 + 1]),\
                    line_scalsr,2);
            }
        }
        this->result_mat =std::make_shared<cv::Mat>(this->src_mat.get()->clone());
    }
}

template <typename T>
void BodyPacket<T>::getValidResult(std::vector<T>& _inf_result)
{
    float temp = 0.0f, prob = 0.0f;
    int x = 0, y =0;
    std::vector<T> _valid_result;
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
        _valid_result.push_back(x * 368 / 46);
        _valid_result.push_back(y * 368 / 46);
        _valid_result.push_back(prob);
        std::cout << " valid result : (" << x * 368 / 46 << "," << y * 368 / 46 << "," << prob << ")" << std::endl;
        prob = 0.0f;
    }
    this->valid_result = std::make_shared<std::vector<T>>(_valid_result);
    std::cout << "Extract valid data completed  !" << std::endl;
}

template<typename T> int BodyPacket<T>::point_pairs[24][2] = {{1, 0}, {1, 2}, {1, 5}, {2, 3}, {3, 4}, {5, 6}, {6, 7}, {0, 15}, {15, 17}, {0, 16}, \
                                            {16, 18}, {1, 8},{8, 9}, {9, 10}, {10, 11}, {11, 22}, {22, 23}, {11, 24},{8, 12},  \
                                            {12, 13}, {13, 14}, {14, 19}, {19, 20}, {14, 21}};

template class BodyPacket<float>;

}


#endif