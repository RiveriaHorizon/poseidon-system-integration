#ifndef _ROS_test_roslib_comm_SameSubMsg1_h
#define _ROS_test_roslib_comm_SameSubMsg1_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace test_roslib_comm
{

  class SameSubMsg1 : public ros::Msg
  {
    public:
      typedef int32_t _a_type;
      _a_type a;
      typedef float _b_type;
      _b_type b;
      typedef const char* _c_type;
      _c_type c;
      uint64_t d[10];
      uint32_t e_length;
      typedef float _e_type;
      _e_type st_e;
      _e_type * e;

    SameSubMsg1():
      a(0),
      b(0),
      c(""),
      d(),
      e_length(0), e(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_a;
      u_a.real = this->a;
      *(outbuffer + offset + 0) = (u_a.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_a.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_a.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_a.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->a);
      union {
        float real;
        uint32_t base;
      } u_b;
      u_b.real = this->b;
      *(outbuffer + offset + 0) = (u_b.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_b.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_b.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_b.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->b);
      uint32_t length_c = strlen(this->c);
      varToArr(outbuffer + offset, length_c);
      offset += 4;
      memcpy(outbuffer + offset, this->c, length_c);
      offset += length_c;
      for( uint32_t i = 0; i < 10; i++){
      *(outbuffer + offset + 0) = (this->d[i] >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->d[i] >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->d[i] >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->d[i] >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (this->d[i] >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (this->d[i] >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (this->d[i] >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (this->d[i] >> (8 * 7)) & 0xFF;
      offset += sizeof(this->d[i]);
      }
      *(outbuffer + offset + 0) = (this->e_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->e_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->e_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->e_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->e_length);
      for( uint32_t i = 0; i < e_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->e[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_a;
      u_a.base = 0;
      u_a.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_a.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_a.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_a.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->a = u_a.real;
      offset += sizeof(this->a);
      union {
        float real;
        uint32_t base;
      } u_b;
      u_b.base = 0;
      u_b.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_b.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_b.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_b.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->b = u_b.real;
      offset += sizeof(this->b);
      uint32_t length_c;
      arrToVar(length_c, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_c; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_c-1]=0;
      this->c = (char *)(inbuffer + offset-1);
      offset += length_c;
      for( uint32_t i = 0; i < 10; i++){
      this->d[i] =  ((uint64_t) (*(inbuffer + offset)));
      this->d[i] |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->d[i] |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->d[i] |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->d[i] |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      this->d[i] |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      this->d[i] |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      this->d[i] |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      offset += sizeof(this->d[i]);
      }
      uint32_t e_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      e_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      e_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      e_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->e_length);
      if(e_lengthT > e_length)
        this->e = (float*)realloc(this->e, e_lengthT * sizeof(float));
      e_length = e_lengthT;
      for( uint32_t i = 0; i < e_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_e));
        memcpy( &(this->e[i]), &(this->st_e), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return "test_roslib_comm/SameSubMsg1"; };
    const char * getMD5(){ return "49145a54e4be1a218629e518575a0bf3"; };

  };

}
#endif
