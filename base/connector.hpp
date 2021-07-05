#ifndef LINKER_H_
#define LINKER_H_

#include "rm_armor.hpp"
#include "rm_serial_port.hpp"
#include "rm_solve_pnp.hpp"
#include "rm_video_capture.hpp"

class Connector {
 private:
  cv::Mat src_img_;

 public:
  void run();
  Connector();
  ~Connector();
};

#endif  // !LINKER_H_