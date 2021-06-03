#include "connector.h"

Connector::Connector(const UserParam &_user_param)
    : mv_capture_(_user_param.camera_param),
      usb_capture_(0) {
  
}

Connector::~Connector() {

}

void Connector::run() {
  // get image
  // 如果默认使用工业相机，如果工业相机未连接则尝试使用 免驱usb 相机
  if(mv_capture_.isindustryimgInput()){
    src_img_ = mv_capture_.image();
  } else {
    usb_capture_ >> src_img_;
  }

  if(!src_img_.empty()){

    
  }

}