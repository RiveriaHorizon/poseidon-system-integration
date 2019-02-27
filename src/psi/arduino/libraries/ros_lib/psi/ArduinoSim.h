#ifndef _ROS_psi_ArduinoSim_h
#define _ROS_psi_ArduinoSim_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Twist.h"

namespace psi
{

  class ArduinoSim : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef geometry_msgs::Twist _cmd_vel_type;
      _cmd_vel_type cmd_vel;

    ArduinoSim():
      header(),
      cmd_vel()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->cmd_vel.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->cmd_vel.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "psi/ArduinoSim"; };
    const char * getMD5(){ return "8c340fa6f20a49eecf141f0b59dabe32"; };

  };

}
#endif
