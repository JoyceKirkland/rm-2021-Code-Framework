/**
 * @file Abstract_SerialPort.h
 * 
 * @author GCUROBOT-Visual-Group (GCUROBOT_WOLF@163.com)
 * 
 * @brief A abstract declaration of serial port base class
 * 
 * @version 2.0
 * 
 * @date 2019-11-19 First edit
 * @date 2021-05-18 Last edit
 * 
 * @note This class was created by HZKKK and modified by RCXXX
 * 
 * @copyright GCU Robot Lab. All Rights Reserved.
 * 
 */
#ifndef RM_ABSTRACT_SERIALPORT_H_
#define RM_ABSTRACT_SERIALPORT_H_

#include <string.h>
#include <fcntl.h>  //文件控制定义
#include <termios.h>   //POSIX终端控制定义
#include <unistd.h>    //UNIX标准定义
#include <errno.h>     //ERROR数字定义
#include <sys/select.h>

#include <iostream>

namespace serial_port {

/**
 * @brief Abstract class of serial port
 * 
 */
class Abstract_SerialPort {

public:

    /**
     * @brief Construct a new Abstract_SerialPort object
     * 
     * @param[in] BAUDRATE_ 波特率
     */
    explicit Abstract_SerialPort(const int BAUDRATE_){
      std::cout<<"The Serial set ......"<<std::endl;
      
      /* WARNING :  终端设备默认会设置为控制终端，因此open(O_NOCTTY不作为控制终端)
       * Terminals'll default to be set as Control Terminals
       */
      struct termios newstate;
      /*打开串口*/
      bzero(&newstate, sizeof(newstate));//清零
      for(size_t i = 0; i<(sizeof(DeviceName)/sizeof(char*)); ++i){
        this-> fd = open(DeviceName[i], O_RDWR|O_NONBLOCK|O_NOCTTY|O_NDELAY);
        
        if (fd == -1) {
          printf("Can't Open Serial Port %s\n", DeviceName[i]);
          continue;
        } else {
          printf("Open Serial Port %s Successful\n", DeviceName[i]);
          break;
        }
      }

      // 设置 波特率
      switch (BAUDRATE_)
      {
      case 115200:{
        cfsetospeed(&newstate, B115200);
        cfsetispeed(&newstate, B115200);
      } break;
      
      case 1500000:{
        cfsetospeed(&newstate, B1500000);
        cfsetispeed(&newstate, B1500000);
      } break;
      default:{
        // the default baud rate is 115200
        cfsetospeed(&newstate, B115200);
        cfsetispeed(&newstate, B115200);
      } break;
      
      } // switch (BADNRATE_)

      //本地连线, 取消控制功能 | 开始接收
      newstate.c_cflag |= CLOCAL | CREAD;
      //设置字符大小
      newstate.c_cflag &= ~CSIZE;
      //设置停止位1
      newstate.c_cflag &= ~CSTOPB;
      //设置数据位8位
      newstate.c_cflag |= CS8;
      //设置无奇偶校验位，N
      newstate.c_cflag &= ~PARENB;

      /*阻塞模式的设置*/
      newstate.c_cc[VTIME]=0;
      newstate.c_cc[VMIN]=0;

      /*清空当前串口*/
      tcflush(fd,TCIOFLUSH);
      tcsetattr(fd, TCSANOW, &newstate);
    }
    
    /**
     * @brief Destroy the Abstract_SerialPort object
     * 
     */
    virtual ~Abstract_SerialPort(){
      if (!close(fd))
        printf("Close Serial Port Successful\n");
    }

protected:
  static int fd;

  static constexpr char* DeviceName[6] = {
    "", 
    "/dev/ttyUSB0", 
    "/dev/ttyUSB1", 
    "/dev/ttyUSB2",
    "/dev/ttyUSB3",
    "/dev/ttyUSB4"};

  static constexpr unsigned char CRC8TAB[300] = {
    0,94,188,226,97,63,221,131,194,156,126,32,163,253,31,65,
    157,195,33,127,252,162,64,30, 95,1,227,189,62,96,130,220,
    35,125,159,193,66,28,254,160,225,191,93,3,128,222,60,98,
    190,224,2,92,223,129,99,61,124,34,192,158,29,67,161,255,
    70,24,250,164,39,121,155,197,132,218,56,102,229,187,89,7,
    219,133,103,57,186,228,6,88,25,71,165,251,120,38,196,154,
    101,59,217,135,4,90,184,230,167,249,27,69,198,152,122,36,
    248,166,68,26,153,199,37,123,58,100,134,216,91,5,231,185,
    140,210,48,110,237,179,81,15,78,16,242,172,47,113,147,205,
    17,79,173,243,112,46,204,146,211,141,111,49,178,236,14,80,
    175,241,19,77,206,144,114,44,109,51,209,143,12,82,176,238,
    50,108,142,208,83,13,239,177,240,174,76,18,145,207,45,115,
    202,148,118,40,171,245,23,73,8,86,180,234,105,55,213,139,
    87,9,235,181,54,104,138,212,149,203, 41,119,244,170,72,22,
    233,183,85,11,136,214,52,106,43,117,151,201,74,20,246,168,
    116,42,200,150,21,75,169,247,182,232,10,84,215,137,107,53
  };
};

} // namespace serial_port

#endif // !RM_ABSTRACT_SERIALPORT_H_
