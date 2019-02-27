#ifndef _ROS_psi_CardinalDirection_h
#define _ROS_psi_CardinalDirection_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace psi
{

  class CardinalDirection : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef const char* _cardinal_direction_type;
      _cardinal_direction_type cardinal_direction;

    CardinalDirection():
      header(),
      cardinal_direction("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      uint32_t length_cardinal_direction = strlen(this->cardinal_direction);
      varToArr(outbuffer + offset, length_cardinal_direction);
      offset += 4;
      memcpy(outbuffer + offset, this->cardinal_direction, length_cardinal_direction);
      offset += length_cardinal_direction;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t length_cardinal_direction;
      arrToVar(length_cardinal_direction, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_cardinal_direction; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_cardinal_direction-1]=0;
      this->cardinal_direction = (char *)(inbuffer + offset-1);
      offset += length_cardinal_direction;
     return offset;
    }

    const char * getType(){ return "psi/CardinalDirection"; };
    const char * getMD5(){ return "f32ac4e9d9ebc1f679fcfd8da619c5b2"; };

  };

}
#endif
