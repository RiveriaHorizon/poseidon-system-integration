#ifndef _ROS_test_rospy_Val_h
#define _ROS_test_rospy_Val_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace test_rospy
{

  class Val : public ros::Msg
  {
    public:
      typedef const char* _val_type;
      _val_type val;

    Val():
      val("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
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

    const char * getType(){ return "test_rospy/Val"; };
    const char * getMD5(){ return "c45577ce53559408f0f69fe465be7c70"; };

  };

}
#endif
