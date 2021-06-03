#ifndef RM_SERIALPORT_H_
#define RM_SERIALPORT_H_

#include "abstract_serial_port.h"

namespace serial_port {

class RM_SerialPort : public Abstract_SerialPort<char> {
public:
  RM_SerialPort(const int _BAUDRATE,
                const int _write_buff_len,
                const int _receive_buff_len,
                const int _crc_buff_len)
      : Abstract_SerialPort(_BAUDRATE, _write_buff_len, _receive_buff_len, _crc_buff_len) 
  { }

  virtual ~RM_SerialPort() {
    Abstract_SerialPort::~Abstract_SerialPort();
  }

private:

  
};
} // namespace serial_port

#endif // !RM_SERIALPORT_H_
