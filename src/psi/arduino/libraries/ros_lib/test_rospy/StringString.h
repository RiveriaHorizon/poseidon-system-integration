#ifndef _ROS_SERVICE_StringString_h
#define _ROS_SERVICE_StringString_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "test_rospy/Val.h"
#include "std_msgs/String.h"

namespace test_rospy
{

static const char STRINGSTRING[] = "test_rospy/StringString";

  class StringStringRequest : public ros::Msg
  {
    public:
      typedef std_msgs::String _str_type;
      _str_type str;
      typedef test_rospy::Val _str2_type;
      _str2_type str2;

    StringStringRequest():
      str(),
      str2()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->str.serialize(outbuffer + offset);
      offset += this->str2.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->str.deserialize(inbuffer + offset);
      offset += this->str2.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return STRINGSTRING; };
    const char * getMD5(){ return "1546156fedebbd48201e9764f27ae3e2"; };

  };

  class StringStringResponse : public ros::Msg
  {
    public:
      typedef std_msgs::String _str_type;
      _str_type str;

    StringStringResponse():
      str()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->str.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->str.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return STRINGSTRING; };
    const char * getMD5(){ return "32224c1636e75e68745b61629dfa07c5"; };

  };

  class StringString {
    public:
    typedef StringStringRequest Request;
    typedef StringStringResponse Response;
  };

}
#endif
