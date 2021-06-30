#ifndef RM_SOLVEPNP_H_
#define RM_SOLVEPNP_H_

#include "module/angle_solve/abstract_solve_pnp.hpp"

namespace angle_solve {
class Rm_Solvepnp : public Abstract_Solvepnp {
 private:
  cv::Mat cameraMatrix_, distCoeffs_;
  cv::Mat rvec_ = cv::Mat::zeros(3, 3, CV_64FC1);
  cv::Mat tvec_ = cv::Mat::zeros(3, 1, CV_64FC1);
  std::vector<cv::Point2f> target_2d_;
  std::vector<cv::Point3f> object_3d_;

  Solvepnp_Cfg pnp_config_;

 public:
  Rm_Solvepnp(std::string _camera_path, std::string _pnp_config_path);
  Rm_Solvepnp();

  cv::Point3f run_Solvepnp(int _ballet_speed, int _armor_type,
                           cv::Mat &_src_img, cv::RotatedRect _rect);

  cv::Point3f run_Solvepnp(int _ballet_speed, int _width, int _height,
                           cv::Mat &_src_img, cv::RotatedRect _rect);

  cv::Point3f run_Solvepnp(int _ballet_speed, int _armor_type,
                           cv::Mat &_src_img, cv::Rect _rect);

  cv::Point3f run_Solvepnp(int _ballet_speed, int _width, int _height,
                           cv::Mat &_src_img, cv::Rect _rect);

  cv::Point3f run_Solvepnp(int _ballet_speed, int _armor_type,
                           cv::RotatedRect _rect);

  cv::Point3f run_Solvepnp(int _ballet_speed, int _width, int _height,
                           cv::RotatedRect _rect);

  cv::Point3f run_Solvepnp(int _ballet_speed, int _armor_type, cv::Rect _rect);

  cv::Point3f run_Solvepnp(int _ballet_speed, int _width, int _height,
                           cv::Rect _rect);
  ~Rm_Solvepnp();
};

}  // namespace angle_solve

#endif  // !RM_SOLVEPNP_H_