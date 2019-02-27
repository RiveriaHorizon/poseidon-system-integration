#ifndef _ROS_test_rospy_ArrayVal_h
#define _ROS_test_rospy_ArrayVal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "test_rospy/Val.h"

namespace test_rospy
{

  class ArrayVal : public ros::Msg
  {
    public:
      uint32_t vals_length;
      typedef test_rospy::Val _vals_type;
      _vals_type st_vals;
      _vals_type * vals;

    ArrayVal():
      vals_length(0), vals(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->vals_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->vals_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->vals_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->vals_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->vals_length);
      for( uint32_t i = 0; i < vals_length; i++){
      offset += this->vals[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t vals_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      vals_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      vals_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      vals_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->vals_length);
      if(vals_lengthT > vals_length)
        this->vals = (test_rospy::Val*)realloc(this->vals, vals_lengthT * sizeof(test_rospy::Val));
      vals_length = vals_lengthT;
      for( uint32_t i = 0; i < vals_length; i++){
      offset += this->st_vals.deserialize(inbuffer + offset);
        memcpy( &(this->vals[i]), &(this->st_vals), sizeof(test_rospy::Val));
      }
     return offset;
    }

    const char * getType(){ return "test_rospy/ArrayVal"; };
    const char * getMD5(){ return "94e095e6a59bceb3466e4b23c166732e"; };

  };

}
#endif
