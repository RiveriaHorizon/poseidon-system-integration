#ifndef _ROS_test_rospy_TestFixedArray_h
#define _ROS_test_rospy_TestFixedArray_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace test_rospy
{

  class TestFixedArray : public ros::Msg
  {
    public:
      float f32_1[1];
      float f32_3[3];
      float f64_1[1];
      float f64_3[3];
      int8_t i8_1[1];
      int8_t i8_3[3];
      uint8_t u8_1[1];
      uint8_t u8_3[3];
      int32_t i32_1[1];
      int32_t i32_3[3];
      uint32_t u32_1[1];
      uint32_t u32_3[3];
      char* s_1[1];
      char* s_3[3];
      bool b_1[1];
      bool b_3[3];

    TestFixedArray():
      f32_1(),
      f32_3(),
      f64_1(),
      f64_3(),
      i8_1(),
      i8_3(),
      u8_1(),
      u8_3(),
      i32_1(),
      i32_3(),
      u32_1(),
      u32_3(),
      s_1(),
      s_3(),
      b_1(),
      b_3()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      for( uint32_t i = 0; i < 1; i++){
      union {
        float real;
        uint32_t base;
      } u_f32_1i;
      u_f32_1i.real = this->f32_1[i];
      *(outbuffer + offset + 0) = (u_f32_1i.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_f32_1i.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_f32_1i.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_f32_1i.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->f32_1[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        float real;
        uint32_t base;
      } u_f32_3i;
      u_f32_3i.real = this->f32_3[i];
      *(outbuffer + offset + 0) = (u_f32_3i.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_f32_3i.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_f32_3i.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_f32_3i.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->f32_3[i]);
      }
      for( uint32_t i = 0; i < 1; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->f64_1[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->f64_3[i]);
      }
      for( uint32_t i = 0; i < 1; i++){
      union {
        int8_t real;
        uint8_t base;
      } u_i8_1i;
      u_i8_1i.real = this->i8_1[i];
      *(outbuffer + offset + 0) = (u_i8_1i.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->i8_1[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        int8_t real;
        uint8_t base;
      } u_i8_3i;
      u_i8_3i.real = this->i8_3[i];
      *(outbuffer + offset + 0) = (u_i8_3i.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->i8_3[i]);
      }
      for( uint32_t i = 0; i < 1; i++){
      *(outbuffer + offset + 0) = (this->u8_1[i] >> (8 * 0)) & 0xFF;
      offset += sizeof(this->u8_1[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      *(outbuffer + offset + 0) = (this->u8_3[i] >> (8 * 0)) & 0xFF;
      offset += sizeof(this->u8_3[i]);
      }
      for( uint32_t i = 0; i < 1; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_i32_1i;
      u_i32_1i.real = this->i32_1[i];
      *(outbuffer + offset + 0) = (u_i32_1i.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_i32_1i.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_i32_1i.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_i32_1i.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->i32_1[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_i32_3i;
      u_i32_3i.real = this->i32_3[i];
      *(outbuffer + offset + 0) = (u_i32_3i.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_i32_3i.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_i32_3i.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_i32_3i.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->i32_3[i]);
      }
      for( uint32_t i = 0; i < 1; i++){
      *(outbuffer + offset + 0) = (this->u32_1[i] >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->u32_1[i] >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->u32_1[i] >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->u32_1[i] >> (8 * 3)) & 0xFF;
      offset += sizeof(this->u32_1[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      *(outbuffer + offset + 0) = (this->u32_3[i] >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->u32_3[i] >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->u32_3[i] >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->u32_3[i] >> (8 * 3)) & 0xFF;
      offset += sizeof(this->u32_3[i]);
      }
      for( uint32_t i = 0; i < 1; i++){
      uint32_t length_s_1i = strlen(this->s_1[i]);
      varToArr(outbuffer + offset, length_s_1i);
      offset += 4;
      memcpy(outbuffer + offset, this->s_1[i], length_s_1i);
      offset += length_s_1i;
      }
      for( uint32_t i = 0; i < 3; i++){
      uint32_t length_s_3i = strlen(this->s_3[i]);
      varToArr(outbuffer + offset, length_s_3i);
      offset += 4;
      memcpy(outbuffer + offset, this->s_3[i], length_s_3i);
      offset += length_s_3i;
      }
      for( uint32_t i = 0; i < 1; i++){
      union {
        bool real;
        uint8_t base;
      } u_b_1i;
      u_b_1i.real = this->b_1[i];
      *(outbuffer + offset + 0) = (u_b_1i.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->b_1[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        bool real;
        uint8_t base;
      } u_b_3i;
      u_b_3i.real = this->b_3[i];
      *(outbuffer + offset + 0) = (u_b_3i.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->b_3[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      for( uint32_t i = 0; i < 1; i++){
      union {
        float real;
        uint32_t base;
      } u_f32_1i;
      u_f32_1i.base = 0;
      u_f32_1i.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_f32_1i.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_f32_1i.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_f32_1i.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->f32_1[i] = u_f32_1i.real;
      offset += sizeof(this->f32_1[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        float real;
        uint32_t base;
      } u_f32_3i;
      u_f32_3i.base = 0;
      u_f32_3i.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_f32_3i.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_f32_3i.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_f32_3i.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->f32_3[i] = u_f32_3i.real;
      offset += sizeof(this->f32_3[i]);
      }
      for( uint32_t i = 0; i < 1; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->f64_1[i]));
      }
      for( uint32_t i = 0; i < 3; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->f64_3[i]));
      }
      for( uint32_t i = 0; i < 1; i++){
      union {
        int8_t real;
        uint8_t base;
      } u_i8_1i;
      u_i8_1i.base = 0;
      u_i8_1i.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->i8_1[i] = u_i8_1i.real;
      offset += sizeof(this->i8_1[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        int8_t real;
        uint8_t base;
      } u_i8_3i;
      u_i8_3i.base = 0;
      u_i8_3i.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->i8_3[i] = u_i8_3i.real;
      offset += sizeof(this->i8_3[i]);
      }
      for( uint32_t i = 0; i < 1; i++){
      this->u8_1[i] =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->u8_1[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      this->u8_3[i] =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->u8_3[i]);
      }
      for( uint32_t i = 0; i < 1; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_i32_1i;
      u_i32_1i.base = 0;
      u_i32_1i.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_i32_1i.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_i32_1i.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_i32_1i.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->i32_1[i] = u_i32_1i.real;
      offset += sizeof(this->i32_1[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_i32_3i;
      u_i32_3i.base = 0;
      u_i32_3i.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_i32_3i.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_i32_3i.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_i32_3i.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->i32_3[i] = u_i32_3i.real;
      offset += sizeof(this->i32_3[i]);
      }
      for( uint32_t i = 0; i < 1; i++){
      this->u32_1[i] =  ((uint32_t) (*(inbuffer + offset)));
      this->u32_1[i] |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->u32_1[i] |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->u32_1[i] |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->u32_1[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      this->u32_3[i] =  ((uint32_t) (*(inbuffer + offset)));
      this->u32_3[i] |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->u32_3[i] |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->u32_3[i] |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->u32_3[i]);
      }
      for( uint32_t i = 0; i < 1; i++){
      uint32_t length_s_1i;
      arrToVar(length_s_1i, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_s_1i; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_s_1i-1]=0;
      this->s_1[i] = (char *)(inbuffer + offset-1);
      offset += length_s_1i;
      }
      for( uint32_t i = 0; i < 3; i++){
      uint32_t length_s_3i;
      arrToVar(length_s_3i, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_s_3i; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_s_3i-1]=0;
      this->s_3[i] = (char *)(inbuffer + offset-1);
      offset += length_s_3i;
      }
      for( uint32_t i = 0; i < 1; i++){
      union {
        bool real;
        uint8_t base;
      } u_b_1i;
      u_b_1i.base = 0;
      u_b_1i.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->b_1[i] = u_b_1i.real;
      offset += sizeof(this->b_1[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        bool real;
        uint8_t base;
      } u_b_3i;
      u_b_3i.base = 0;
      u_b_3i.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->b_3[i] = u_b_3i.real;
      offset += sizeof(this->b_3[i]);
      }
     return offset;
    }

    const char * getType(){ return "test_rospy/TestFixedArray"; };
    const char * getMD5(){ return "1557473dc09f1a01a00123a713c822a7"; };

  };

}
#endif
