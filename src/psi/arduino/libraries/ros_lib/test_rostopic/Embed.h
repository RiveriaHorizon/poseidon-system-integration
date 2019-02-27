#ifndef _ROS_test_rostopic_Embed_h
#define _ROS_test_rostopic_Embed_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "test_rostopic/Simple.h"
#include "test_rostopic/Arrays.h"

namespace test_rostopic
{

  class Embed : public ros::Msg
  {
    public:
      typedef test_rostopic::Simple _simple_type;
      _simple_type simple;
      typedef test_rostopic::Arrays _arrays_type;
      _arrays_type arrays;

    Embed():
      simple(),
      arrays()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->simple.serialize(outbuffer + offset);
      offset += this->arrays.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->simple.deserialize(inbuffer + offset);
      offset += this->arrays.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "test_rostopic/Embed"; };
    const char * getMD5(){ return "6dec891298f3675c2d964c161d28efaa"; };

  };

}
#endif
