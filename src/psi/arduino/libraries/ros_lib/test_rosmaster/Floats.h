#ifndef _ROS_test_rosmaster_Floats_h
#define _ROS_test_rosmaster_Floats_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace test_rosmaster
{

  class Floats : public ros::Msg
  {
    public:
      typedef float _float32_type;
      _float32_type float32;
      typedef float _float64_type;
      _float64_type float64;

    Floats():
      float32(0),
      float64(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_float32;
      u_float32.real = this->float32;
      *(outbuffer + offset + 0) = (u_float32.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_float32.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_float32.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_float32.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->float32);
      offset += serializeAvrFloat64(outbuffer + offset, this->float64);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_float32;
      u_float32.base = 0;
      u_float32.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_float32.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_float32.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_float32.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->float32 = u_float32.real;
      offset += sizeof(this->float32);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->float64));
     return offset;
    }

    const char * getType(){ return "test_rosmaster/Floats"; };
    const char * getMD5(){ return "1ee8aba2d870f75f2b5916e2cddbd928"; };

  };

}
#endif
