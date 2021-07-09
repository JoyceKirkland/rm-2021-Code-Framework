#ifndef LINKER_H_
#define LINKER_H_

#include "rm_video_capture.h"

struct UserParam
{
  mv_camera::CameraParam camera_param;

  /**
   * @brief Construct a new User Param object
   * 
   * @param[in] _camera_param   相机参数
   */
  UserParam(mv_camera::CameraParam _camera_param)
      :camera_param(_camera_param){ }
};


class Connector
{
private:
  cv:: Mat src_img_;

public:
  explicit Connector(const UserParam &_user_param);
  virtual ~Connector();

  void init();

  void run();

  /**
   * @brief src_img_ 取值函数
   * @param[out] src_img_
   * @return cv::Mat 
   */
  inline cv::Mat image(){ return src_img_; }

private:
  mv_camera::RM_VideoCapture  mv_capture_;
  cv::VideoCapture            usb_capture_;
};

#endif // !LINKER_H_