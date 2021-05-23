#ifndef RM_SERIALPORT_H_
#define RM_SERIALPORT_H_

#include "abstract_serial_port.h"

namespace serial_port {
class RM_SerialPort : public Abstract_SerialPort {
public:
  RM_SerialPort(const int BAUDRATE_);

  virtual ~RM_SerialPort() {
    Abstract_SerialPort::~Abstract_SerialPort();
  }
};

} // namespace serial_port

#endif // !RM_SERIALPORT_H_
