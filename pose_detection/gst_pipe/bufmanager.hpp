#ifndef BUF_MANAGER_H
#define BUF_MANAGER_H

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

#include <gst/gst.h>

using namespace std;
namespace gstpipe {

template<typename T>
class BodyPacket {
public:
    BodyPacket();
    ~BodyPacket();

    cv::Mat show_mat;
    std::vector<T> inference_result;

};

template<typename T>
class BufManager {
public:
    BufManager();
    ~BufManager();
    void feed(std::shared_ptr<T> pending);
    std::shared_ptr<T> front();
    std::shared_ptr<T> fetch();
private:
    std::atomic<bool> swap_ready;
    std::mutex swap_mtx;
    std::shared_ptr<T> front_sp;
    std::shared_ptr<T> back_sp;
public:
    std::string debug_info;

};
//typedef BufManager<cv::Mat> MatBufManager;
//typedef BufManager<GstSample> GstBufManager;
//#include "BufManager.tpp"

/** @brief It provides an easy-to-use, high-level interface to variety FaceSDK Algorithms.
 *
 * */
template<typename T> 
BufManager<T>::BufManager() /*noexcept */ {
	// swap_ready(false);
	swap_ready = false;
}

template<typename T>
BufManager<T>::~BufManager() /*noexcept*/ {
	if (!debug_info.empty() ) {
		std::cout << "BufManager" << debug_info << "destroyed." << std::endl;
	}
}
/** @brief Put the latest buffer into cache queue to be processed.
 *
 * Giving up control of previous front buffer.
 * @param[in] The latest buffer.
 * */
template<typename T> 
void BufManager<T>::feed(std::shared_ptr<T> pending) {
        if (nullptr == pending.get()) {
            throw "ERROR: feed an empty buffer to BufManager";
        }
        swap_mtx.lock();
        front_sp = pending;
        swap_ready = true;
		swap_mtx.unlock();
        return;
    }

    /** @brief Get the front buffer.
     * @return Front buffer.
     * */
template<typename T> 
std::shared_ptr<T> BufManager<T>::front()  /*noexcept */{
        return front_sp;
    }

    /** @brief Fetch the shared back buffer.
     * @return Back buffer.
     * */
template<typename T>
std::shared_ptr<T> BufManager<T>::fetch()  /*noexcept */{
        if (swap_ready) {
            swap_mtx.lock();
            std::swap(back_sp, front_sp);
			swap_ready = false;
            swap_mtx.unlock();
        }
        return back_sp;
    }

template class BufManager<GstSample>;

}
#endif
