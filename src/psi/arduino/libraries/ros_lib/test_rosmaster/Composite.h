#ifndef _ROS_test_rosmaster_Composite_h
#define _ROS_test_rosmaster_Composite_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "test_rosmaster/CompositeA.h"
#include "test_rosmaster/CompositeB.h"

namespace test_rosmaster
{

  class Composite : public ros::Msg
  {
    public:
      typedef test_rosmaster::CompositeA _a_type;
      _a_type a;
      typedef test_rosmaster::CompositeB _b_type;
      _b_type b;

    Composite():
      a(),
      b()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->a.serialize(outbuffer + offset);
      offset += this->b.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->a.deserialize(inbuffer + offset);
      offset += this->b.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "test_rosmaster/Composite"; };
    const char * getMD5(){ return "d8fb6eb869ad3956b50e8737d96dc9fa"; };

  };

}
#endif
