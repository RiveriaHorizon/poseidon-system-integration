#ifndef _ROS_test_rospy_TestConstants_h
#define _ROS_test_rospy_TestConstants_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace test_rospy
{

  class TestConstants : public ros::Msg
  {
    public:
      enum { A = -123.0 };
      enum { B = 124.0 };
      enum { C = 125.0 };
      enum { X = 123 };
      enum { Y = -123 };
      enum { Z = 124 };
      enum { FOO = foo };
      enum { SINGLEQUOTE = 'hi };
      enum { DOUBLEQUOTE = "hello" there };
      enum { MULTIQUOTE = "hello" 'goodbye' };
      enum { EXAMPLE = " };
      enum { WHITESPACE =  strip };
      enum { EMPTY =  };
      enum { TRUE = 1 };
      enum { FALSE = 0 };

    TestConstants()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return "test_rospy/TestConstants"; };
    const char * getMD5(){ return "e60959d2ccf9718dc5e42767bebd1644"; };

  };

}
#endif
