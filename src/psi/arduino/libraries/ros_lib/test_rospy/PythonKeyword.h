#ifndef _ROS_test_rospy_PythonKeyword_h
#define _ROS_test_rospy_PythonKeyword_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace test_rospy
{

  class PythonKeyword : public ros::Msg
  {
    public:
      typedef int32_t _yield_type;
      _yield_type yield;

    PythonKeyword():
      yield(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_yield;
      u_yield.real = this->yield;
      *(outbuffer + offset + 0) = (u_yield.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_yield.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_yield.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_yield.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->yield);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_yield;
      u_yield.base = 0;
      u_yield.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_yield.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_yield.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_yield.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->yield = u_yield.real;
      offset += sizeof(this->yield);
     return offset;
    }

    const char * getType(){ return "test_rospy/PythonKeyword"; };
    const char * getMD5(){ return "1330d6bbfad8e75334346fec949d5133"; };

  };

}
#endif
