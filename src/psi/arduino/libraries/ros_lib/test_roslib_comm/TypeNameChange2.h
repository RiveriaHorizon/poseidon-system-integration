#ifndef _ROS_test_roslib_comm_TypeNameChange2_h
#define _ROS_test_roslib_comm_TypeNameChange2_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "test_roslib_comm/SameSubMsg2.h"

namespace test_roslib_comm
{

  class TypeNameChange2 : public ros::Msg
  {
    public:
      typedef test_roslib_comm::SameSubMsg2 _a_type;
      _a_type a;

    TypeNameChange2():
      a()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->a.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->a.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "test_roslib_comm/TypeNameChange2"; };
    const char * getMD5(){ return "31a9992534c4d020bfc4045e7dc1a786"; };

  };

}
#endif
