#ifndef _ROS_test_roslib_comm_TypeNameChangeComplex2_h
#define _ROS_test_roslib_comm_TypeNameChangeComplex2_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "test_roslib_comm/SameSubMsg2.h"
#include "test_roslib_comm/SameSubMsg3.h"

namespace test_roslib_comm
{

  class TypeNameChangeComplex2 : public ros::Msg
  {
    public:
      uint32_t a_length;
      typedef test_roslib_comm::SameSubMsg2 _a_type;
      _a_type st_a;
      _a_type * a;
      test_roslib_comm::SameSubMsg3 b[10];

    TypeNameChangeComplex2():
      a_length(0), a(NULL),
      b()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->a_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->a_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->a_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->a_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->a_length);
      for( uint32_t i = 0; i < a_length; i++){
      offset += this->a[i].serialize(outbuffer + offset);
      }
      for( uint32_t i = 0; i < 10; i++){
      offset += this->b[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t a_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      a_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      a_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      a_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->a_length);
      if(a_lengthT > a_length)
        this->a = (test_roslib_comm::SameSubMsg2*)realloc(this->a, a_lengthT * sizeof(test_roslib_comm::SameSubMsg2));
      a_length = a_lengthT;
      for( uint32_t i = 0; i < a_length; i++){
      offset += this->st_a.deserialize(inbuffer + offset);
        memcpy( &(this->a[i]), &(this->st_a), sizeof(test_roslib_comm::SameSubMsg2));
      }
      for( uint32_t i = 0; i < 10; i++){
      offset += this->b[i].deserialize(inbuffer + offset);
      }
     return offset;
    }

    const char * getType(){ return "test_roslib_comm/TypeNameChangeComplex2"; };
    const char * getMD5(){ return "a01688a0991b9d7d9facf6d94b993e93"; };

  };

}
#endif
