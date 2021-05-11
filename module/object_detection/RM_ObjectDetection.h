#ifndef RM_OBJECTDETECTION_H
#define RM_OBJECTDETECTION_H

#include <iostream>
#include <fstream>
#include <sstream>

#include <opencv2/dnn/dnn.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace ObjectDetection
{
// 相对路径，用的时候改成绝对路径
const std::string yolov4_cfg = "common/yolo/model/";
const std::string yolov4_weights = "common/yolo/weights/";
const std::string classes = "common/yolo/classes/";

class CvYolov4
{
public:
  CvYolov4();
  ~CvYolov4();

  void objDetection(cv::Mat &input_img, std::vector<cv::Rect> &obj_boxes);

private:
  cv::dnn::Net net;
  std::vector<std::string> out_names;
  std::vector<std::string> class_names;
};

} // namespace ObjectDetection

#endif // !RM_OBJECTDETECTION_H
