/**
 * @file Abstract_NN_Module.h
 *
 * @author GCUROBOT-Visual-Group: RCXXX(chuangxinr@gmail.com)
 *
 * @brief A abstract declaration of serial port base class
 *
 * @version 1.0
 *
 * @date 2021-05-18
 *
 * @copyright Copyright (c) 2021 GCU Robot Lab. All Rights Reserved.
 *
 */
#ifndef ABSTRACT_NN_MODULE_H_
#define ABSTRACT_NN_MODULE_H_

#include <iostream>
#include <fstream>
#include <sstream>

#include <opencv2/dnn/dnn.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace NN_Module {

/**
 * @brief
 *
 */
class Abstract_NN_Module
{
public:
  /**
   * @brief Construct a new Abstract_NN_Module object
   *
   * @param backend_
   * @param target_
   */
  Abstract_NN_Module( const cv::dnn::Backend& backend_,
                      const cv::dnn::Target&  target_)
  {
    // 设置计算后台和目标设备
    this->net.setPreferableBackend(backend_);
    this->net.setPreferableTarget(target_);
  }

  virtual ~Abstract_NN_Module(){}

protected:
  cv::dnn::Net net;
};

} // namespace NN_Module

#endif // !ABSTRACT_NN_MODULE_H_
