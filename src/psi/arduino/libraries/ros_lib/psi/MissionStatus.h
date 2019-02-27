#ifndef _ROS_psi_MissionStatus_h
#define _ROS_psi_MissionStatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace psi
{

  class MissionStatus : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef const char* _mission_status_type;
      _mission_status_type mission_status;

    MissionStatus():
      header(),
      mission_status("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      uint32_t length_mission_status = strlen(this->mission_status);
      varToArr(outbuffer + offset, length_mission_status);
      offset += 4;
      memcpy(outbuffer + offset, this->mission_status, length_mission_status);
      offset += length_mission_status;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t length_mission_status;
      arrToVar(length_mission_status, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_mission_status; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_mission_status-1]=0;
      this->mission_status = (char *)(inbuffer + offset-1);
      offset += length_mission_status;
     return offset;
    }

    const char * getType(){ return "psi/MissionStatus"; };
    const char * getMD5(){ return "1d0817c1b98aebe015bc37ce1a74ecc5"; };

  };

}
#endif
