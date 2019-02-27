#ifndef _ROS_test_rosmaster_RosmsgC_h
#define _ROS_test_rosmaster_RosmsgC_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "test_rosmaster/String.h"

namespace test_rosmaster
{

  class RosmsgC : public ros::Msg
  {
    public:
      typedef test_rosmaster::String _s1_type;
      _s1_type s1;
      typedef test_rosmaster::String _s2_type;
      _s2_type s2;

    RosmsgC():
      s1(),
      s2()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->s1.serialize(outbuffer + offset);
      offset += this->s2.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->s1.deserialize(inbuffer + offset);
      offset += this->s2.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "test_rosmaster/RosmsgC"; };
    const char * getMD5(){ return "cc91a7e3c1498150f3554cbcab2800d2"; };

  };

}
#endif
