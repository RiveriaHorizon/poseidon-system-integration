#ifndef _ROS_psi_ArmFeedback_h
#define _ROS_psi_ArmFeedback_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace psi
{

  class ArmFeedback : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef const char* _wormgear_status_type;
      _wormgear_status_type wormgear_status;

    ArmFeedback():
      header(),
      wormgear_status("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      uint32_t length_wormgear_status = strlen(this->wormgear_status);
      varToArr(outbuffer + offset, length_wormgear_status);
      offset += 4;
      memcpy(outbuffer + offset, this->wormgear_status, length_wormgear_status);
      offset += length_wormgear_status;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t length_wormgear_status;
      arrToVar(length_wormgear_status, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_wormgear_status; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_wormgear_status-1]=0;
      this->wormgear_status = (char *)(inbuffer + offset-1);
      offset += length_wormgear_status;
     return offset;
    }

    const char * getType(){ return "psi/ArmFeedback"; };
    const char * getMD5(){ return "168ac7a231323f92f45fefc31296bd2c"; };

  };

}
#endif
