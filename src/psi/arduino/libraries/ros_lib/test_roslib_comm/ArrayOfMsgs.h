#ifndef _ROS_test_roslib_comm_ArrayOfMsgs_h
#define _ROS_test_roslib_comm_ArrayOfMsgs_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/String.h"
#include "std_msgs/Time.h"
#include "std_msgs/MultiArrayLayout.h"

namespace test_roslib_comm
{

  class ArrayOfMsgs : public ros::Msg
  {
    public:
      uint32_t strings_length;
      typedef std_msgs::String _strings_type;
      _strings_type st_strings;
      _strings_type * strings;
      uint32_t times_length;
      typedef std_msgs::Time _times_type;
      _times_type st_times;
      _times_type * times;
      uint32_t muls_length;
      typedef std_msgs::MultiArrayLayout _muls_type;
      _muls_type st_muls;
      _muls_type * muls;

    ArrayOfMsgs():
      strings_length(0), strings(NULL),
      times_length(0), times(NULL),
      muls_length(0), muls(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->strings_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->strings_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->strings_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->strings_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->strings_length);
      for( uint32_t i = 0; i < strings_length; i++){
      offset += this->strings[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->times_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->times_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->times_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->times_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->times_length);
      for( uint32_t i = 0; i < times_length; i++){
      offset += this->times[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->muls_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->muls_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->muls_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->muls_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->muls_length);
      for( uint32_t i = 0; i < muls_length; i++){
      offset += this->muls[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t strings_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      strings_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      strings_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      strings_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->strings_length);
      if(strings_lengthT > strings_length)
        this->strings = (std_msgs::String*)realloc(this->strings, strings_lengthT * sizeof(std_msgs::String));
      strings_length = strings_lengthT;
      for( uint32_t i = 0; i < strings_length; i++){
      offset += this->st_strings.deserialize(inbuffer + offset);
        memcpy( &(this->strings[i]), &(this->st_strings), sizeof(std_msgs::String));
      }
      uint32_t times_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      times_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      times_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      times_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->times_length);
      if(times_lengthT > times_length)
        this->times = (std_msgs::Time*)realloc(this->times, times_lengthT * sizeof(std_msgs::Time));
      times_length = times_lengthT;
      for( uint32_t i = 0; i < times_length; i++){
      offset += this->st_times.deserialize(inbuffer + offset);
        memcpy( &(this->times[i]), &(this->st_times), sizeof(std_msgs::Time));
      }
      uint32_t muls_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      muls_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      muls_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      muls_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->muls_length);
      if(muls_lengthT > muls_length)
        this->muls = (std_msgs::MultiArrayLayout*)realloc(this->muls, muls_lengthT * sizeof(std_msgs::MultiArrayLayout));
      muls_length = muls_lengthT;
      for( uint32_t i = 0; i < muls_length; i++){
      offset += this->st_muls.deserialize(inbuffer + offset);
        memcpy( &(this->muls[i]), &(this->st_muls), sizeof(std_msgs::MultiArrayLayout));
      }
     return offset;
    }

    const char * getType(){ return "test_roslib_comm/ArrayOfMsgs"; };
    const char * getMD5(){ return "1f4cf3ffabe2555a0cfe19c974f01a01"; };

  };

}
#endif
