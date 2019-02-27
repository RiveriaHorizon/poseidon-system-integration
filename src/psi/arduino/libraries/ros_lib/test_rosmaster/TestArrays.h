#ifndef _ROS_test_rosmaster_TestArrays_h
#define _ROS_test_rosmaster_TestArrays_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "ros/time.h"
#include "test_rosmaster/TestString.h"

namespace test_rosmaster
{

  class TestArrays : public ros::Msg
  {
    public:
      typedef const char* _caller_id_type;
      _caller_id_type caller_id;
      typedef const char* _orig_caller_id_type;
      _orig_caller_id_type orig_caller_id;
      uint32_t int32_array_length;
      typedef int32_t _int32_array_type;
      _int32_array_type st_int32_array;
      _int32_array_type * int32_array;
      uint32_t float32_array_length;
      typedef float _float32_array_type;
      _float32_array_type st_float32_array;
      _float32_array_type * float32_array;
      uint32_t time_array_length;
      typedef ros::Time _time_array_type;
      _time_array_type st_time_array;
      _time_array_type * time_array;
      uint32_t test_string_array_length;
      typedef test_rosmaster::TestString _test_string_array_type;
      _test_string_array_type st_test_string_array;
      _test_string_array_type * test_string_array;

    TestArrays():
      caller_id(""),
      orig_caller_id(""),
      int32_array_length(0), int32_array(NULL),
      float32_array_length(0), float32_array(NULL),
      time_array_length(0), time_array(NULL),
      test_string_array_length(0), test_string_array(NULL)
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
      *(outbuffer + offset + 0) = (this->int32_array_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->int32_array_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->int32_array_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->int32_array_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->int32_array_length);
      for( uint32_t i = 0; i < int32_array_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_int32_arrayi;
      u_int32_arrayi.real = this->int32_array[i];
      *(outbuffer + offset + 0) = (u_int32_arrayi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_int32_arrayi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_int32_arrayi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_int32_arrayi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->int32_array[i]);
      }
      *(outbuffer + offset + 0) = (this->float32_array_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->float32_array_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->float32_array_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->float32_array_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->float32_array_length);
      for( uint32_t i = 0; i < float32_array_length; i++){
      union {
        float real;
        uint32_t base;
      } u_float32_arrayi;
      u_float32_arrayi.real = this->float32_array[i];
      *(outbuffer + offset + 0) = (u_float32_arrayi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_float32_arrayi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_float32_arrayi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_float32_arrayi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->float32_array[i]);
      }
      *(outbuffer + offset + 0) = (this->time_array_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->time_array_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->time_array_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->time_array_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->time_array_length);
      for( uint32_t i = 0; i < time_array_length; i++){
      *(outbuffer + offset + 0) = (this->time_array[i].sec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->time_array[i].sec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->time_array[i].sec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->time_array[i].sec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->time_array[i].sec);
      *(outbuffer + offset + 0) = (this->time_array[i].nsec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->time_array[i].nsec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->time_array[i].nsec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->time_array[i].nsec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->time_array[i].nsec);
      }
      *(outbuffer + offset + 0) = (this->test_string_array_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->test_string_array_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->test_string_array_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->test_string_array_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->test_string_array_length);
      for( uint32_t i = 0; i < test_string_array_length; i++){
      offset += this->test_string_array[i].serialize(outbuffer + offset);
      }
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
      uint32_t int32_array_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      int32_array_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      int32_array_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      int32_array_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->int32_array_length);
      if(int32_array_lengthT > int32_array_length)
        this->int32_array = (int32_t*)realloc(this->int32_array, int32_array_lengthT * sizeof(int32_t));
      int32_array_length = int32_array_lengthT;
      for( uint32_t i = 0; i < int32_array_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_int32_array;
      u_st_int32_array.base = 0;
      u_st_int32_array.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_int32_array.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_int32_array.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_int32_array.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_int32_array = u_st_int32_array.real;
      offset += sizeof(this->st_int32_array);
        memcpy( &(this->int32_array[i]), &(this->st_int32_array), sizeof(int32_t));
      }
      uint32_t float32_array_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      float32_array_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      float32_array_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      float32_array_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->float32_array_length);
      if(float32_array_lengthT > float32_array_length)
        this->float32_array = (float*)realloc(this->float32_array, float32_array_lengthT * sizeof(float));
      float32_array_length = float32_array_lengthT;
      for( uint32_t i = 0; i < float32_array_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_float32_array;
      u_st_float32_array.base = 0;
      u_st_float32_array.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_float32_array.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_float32_array.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_float32_array.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_float32_array = u_st_float32_array.real;
      offset += sizeof(this->st_float32_array);
        memcpy( &(this->float32_array[i]), &(this->st_float32_array), sizeof(float));
      }
      uint32_t time_array_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      time_array_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      time_array_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      time_array_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->time_array_length);
      if(time_array_lengthT > time_array_length)
        this->time_array = (ros::Time*)realloc(this->time_array, time_array_lengthT * sizeof(ros::Time));
      time_array_length = time_array_lengthT;
      for( uint32_t i = 0; i < time_array_length; i++){
      this->st_time_array.sec =  ((uint32_t) (*(inbuffer + offset)));
      this->st_time_array.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->st_time_array.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->st_time_array.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->st_time_array.sec);
      this->st_time_array.nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->st_time_array.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->st_time_array.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->st_time_array.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->st_time_array.nsec);
        memcpy( &(this->time_array[i]), &(this->st_time_array), sizeof(ros::Time));
      }
      uint32_t test_string_array_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      test_string_array_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      test_string_array_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      test_string_array_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->test_string_array_length);
      if(test_string_array_lengthT > test_string_array_length)
        this->test_string_array = (test_rosmaster::TestString*)realloc(this->test_string_array, test_string_array_lengthT * sizeof(test_rosmaster::TestString));
      test_string_array_length = test_string_array_lengthT;
      for( uint32_t i = 0; i < test_string_array_length; i++){
      offset += this->st_test_string_array.deserialize(inbuffer + offset);
        memcpy( &(this->test_string_array[i]), &(this->st_test_string_array), sizeof(test_rosmaster::TestString));
      }
     return offset;
    }

    const char * getType(){ return "test_rosmaster/TestArrays"; };
    const char * getMD5(){ return "4cc9b5e2cebe791aa3e994f5bc159eb6"; };

  };

}
#endif
