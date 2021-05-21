#ifndef RM_ARMORDETECTION_H_
#define RM_ARMORDETECTION_H_

#include <iostream>
#include <boost>

namespace armor{

typedef boost::shared_ptr<RM_ArmorDetector> RM_ArmorDetector_Ptr;

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