#ifndef _ROS_test_rosmaster_TestString_h
#define _ROS_test_rosmaster_TestString_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace test_rosmaster
{

  class TestString : public ros::Msg
  {
    public:
      typedef const char* _caller_id_type;
      _caller_id_type caller_id;
      typedef const char* _orig_caller_id_type;
      _orig_caller_id_type orig_caller_id;
      typedef const char* _data_type;
      _data_type data;

    TestString():
      caller_id(""),
      orig_caller_id(""),
      data("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
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
      uint32_t length_data = strlen(this->data);
      varToArr(outbuffer + offset, length_data);
      offset += 4;
      memcpy(outbuffer + offset, this->data, length_data);
      offset += length_data;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
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
      uint32_t length_data;
      arrToVar(length_data, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_data; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_data-1]=0;
      this->data = (char *)(inbuffer + offset-1);
      offset += length_data;
     return offset;
    }

    const char * getType(){ return "test_rosmaster/TestString"; };
    const char * getMD5(){ return "334ff4377be93faa44ebc66d23d40fd3"; };

  };

}
#endif
