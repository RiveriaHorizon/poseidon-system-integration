#ifndef _ROS_test_roslib_comm_HeaderTest_h
#define _ROS_test_roslib_comm_HeaderTest_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace test_roslib_comm
{

  class HeaderTest : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef int32_t _i32_type;
      _i32_type i32;

    HeaderTest():
      header(),
      i32(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_i32;
      u_i32.real = this->i32;
      *(outbuffer + offset + 0) = (u_i32.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_i32.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_i32.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_i32.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->i32);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_i32;
      u_i32.base = 0;
      u_i32.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_i32.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_i32.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_i32.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->i32 = u_i32.real;
      offset += sizeof(this->i32);
     return offset;
    }

    const char * getType(){ return "test_roslib_comm/HeaderTest"; };
    const char * getMD5(){ return "4426b8931bec8509041d64c6a89b54a2"; };

  };

}
#endif
