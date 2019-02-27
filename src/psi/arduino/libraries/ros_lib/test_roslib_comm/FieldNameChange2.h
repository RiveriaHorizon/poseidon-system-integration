#ifndef _ROS_test_roslib_comm_FieldNameChange2_h
#define _ROS_test_roslib_comm_FieldNameChange2_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "test_roslib_comm/SameSubMsg1.h"

namespace test_roslib_comm
{

  class FieldNameChange2 : public ros::Msg
  {
    public:
      typedef test_roslib_comm::SameSubMsg1 _b_type;
      _b_type b;

    FieldNameChange2():
      b()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->b.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->b.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "test_roslib_comm/FieldNameChange2"; };
    const char * getMD5(){ return "dde34a89b93706fc183fd13c24ae090a"; };

  };

}
#endif
