#ifndef _ROS_test_rostopic_Simple_h
#define _ROS_test_rostopic_Simple_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace test_rostopic
{

  class Simple : public ros::Msg
  {
    public:
      typedef int8_t _b_type;
      _b_type b;
      typedef int16_t _int16_type;
      _int16_type int16;
      typedef int32_t _int32_type;
      _int32_type int32;
      typedef int64_t _int64_type;
      _int64_type int64;
      typedef uint8_t _c_type;
      _c_type c;
      typedef uint16_t _uint16_type;
      _uint16_type uint16;
      typedef uint32_t _uint32_type;
      _uint32_type uint32;
      typedef uint64_t _uint64_type;
      _uint64_type uint64;
      typedef const char* _str_type;
      _str_type str;

    Simple():
      b(0),
      int16(0),
      int32(0),
      int64(0),
      c(0),
      uint16(0),
      uint32(0),
      uint64(0),
      str("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_b;
      u_b.real = this->b;
      *(outbuffer + offset + 0) = (u_b.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->b);
      union {
        int16_t real;
        uint16_t base;
      } u_int16;
      u_int16.real = this->int16;
      *(outbuffer + offset + 0) = (u_int16.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_int16.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->int16);
      union {
        int32_t real;
        uint32_t base;
      } u_int32;
      u_int32.real = this->int32;
      *(outbuffer + offset + 0) = (u_int32.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_int32.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_int32.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_int32.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->int32);
      union {
        int64_t real;
        uint64_t base;
      } u_int64;
      u_int64.real = this->int64;
      *(outbuffer + offset + 0) = (u_int64.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_int64.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_int64.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_int64.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_int64.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_int64.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_int64.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_int64.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->int64);
      *(outbuffer + offset + 0) = (this->c >> (8 * 0)) & 0xFF;
      offset += sizeof(this->c);
      *(outbuffer + offset + 0) = (this->uint16 >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->uint16 >> (8 * 1)) & 0xFF;
      offset += sizeof(this->uint16);
      *(outbuffer + offset + 0) = (this->uint32 >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->uint32 >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->uint32 >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->uint32 >> (8 * 3)) & 0xFF;
      offset += sizeof(this->uint32);
      *(outbuffer + offset + 0) = (this->uint64 >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->uint64 >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->uint64 >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->uint64 >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (this->uint64 >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (this->uint64 >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (this->uint64 >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (this->uint64 >> (8 * 7)) & 0xFF;
      offset += sizeof(this->uint64);
      uint32_t length_str = strlen(this->str);
      varToArr(outbuffer + offset, length_str);
      offset += 4;
      memcpy(outbuffer + offset, this->str, length_str);
      offset += length_str;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_b;
      u_b.base = 0;
      u_b.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->b = u_b.real;
      offset += sizeof(this->b);
      union {
        int16_t real;
        uint16_t base;
      } u_int16;
      u_int16.base = 0;
      u_int16.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_int16.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->int16 = u_int16.real;
      offset += sizeof(this->int16);
      union {
        int32_t real;
        uint32_t base;
      } u_int32;
      u_int32.base = 0;
      u_int32.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_int32.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_int32.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_int32.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->int32 = u_int32.real;
      offset += sizeof(this->int32);
      union {
        int64_t real;
        uint64_t base;
      } u_int64;
      u_int64.base = 0;
      u_int64.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_int64.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_int64.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_int64.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_int64.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_int64.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_int64.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_int64.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->int64 = u_int64.real;
      offset += sizeof(this->int64);
      this->c =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->c);
      this->uint16 =  ((uint16_t) (*(inbuffer + offset)));
      this->uint16 |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->uint16);
      this->uint32 =  ((uint32_t) (*(inbuffer + offset)));
      this->uint32 |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->uint32 |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->uint32 |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->uint32);
      this->uint64 =  ((uint64_t) (*(inbuffer + offset)));
      this->uint64 |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->uint64 |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->uint64 |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->uint64 |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      this->uint64 |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      this->uint64 |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      this->uint64 |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      offset += sizeof(this->uint64);
      uint32_t length_str;
      arrToVar(length_str, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_str; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_str-1]=0;
      this->str = (char *)(inbuffer + offset-1);
      offset += length_str;
     return offset;
    }

    const char * getType(){ return "test_rostopic/Simple"; };
    const char * getMD5(){ return "c9940b1313e61fed87cd22c50742578f"; };

  };

}
#endif
