#include <iostream>
#include <opencv2/opencv.hpp>

#include "devices/camera/rm_video_capture.h"

int main() {
  auto camera_param =
      mv_camera::CameraParam(0, mv_camera::RESOLUTION::RESOLUTION_1280_X_1024,
                             mv_camera::EXPOSURETIME::EXPOSURE_800);

  mv_camera::RM_VideoCapture cap(camera_param);

  cv::Mat src_img;

  while (1) {
    if (cap.isindustryimgInput()) {
      src_img = cap.image();
    } else {
      break;
    }

    cv::imshow("src_img", src_img);

    if (char(cv::waitKey(1)) == 27) {
      cap.cameraReleasebuff();
      break;
    }
    cap.cameraReleasebuff();
  }

  cap.~RM_VideoCapture();
  return 0;
}