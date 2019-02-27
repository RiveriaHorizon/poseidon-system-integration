#ifndef _ROS_test_rospy_HeaderVal_h
#define _ROS_test_rospy_HeaderVal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace test_rospy
{

  class HeaderVal : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef const char* _val_type;
      _val_type val;

    HeaderVal():
      header(),
      val("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      uint32_t length_val = strlen(this->val);
      varToArr(outbuffer + offset, length_val);
      offset += 4;
      memcpy(outbuffer + offset, this->val, length_val);
      offset += length_val;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t length_val;
      arrToVar(length_val, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_val; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_val-1]=0;
      this->val = (char *)(inbuffer + offset-1);
      offset += length_val;
     return offset;
    }

    const char * getType(){ return "test_rospy/HeaderVal"; };
    const char * getMD5(){ return "c3262d64205f82361bc7aa4173b8fe64"; };

  };

}
#endif
