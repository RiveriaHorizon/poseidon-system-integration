#ifndef _ROS_psi_JoystickInput_h
#define _ROS_psi_JoystickInput_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace psi
{

  class JoystickInput : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef uint16_t _x_input_type;
      _x_input_type x_input;
      typedef uint16_t _y_input_type;
      _y_input_type y_input;

    JoystickInput():
      header(),
      x_input(0),
      y_input(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->x_input >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->x_input >> (8 * 1)) & 0xFF;
      offset += sizeof(this->x_input);
      *(outbuffer + offset + 0) = (this->y_input >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->y_input >> (8 * 1)) & 0xFF;
      offset += sizeof(this->y_input);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      this->x_input =  ((uint16_t) (*(inbuffer + offset)));
      this->x_input |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->x_input);
      this->y_input =  ((uint16_t) (*(inbuffer + offset)));
      this->y_input |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->y_input);
     return offset;
    }

    const char * getType(){ return "psi/JoystickInput"; };
    const char * getMD5(){ return "3f6355fe36a8967a564ae2ff13f66a24"; };

  };

}
#endif
