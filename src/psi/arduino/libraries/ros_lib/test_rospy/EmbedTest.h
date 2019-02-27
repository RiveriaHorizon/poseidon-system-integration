#ifndef _ROS_test_rospy_EmbedTest_h
#define _ROS_test_rospy_EmbedTest_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/String.h"
#include "std_msgs/Int32.h"
#include "test_rospy/Val.h"
#include "test_rospy/ArrayVal.h"

namespace test_rospy
{

  class EmbedTest : public ros::Msg
  {
    public:
      typedef std_msgs::String _str1_type;
      _str1_type str1;
      typedef std_msgs::Int32 _int1_type;
      _int1_type int1;
      uint32_t ints_length;
      typedef std_msgs::Int32 _ints_type;
      _ints_type st_ints;
      _ints_type * ints;
      typedef test_rospy::Val _val_type;
      _val_type val;
      uint32_t vals_length;
      typedef test_rospy::Val _vals_type;
      _vals_type st_vals;
      _vals_type * vals;
      uint32_t arrayval_length;
      typedef test_rospy::ArrayVal _arrayval_type;
      _arrayval_type st_arrayval;
      _arrayval_type * arrayval;

    EmbedTest():
      str1(),
      int1(),
      ints_length(0), ints(NULL),
      val(),
      vals_length(0), vals(NULL),
      arrayval_length(0), arrayval(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->str1.serialize(outbuffer + offset);
      offset += this->int1.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->ints_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->ints_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->ints_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->ints_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ints_length);
      for( uint32_t i = 0; i < ints_length; i++){
      offset += this->ints[i].serialize(outbuffer + offset);
      }
      offset += this->val.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->vals_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->vals_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->vals_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->vals_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->vals_length);
      for( uint32_t i = 0; i < vals_length; i++){
      offset += this->vals[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->arrayval_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->arrayval_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->arrayval_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->arrayval_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->arrayval_length);
      for( uint32_t i = 0; i < arrayval_length; i++){
      offset += this->arrayval[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->str1.deserialize(inbuffer + offset);
      offset += this->int1.deserialize(inbuffer + offset);
      uint32_t ints_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      ints_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      ints_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      ints_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->ints_length);
      if(ints_lengthT > ints_length)
        this->ints = (std_msgs::Int32*)realloc(this->ints, ints_lengthT * sizeof(std_msgs::Int32));
      ints_length = ints_lengthT;
      for( uint32_t i = 0; i < ints_length; i++){
      offset += this->st_ints.deserialize(inbuffer + offset);
        memcpy( &(this->ints[i]), &(this->st_ints), sizeof(std_msgs::Int32));
      }
      offset += this->val.deserialize(inbuffer + offset);
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
      uint32_t arrayval_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      arrayval_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      arrayval_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      arrayval_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->arrayval_length);
      if(arrayval_lengthT > arrayval_length)
        this->arrayval = (test_rospy::ArrayVal*)realloc(this->arrayval, arrayval_lengthT * sizeof(test_rospy::ArrayVal));
      arrayval_length = arrayval_lengthT;
      for( uint32_t i = 0; i < arrayval_length; i++){
      offset += this->st_arrayval.deserialize(inbuffer + offset);
        memcpy( &(this->arrayval[i]), &(this->st_arrayval), sizeof(test_rospy::ArrayVal));
      }
     return offset;
    }

    const char * getType(){ return "test_rospy/EmbedTest"; };
    const char * getMD5(){ return "f8b1fc6a0f70f541c9d6bd2886b9e249"; };

  };

}
#endif
