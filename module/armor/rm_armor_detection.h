#ifndef RM_ARMORDETECTION_H_
#define RM_ARMORDETECTION_H_

#include "module/angle_solve/rm_solve_pnp.h"
#include "module/filter/rm_kalman_filter.h"
#include "devices/serial/rm_serial_port.h"

#include <iostream>

namespace armor{
  
class RM_ArmorDetector
{
private:
  /* data */
public:
  RM_ArmorDetector(/* args */);
  ~RM_ArmorDetector();
};

} // namespace armor

#endif // !RM_ARMORDETECTION_H_