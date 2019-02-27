#ifndef _ROS_test_rosmaster_TestHeader_h
#define _ROS_test_rosmaster_TestHeader_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace test_rosmaster
{

  class TestHeader : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef const char* _caller_id_type;
      _caller_id_type caller_id;
      typedef const char* _orig_caller_id_type;
      _orig_caller_id_type orig_caller_id;
      typedef int8_t _auto_header_type;
      _auto_header_type auto_header;

    TestHeader():
      header(),
      caller_id(""),
      orig_caller_id(""),
      auto_header(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      uint32_t length_caller_id = strlen(this->caller_id);
      varToArr(outbuffer + offset, length_caller_id);
      offset += 4;
      memcpy(outbuffer + offset, this->caller_id, length_caller_id);
      offset += length_caller_id;
      uint32_t length_orig_caller_id = strlen(this->orig_caller_id);
      varToArr(outbuffer + offset, length_orig_caller_id);
      offset += 4;
      memcpy(outbuffer + offset, this->orig_caller_id, length_orig_caller_id);
      offset += length_orig_caller_id;
      union {
        int8_t real;
        uint8_t base;
      } u_auto_header;
      u_auto_header.real = this->auto_header;
      *(outbuffer + offset + 0) = (u_auto_header.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->auto_header);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t length_caller_id;
      arrToVar(length_caller_id, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_caller_id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_caller_id-1]=0;
      this->caller_id = (char *)(inbuffer + offset-1);
      offset += length_caller_id;
      uint32_t length_orig_caller_id;
      arrToVar(length_orig_caller_id, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_orig_caller_id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_orig_caller_id-1]=0;
      this->orig_caller_id = (char *)(inbuffer + offset-1);
      offset += length_orig_caller_id;
      union {
        int8_t real;
        uint8_t base;
      } u_auto_header;
      u_auto_header.base = 0;
      u_auto_header.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->auto_header = u_auto_header.real;
      offset += sizeof(this->auto_header);
     return offset;
    }

    const char * getType(){ return "test_rosmaster/TestHeader"; };
    const char * getMD5(){ return "4b5a00f536da2f756ba6aebcf795a967"; };

  };

}
#endif
