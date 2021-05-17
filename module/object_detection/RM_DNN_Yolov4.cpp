#include "RM_DNN_Yolov4.h"

namespace ObjectDetection
{

DNN_Yolov4::DNN_Yolov4( const std::string yolov4_cfg_,
                        const std::string yolov4_weights_,
                        const std::string classes_,
                        const cv::dnn::Backend& backend_,
                        const cv::dnn::Target&  target_)
  :Abstract_ObjectDetection(backend_, target_)        
{
  // 加载模型
  this->net = cv::dnn::readNetFromDarknet(yolov4_cfg_, yolov4_weights_);

  // 获取网络的输出层名称
  out_names = this->net.getUnconnectedOutLayersNames();
  for (size_t i = 0; i < out_names.size(); ++i){
    std::cout<< "output layer name: " << out_names[i].c_str() << std::endl;
  }

  // 加载模型的标签集
  std::ifstream ifs_classes(classes_);
  if (ifs_classes.is_open()) {
    std::string class_name = "";
    while (getline(ifs_classes, class_name)) {
      class_names.push_back(class_name);
      std::cout<< "class " << class_names.size() - 1 << " :" << class_name << std::endl;
    }
  }

} // DNN_Yolov4()

DNN_Yolov4::~DNN_Yolov4(){
  net.~Net();
}

void DNN_Yolov4::objDetection(cv::Mat &input_img, std::vector<cv::Rect> &obj_boxes){
  cv::Mat input_blob = cv::dnn::blobFromImage(input_img, 1 / 256.F, input_img.size(), cv::Scalar(), true, false);
  
  net.setInput(input_blob);

  std::vector<cv::Mat> outs;
  net.forward(outs, out_names);

  // runtime 推理花费的时间
  std::vector<double> layers_time;
  double freq = cv::getTickFrequency() / 1000;
  double time = net.getPerfProfile(layers_time) / freq;
  std::string run_time = "run time: " + std::to_string(time) + "ms";
  cv::putText(input_img, run_time, cv::Point(20, 20), 0, 0.5, cv::Scalar::all(255));

  std::vector<cv::Rect> boxes;     // box
  std::vector<int> class_id;       // label
  std::vector<float> confidences;  // confidence level

  for (size_t i = 0; i < outs.size(); ++i)
  {
    float* data = (float*)(outs[i].data);

    for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols)
    {
      cv::Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
      cv::Point id_point;
      double confidence;

      cv::minMaxLoc(scores, nullptr, &confidence, nullptr, &id_point);
      if (confidence > 0.5) // 置信度阈值
      { // 获取 box
        int center_x = int(data[0] * input_img.cols);
        int center_y = int(data[1] * input_img.rows);
        int width = int(data[2] * input_img.cols);
        int height = int(data[3] * input_img.rows);
        int tl_x = center_x - width / 2;
        int tl_y = center_y - height / 2;

        boxes.push_back(cv::Rect(tl_x, tl_y, width, height));
        class_id.push_back(id_point.x);
        confidences.push_back(float(confidence));
      }
    }
  }

  // 极大值非抑制 获取最外侧的 box
  std::vector<int> max_idx;
  cv::dnn::NMSBoxes(boxes, confidences, 0.5, 0.2f , max_idx);
  for (size_t i = 0; i < max_idx.size(); ++i) {
    int idx = max_idx[i];
    cv::Rect box = boxes[idx];
    obj_boxes.push_back(box);
    
    std::string label = class_names[class_id[idx]];
    putText(input_img, label.c_str(), box.tl(), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 255, 0), 2, 8);
    rectangle(input_img, box, cv::Scalar::all(255), 2, 8, 0);
  }
} // void objDetection()

} // namespace ObjectDetection
