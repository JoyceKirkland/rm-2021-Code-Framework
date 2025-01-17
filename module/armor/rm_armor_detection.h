#ifndef RM_ARMORDETECTION_H_
#define RM_ARMORDETECTION_H_

#include <iostream>
#include <opencv2/opencv.hpp>

#include "rm_serial_port.h"
#include "rm_solve_pnp.h"
#include "rm_kalman_filter.h"

namespace armor {
struct Armor_Data {
  cv::RotatedRect armor_rect;   ///
  float width = 0;              ///装甲板宽度
  float height = 0;             ///装甲板高度
  float aspect_ratio = 0;       ///装甲板宽高比
  float tan_angle = 0;          ///
  cv::RotatedRect left_light;   ///
  cv::RotatedRect right_light;  ///

  int distance_center = 0;

  float left_light_width = 0;    ///左灯条宽度
  float right_light_width = 0;   ///右灯条高度
  float left_light_height = 0;   ///左灯条高度
  float right_light_height = 0;  ///右灯条高度

  float light_height_aspect = 0;  ///左灯条高和右灯条高比值
  float light_width_aspect = 0;   ///左灯条宽和右灯条宽比值

  int distinguish = 0;  ///大小装甲板 小0 大1
};
struct Armor_Cfg {
  int armor_edit;

  int light_height_ratio_min;
  int light_height_ratio_max;
  int light_width_ratio_min;
  int light_width_ratio_max;

  int light_y_different;
  int light_height_different;
  int armor_angle_different;

  int small_armor_aspect_min;
  int armor_type_th;
  int big_armor_aspect_max;
};

struct Light_Cfg {
  int light_draw;
  int light_edit;
  //灯条宽高比范围
  int ratio_w_h_min;
  int ratio_w_h_max;
  //灯条角度范围
  int angle_min;
  int angle_max;
  //灯条长度范围
  int perimeter_max;
  int perimeter_min;
};

struct Image_Cfg {
  // BGR
  int red_armor_gray_th;
  int red_armor_color_th;
  int blue_armor_gray_th;
  int blue_armor_color_th;
  // HSV-red
  int h_red_max;
  int h_red_min;
  int s_red_max;
  int s_red_min;
  int v_red_max;
  int v_red_min;
  // HSV-blue
  int h_blue_max;
  int h_blue_min;
  int s_blue_max;
  int s_blue_min;
  int v_blue_max;
  int v_blue_min;

  int gray_edit = 0;
  int color_edit = 0;
  int method = 0;
};
/**
 * @brief 图像处理
 *
 */
class RM_ArmorDetector {
  //构造函数
 public:
  RM_ArmorDetector() {}
  RM_ArmorDetector(std::string _armor_config);
  ~RM_ArmorDetector() {}

  // Image
 private:
  cv::Mat gray_trackbar_ = cv::Mat::zeros(1, 300, CV_8UC1);
  cv::Mat bgr_trackbar_ = cv::Mat::zeros(1, 300, CV_8UC1);
  cv::Mat hsv_trackbar_ = cv::Mat::zeros(1, 300, CV_8UC1);
  cv::Mat ele_ = getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
  Image_Cfg image_config_;

 public:
  void run_Image(cv::Mat &_src_img, const int _my_color);
  cv::Mat bgr_Pretreat(cv::Mat &_src_img, const int _my_color);
  cv::Mat hsv_Pretreat(cv::Mat &_src_img, const int _my_color);
  cv::Mat gray_Pretreat(cv::Mat &_src_img, const int _my_color);
  cv::Mat fuse_Image(cv::Mat _bin_gray_img, cv::Mat _bin_color_img);

  //灯条
 public:
  bool find_Light();  //寻找灯条
 private:
  Light_Cfg light_config_;

  //装甲板
 public:
  bool run_Armor(cv::Mat &_src_img, int my_color);
  bool light_Judge(int i, int j);  //判断左右灯条能否组成装甲板
  int average_Color();             //计算图像颜色平均值
  bool fitting_Armor();            //拟合装甲板
  void final_Armor();              //最优装甲板
  void free_Memory();              //释放内存
  cv::RotatedRect return_Final_Armor_RotatedRect(int _num);
  int return_Final_Armor_Distinguish(int _num);

 private:
  Armor_Cfg armor_config_;
  Armor_Data armor_data_;

  cv::Mat draw_img_;  //画板
  cv::Mat gray_img_;
  cv::Mat hsv_img_;
  cv::Mat bin_gray_img_;
  cv::Mat bin_color_img_;
  cv::Mat armor_trackbar_ = cv::Mat::zeros(1, 300, CV_8UC1);
  cv::Rect armor_roi_;
  cv::Point lost_armor_center_;
  cv::Point armor_center_;  //装甲板中心点

  std::vector<Armor_Data> armor_;
  std::vector<cv::RotatedRect> light_;

  bool lost_armor_success_ = false;
  bool armor_success_ = false;
  bool switch_armor_ = false;  //切换装甲板
};
}  // namespace armor

#endif  // !RM_ARMORDETECTION_H_
