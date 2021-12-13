#ifndef INFERENCE_HPP
#define INFERENCE_HPP

#include <iostream>
#include <vector>
#include <sys/time.h>

#include <opencv2/opencv.hpp>

#include "DlContainer/IDlContainer.hpp"
#include "DlSystem/String.hpp"
#include "DlSystem/DlError.hpp"
#include "DlSystem/ITensor.hpp"
#include "DlSystem/ITensorFactory.hpp"
#include "SNPE/SNPEFactory.hpp"
#include "SNPE/SNPEBuilder.hpp"
#include "DlSystem/IUDL.hpp"
#include "DlSystem/UDLContext.hpp"

#include "common.h"

#define MODEL_INPUT_W 300
#define MODEL_INPUT_H 300
#define MODEL_INPUT_C 3


using namespace zdl;
using namespace std;

namespace inference {
namespace snpe {
/**  File description: only used to complete the configuration and execution inference of the SNPE runtime environment  
 *    Code specification: use SNPE little hump nomenclature , such as : helloWorld()
 *    This file does not contain the realization of pre-processing and post-processing 
 * */
class Inference {
public:
    Inference(){};
    Inference(std::string _model_path,runtime_t _device,DataFormat _format);
    ~Inference();

    int object_num;

    state_t Init(runtime_t device);
    state_t deInit();
    void setConfidence(float value);     
    template <typename T> std::vector<T> doInference(std::vector<cv::Mat>& mat_vec);
    template <typename T> std::vector<T> doInference(cv::Mat object_mat); 

private:
    std::string model_path;
    float mConfidenceThreshold;
    DataFormat data_format;

    std::unique_ptr<zdl::SNPE::SNPE> snpe;
    zdl::DlSystem::StringList outputLayers;
    std::shared_ptr<zdl::DlSystem::ITensor> inTensor;
    zdl::DlSystem::TensorShape iuput_shape;
    zdl::DlSystem::TensorMap outMap;
    zdl::DlSystem::TensorMap inMap;
    std::unique_ptr<zdl::DlSystem::ITensor> input;

