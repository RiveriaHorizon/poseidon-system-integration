#ifndef _ROS_psi_DirectionError_h
#define _ROS_psi_DirectionError_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace psi
{

  class DirectionError : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef float _direction_error_type;
      _direction_error_type direction_error;

    DirectionError():
      header(),
      direction_error(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_direction_error;
      u_direction_error.real = this->direction_error;
      *(outbuffer + offset + 0) = (u_direction_error.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_direction_error.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_direction_error.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_direction_error.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->direction_error);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_direction_error;
      u_direction_error.base = 0;
      u_direction_error.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_direction_error.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_direction_error.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_direction_error.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->direction_error = u_direction_error.real;
      offset += sizeof(this->direction_error);
     return offset;
    }

    const char * getType(){ return "psi/DirectionError"; };
    const char * getMD5(){ return "7039887fa109833bc9d7015d43421eb9"; };

  };

}
#endif
