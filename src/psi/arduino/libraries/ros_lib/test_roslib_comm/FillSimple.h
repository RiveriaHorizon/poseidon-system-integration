#ifndef _ROS_test_roslib_comm_FillSimple_h
#define _ROS_test_roslib_comm_FillSimple_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace test_roslib_comm
{

  class FillSimple : public ros::Msg
  {
    public:
      typedef int32_t _i32_type;
      _i32_type i32;
      typedef const char* _str_type;
      _str_type str;
      uint32_t i32_array_length;
      typedef int32_t _i32_array_type;
      _i32_array_type st_i32_array;
      _i32_array_type * i32_array;
      typedef bool _b_type;
      _b_type b;

    FillSimple():
      i32(0),
      str(""),
      i32_array_length(0), i32_array(NULL),
      b(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
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
      uint32_t length_str = strlen(this->str);
      varToArr(outbuffer + offset, length_str);
      offset += 4;
      memcpy(outbuffer + offset, this->str, length_str);
      offset += length_str;
      *(outbuffer + offset + 0) = (this->i32_array_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->i32_array_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->i32_array_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->i32_array_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->i32_array_length);
      for( uint32_t i = 0; i < i32_array_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_i32_arrayi;
      u_i32_arrayi.real = this->i32_array[i];
      *(outbuffer + offset + 0) = (u_i32_arrayi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_i32_arrayi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_i32_arrayi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_i32_arrayi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->i32_array[i]);
      }
      union {
        bool real;
        uint8_t base;
      } u_b;
      u_b.real = this->b;
      *(outbuffer + offset + 0) = (u_b.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->b);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
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
      uint32_t length_str;
      arrToVar(length_str, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_str; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_str-1]=0;
      this->str = (char *)(inbuffer + offset-1);
      offset += length_str;
      uint32_t i32_array_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      i32_array_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      i32_array_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      i32_array_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->i32_array_length);
      if(i32_array_lengthT > i32_array_length)
        this->i32_array = (int32_t*)realloc(this->i32_array, i32_array_lengthT * sizeof(int32_t));
      i32_array_length = i32_array_lengthT;
      for( uint32_t i = 0; i < i32_array_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_i32_array;
      u_st_i32_array.base = 0;
      u_st_i32_array.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_i32_array.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_i32_array.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_i32_array.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_i32_array = u_st_i32_array.real;
      offset += sizeof(this->st_i32_array);
        memcpy( &(this->i32_array[i]), &(this->st_i32_array), sizeof(int32_t));
      }
      union {
        bool real;
        uint8_t base;
      } u_b;
      u_b.base = 0;
      u_b.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->b = u_b.real;
      offset += sizeof(this->b);
     return offset;
    }

    const char * getType(){ return "test_roslib_comm/FillSimple"; };
    const char * getMD5(){ return "da04a60d03fa22f7d301f9bd5f9a08ab"; };

  };

}
#endif
