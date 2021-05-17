#ifndef RM_DNN_YOLOV4_H
#define RM_DNN_YOLOV4_H

#include "Abstract_ObjectDetection.h"

namespace ObjectDetection
{

class DNN_Yolov4 : public Abstract_ObjectDetection
{
public:
  DNN_Yolov4( const std::string yolov4_cfg,
              const std::string yolov4_weights,
              const std::string classes,
              const cv::dnn::Backend& backend_,
              const cv::dnn::Target&  target_);

  ~DNN_Yolov4();

  void objDetection(cv::Mat &input_img, std::vector<cv::Rect> &obj_boxes);

private:
  std::vector<std::string> out_names;
  std::vector<std::string> class_names;
};

} // namespace ObjectDetection

#endif // !RM_DNN_YOLOV4_H
