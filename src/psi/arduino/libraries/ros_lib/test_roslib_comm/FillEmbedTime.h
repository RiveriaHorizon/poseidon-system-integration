#ifndef _ROS_test_roslib_comm_FillEmbedTime_h
#define _ROS_test_roslib_comm_FillEmbedTime_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "ros/time.h"
#include "ros/duration.h"
#include "std_msgs/String.h"

namespace test_roslib_comm
{

  class FillEmbedTime : public ros::Msg
  {
    public:
      typedef ros::Time _t_type;
      _t_type t;
      typedef ros::Duration _d_type;
      _d_type d;
      typedef std_msgs::String _str_msg_type;
      _str_msg_type str_msg;
      uint32_t str_msg_array_length;
      typedef std_msgs::String _str_msg_array_type;
      _str_msg_array_type st_str_msg_array;
      _str_msg_array_type * str_msg_array;
      typedef int32_t _i32_type;
      _i32_type i32;

    FillEmbedTime():
      t(),
      d(),
      str_msg(),
      str_msg_array_length(0), str_msg_array(NULL),
      i32(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->t.sec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->t.sec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->t.sec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->t.sec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->t.sec);
      *(outbuffer + offset + 0) = (this->t.nsec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->t.nsec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->t.nsec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->t.nsec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->t.nsec);
      *(outbuffer + offset + 0) = (this->d.sec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->d.sec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->d.sec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->d.sec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->d.sec);
      *(outbuffer + offset + 0) = (this->d.nsec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->d.nsec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->d.nsec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->d.nsec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->d.nsec);
      offset += this->str_msg.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->str_msg_array_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->str_msg_array_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->str_msg_array_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->str_msg_array_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->str_msg_array_length);
      for( uint32_t i = 0; i < str_msg_array_length; i++){
      offset += this->str_msg_array[i].serialize(outbuffer + offset);
      }
      union {
        int32_t real;
        uint32_t base;
      } u_i32;
      u_i32.real = this->i32;
      *(outbuffer + offset + 0) = (u_i32.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_i32.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_i32.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_i32.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->i32);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->t.sec =  ((uint32_t) (*(inbuffer + offset)));
      this->t.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->t.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->t.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->t.sec);
      this->t.nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->t.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->t.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->t.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->t.nsec);
      this->d.sec =  ((uint32_t) (*(inbuffer + offset)));
      this->d.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->d.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->d.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->d.sec);
      this->d.nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->d.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->d.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->d.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->d.nsec);
      offset += this->str_msg.deserialize(inbuffer + offset);
      uint32_t str_msg_array_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      str_msg_array_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      str_msg_array_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      str_msg_array_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->str_msg_array_length);
      if(str_msg_array_lengthT > str_msg_array_length)
        this->str_msg_array = (std_msgs::String*)realloc(this->str_msg_array, str_msg_array_lengthT * sizeof(std_msgs::String));
      str_msg_array_length = str_msg_array_lengthT;
      for( uint32_t i = 0; i < str_msg_array_length; i++){
      offset += this->st_str_msg_array.deserialize(inbuffer + offset);
        memcpy( &(this->str_msg_array[i]), &(this->st_str_msg_array), sizeof(std_msgs::String));
      }
      union {
        int32_t real;
        uint32_t base;
      } u_i32;
      u_i32.base = 0;
      u_i32.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_i32.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_i32.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_i32.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->i32 = u_i32.real;
      offset += sizeof(this->i32);
     return offset;
    }

    const char * getType(){ return "test_roslib_comm/FillEmbedTime"; };
    const char * getMD5(){ return "90e08039be001a899b8c20e680c289b0"; };

  };

}
#endif
