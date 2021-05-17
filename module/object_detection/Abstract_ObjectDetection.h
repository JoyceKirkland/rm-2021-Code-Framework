#ifndef ABSTRACT_OBJECTDETECTION_H
#define ABSTRACT_OBJECTDETECTION_H

#include <iostream>
#include <fstream>
#include <sstream>

#include <opencv2/dnn/dnn.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace ObjectDetection
{

class Abstract_ObjectDetection
{
public:
  Abstract_ObjectDetection( const cv::dnn::Backend& backend_,
                            const cv::dnn::Target&  target_)
  {
    // 设置计算后台和目标设备
    this->net.setPreferableBackend(backend_);
    this->net.setPreferableTarget(target_);
  }
  
  virtual ~Abstract_ObjectDetection(){}

protected:
  cv::dnn::Net net;
};

} // namespace ObjectDetection

#endif // !ABSTRACT_OBJECTDETECTION_H
