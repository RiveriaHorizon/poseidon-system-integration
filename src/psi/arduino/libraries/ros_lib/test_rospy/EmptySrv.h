#ifndef _ROS_SERVICE_EmptySrv_h
#define _ROS_SERVICE_EmptySrv_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace test_rospy
{

static const char EMPTYSRV[] = "test_rospy/EmptySrv";

  class EmptySrvRequest : public ros::Msg
  {
    public:

    EmptySrvRequest()
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

    const char * getType(){ return EMPTYSRV; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class EmptySrvResponse : public ros::Msg
  {
    public:

    EmptySrvResponse()
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

    const char * getType(){ return EMPTYSRV; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class EmptySrv {
    public:
    typedef EmptySrvRequest Request;
    typedef EmptySrvResponse Response;
  };

}
#endif