    template<typename T> std::vector<T> loadByteDataMat(cv::Mat &_data_mat);
    template<typename T> bool loadByteDataMat(cv::Mat &_input_mat, std::vector<T>& loadVector);
    std::tuple<zdl::DlSystem::TensorMap, bool> loadMultipleInput (std::unique_ptr<zdl::SNPE::SNPE>& snpe , std::vector<cv::Mat>& mat_vec);
};

Inference::Inference(std::string _model_path,runtime_t _device,DataFormat _format)
{
    this->model_path = _model_path;
    this->mConfidenceThreshold = 0.8;
    this->data_format = _format;
    std::cout << "Snpe constructor fineshed ....." << std::endl;
}

/**Function description: func Init() for config snpe runtime ,build container and builder, and load .dlc model to container
 *   container : Represents a container for a neural network model which can be used to load the model into the SNPE runtime. 
 *   builder: Constructor of NeuralNetwork Builder with a supplied model.
 *   Runtime_t: Enumeration of supported target runtimes. 
 *   SNPE : The SNPE interface class definition .
 * */

state_t Inference::Init(runtime_t device) {
    std::cout << "starting Snpe Init....." << std::endl;
    std::unique_ptr<zdl::DlContainer::IDlContainer> container;
    container = zdl::DlContainer::IDlContainer::open(this->model_path);
    zdl::SNPE::SNPEBuilder snpeBuilder(container.get());

    zdl::DlSystem::Runtime_t runtime;
    switch (device) {
        case CPU: runtime = zdl::DlSystem::Runtime_t::CPU;break;
        case GPU: runtime = zdl::DlSystem::Runtime_t::GPU;break;
        case DSP: runtime = zdl::DlSystem::Runtime_t::DSP;break;
        case APU: runtime = zdl::DlSystem::Runtime_t::AIP_FIXED8_TF; break;
        default:  runtime = zdl::DlSystem::Runtime_t::GPU;break;
    }

    zdl::DlSystem::UDLBundle udlBundle;
    zdl::DlSystem::PerformanceProfile_t profile = zdl::DlSystem::PerformanceProfile_t::HIGH_PERFORMANCE;

    zdl::DlSystem::TensorShapeMap new_input_map = zdl::DlSystem::TensorShapeMap();
    std::vector<size_t> new_shpe = {1,368,368,3};
    zdl::DlSystem::TensorShape new_input_shape = zdl::DlSystem::TensorShape(new_shpe);
    new_input_map.add("image",new_input_shape);

    std::cout << "starting Snpe builder....." << std::endl;
    this->snpe = snpeBuilder.setInputDimensions(new_input_map)
        .setOutputLayers(outputLayers)
        .setRuntimeProcessor(runtime)
        .setCPUFallbackMode(true)
        .setPerformanceProfile(profile)
        .setUdlBundle(udlBundle)
        .build();
    if(nullptr == this->snpe) {
        const char* const err = zdl::DlSystem::getLastErrorString();
        std::cout<<"!!!!!! ERROR code :"<<err<<std::endl;
        return INIT_ERROR;
    } else {
        std::cout << "starting get Snpe required info ....." << std::endl;
        const auto strList = snpe->getInputTensorNames();
        auto inputDims = snpe->getInputDimensions((*strList).at(0));
        this->iuput_shape = *inputDims;
        size_t rank = this->iuput_shape.rank();
        int input_size = 1;
        for (size_t i=0; i < rank; i++) {
            input_size *= this->iuput_shape[i];
            std::cout << "input shape" << i << ":" << this->iuput_shape[i] <<std::endl;
        }

        inTensor = zdl::SNPE::SNPEFactory::getTensorFactory().createTensor(inputDims);
        inMap.add((*strList).at(0), inTensor.get());
        zdl::DlSystem::Version_t version = zdl::SNPE::SNPEFactory::getLibraryVersion();
        std::cout << "snpe version is " << version.asString() << std::endl;
    }      
    std::cout << "snpe init finish"<< std::endl;
    return NO_ERROR;
}

state_t Inference::deInit() {
    if (nullptr != snpe) {
        snpe.reset(nullptr);
    }
    return NO_ERROR;
}

template<typename T>
std::vector<T> Inference::loadByteDataMat(cv::Mat &_data_mat)
{
    assert(_data_mat.empty() != true);
   std::vector<T> vec;
   loadByteDataMat(_data_mat, vec);
   return vec;
}

template<typename T>
bool Inference::loadByteDataMat(cv::Mat &_input_mat, std::vector<T>& loadVector)
{
    cv::Mat input;
    cv::Size src_size;
    if (this->data_format == DataFormat::NHWC) {
        src_size = cv::Size(this->iuput_shape[1], this->iuput_shape[2]);
    } else {
        src_size = cv::Size(this->iuput_shape[2], this->iuput_shape[3]);
    }
    std::cout << "input mat`s channels = " << _input_mat.channels() << std::endl;
    cv::Mat resize_mat = cv::Mat(src_size, _input_mat.channels());
    cv::resize(_input_mat, resize_mat, src_size);
    cv::cvtColor(resize_mat, input, CV_BGR2RGB);

    cv::Mat input_norm(src_size.width, src_size.height, CV_32FC3, inTensor.get()->begin().dataPointer());
    input.convertTo(input, CV_32F);
    cv::normalize(input, input_norm, -1.0f, 1.0f, cv::NORM_MINMAX);

    loadVector = (vector<T>)(input_norm.reshape(1, 1));

    std::cout << "loadByteDataMat to _vector`s size =  " << loadVector.size() << std::endl;
    std::cout << __FILE__ << "unsigned char mat finished..." << __LINE__ << std::endl;
    return true;
}

// Load multiple input tensors for a network which require multiple inputs
std::tuple<zdl::DlSystem::TensorMap, bool> Inference::loadMultipleInput (std::unique_ptr<zdl::SNPE::SNPE>& snpe , std::vector<cv::Mat>& mat_vec)
{
    assert(mat_vec.empty() != true);
    std::cout << __FILE__ << "=vector mat`s count = "<< mat_vec.size()  << __LINE__ << std::endl;
    zdl::DlSystem::TensorMap dummy; // dummy map for returning on failure
    const auto& inputTensorNamesRef = snpe->getInputTensorNames();
    if (!inputTensorNamesRef) throw std::runtime_error("Error obtaining Input tensor names");
    const auto &inputTensorNames = *inputTensorNamesRef;
    // Make sure the network requires multiple inputs
    assert (inputTensorNames.size() > 1);

    if (inputTensorNames.size()) std::cout << "Processing DNN Input: " << std::endl;

    std::vector<std::unique_ptr<zdl::DlSystem::ITensor>> inputs(inputTensorNames.size());
    zdl::DlSystem::TensorMap  inputTensorMap;

    std::cout << "input tensor num = " << inputTensorNames.size() << std::endl; 
    for (size_t j = 0; j<inputTensorNames.size(); j++) {
        std::string inputName(inputTensorNames.at(j));
        std::vector<unsigned char> inputVec = loadByteDataMat<unsigned char>(mat_vec[j]);

        const auto &inputShape_opt = snpe->getInputDimensions(inputTensorNames.at(j));
        const auto &inputShape = *inputShape_opt;
        inputs[j] = zdl::SNPE::SNPEFactory::getTensorFactory().createTensor(inputShape);

        if (inputs[j]->getSize() != inputVec.size()) {
            std::cerr << "Size of input does not match network.\n"
                        << "Expecting: " << inputs[j]->getSize() << "\n"
                        << "Got: " << inputVec.size() << "\n";
            return std::make_tuple(dummy, false);
        }

        std::copy(inputVec.begin(), inputVec.end(), inputs[j]->begin());
        inputTensorMap.add(inputName.c_str(), inputs[j].release());
    }
    std::cout << __FILE__ << "Finished processing inputs for current inference " << __LINE__ << std::endl;
    return std::make_tuple(inputTensorMap, true);
}

template <typename T>
std::vector<T> Inference::doInference(std::vector<cv::Mat>& mat_vec) 
{
    assert(mat_vec.empty() != true);
    struct timeval  time_start,time_end;
    gettimeofday(&time_start, nullptr);
    std::vector<T> result;
    if (NULL == snpe) {
        return result;
    }
    std::cout << __FILE__ << "do track processing..." << __LINE__ << std::endl;
    std::tuple<zdl::DlSystem::TensorMap, bool> input_tuple = this->loadMultipleInput(this->snpe, mat_vec);
    this->inMap = std::get<0> (input_tuple);

    zdl::DlSystem::ITensor* outputTensor = nullptr;
    bool ret = snpe->execute(inMap, outMap);
    if (!ret) {
        const char* const err = zdl::DlSystem::getLastErrorString();
        std::cout << "!!!!!!ERROR code [InitError] :" << err << std::endl;
        return result;
    }
    zdl::DlSystem::StringList tensorNames = outMap.getTensorNames();
    for( auto& name: tensorNames ){
        outputTensor = outMap.getTensor(name);
        std::cout << "tensor name: "<< name << std::endl;
        std::cout << "OutputShape : " << outputTensor->getShape().getDimensions()[0] << " x "
            << outputTensor->getShape().getDimensions()[1] << std::endl;
    }
    zdl::DlSystem::TensorShape shape = outputTensor->getShape();

    size_t rank = shape.rank();
    int input_size = 1;
    for (size_t i = 0; i < rank; i++) {
        input_size *= shape[i];
        std::cout << "output shape" << i << ":" << shape[i] << std::endl;
    }
    result.clear();
    double elapsed_time;
    gettimeofday(&time_end, nullptr);
    elapsed_time = (time_end.tv_sec - time_start.tv_sec) * 1000 +
        (time_end.tv_usec - time_start.tv_usec) / 1000;
    cout << "the time of track = " << elapsed_time << endl;
    std::cout << " input size = " << input_size << std::endl;
    cout << "Output Rusult : "<<endl;
    for ( auto it = outputTensor->cbegin(); it != outputTensor->cend() ;it++ ) {
        float f = *it;
        cout <<f << " ";
        result.push_back(f);
    }
    cout <<endl;
    outMap.clear();

    std::cout << __FILE__ << "do detect finished..." << __LINE__ << std::endl;
    return result;
}

void Inference::setConfidence(float value) {
    mConfidenceThreshold = value > 1.0f ? 1.0f : (value < 0.0f ? 0.0f : value);
}

template <typename T>
std::vector<T> Inference::doInference(cv::Mat object_mat)
{
    std::vector<float> result;
    if (NULL == snpe) {
        return result;
    }
    cv::Mat input;
    cv::Size wanted_size;

    if (this->data_format == DataFormat::NHWC) {
        wanted_size = cv::Size(this->iuput_shape[1], this->iuput_shape[2]);
    } else {
        wanted_size = cv::Size(this->iuput_shape[2], this->iuput_shape[3]);
    }

    cv::Mat resize_mat;
    cv::resize(object_mat, resize_mat, wanted_size);
    cv::cvtColor(resize_mat, input, CV_BGR2RGB);

    cv::Mat input_norm(wanted_size.width, wanted_size.height, CV_32FC3, inTensor.get()->begin().dataPointer());
    input.convertTo(input, CV_32F);
    cv::normalize(input, input_norm, -1.0f, 1.0f, cv::NORM_MINMAX);

    zdl::DlSystem::ITensor* outputTensor = nullptr;
    bool ret = snpe->execute(inMap, outMap);
    if (!ret) {
        const char* const err = zdl::DlSystem::getLastErrorString();
        std::cout << "!!!!!!ERROR code [Inference] :" << err << std::endl;
        return result;
    }
    zdl::DlSystem::StringList tensorNames = outMap.getTensorNames();
    for( auto& name: tensorNames ){
        std::cout << "output tensor name: "<< name << std::endl;
        outputTensor = outMap.getTensor(name);
        std::cout << "OutputShape : " << outputTensor->getShape().getDimensions()[0] << " x "
            << outputTensor->getShape().getDimensions()[1] << " x "
            << outputTensor->getShape().getDimensions()[2] << " x "
            << outputTensor->getShape().getDimensions()[3] << std::endl;
    }

    for ( auto it = outputTensor->cbegin(); it != outputTensor->cend() ;it++ ) {
        float f = *it;
        result.push_back(f);
    }

    std::cout << "snpe inference finished !" << std::endl;
    return result;
}

Inference::~Inference() {
    if (snpe != nullptr) {
        snpe.reset(nullptr);
    }
}

}
}

#endif