#ifndef _ROS_SERVICE_HeaderEcho_h
#define _ROS_SERVICE_HeaderEcho_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace test_rosservice
{

static const char HEADERECHO[] = "test_rosservice/HeaderEcho";

  class HeaderEchoRequest : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;

    HeaderEchoRequest():
      header()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return HEADERECHO; };
    const char * getMD5(){ return "d7be0bb39af8fb9129d5a76e6b63a290"; };

  };

  class HeaderEchoResponse : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;

    HeaderEchoResponse():
      header()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return HEADERECHO; };
    const char * getMD5(){ return "d7be0bb39af8fb9129d5a76e6b63a290"; };

  };

  class HeaderEcho {
    public:
    typedef HeaderEchoRequest Request;
    typedef HeaderEchoResponse Response;
  };

}
#endif
