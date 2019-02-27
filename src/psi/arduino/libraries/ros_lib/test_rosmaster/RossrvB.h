#ifndef _ROS_SERVICE_RossrvB_h
#define _ROS_SERVICE_RossrvB_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "test_rosmaster/Empty.h"

namespace test_rosmaster
{

static const char ROSSRVB[] = "test_rosmaster/RossrvB";

  class RossrvBRequest : public ros::Msg
  {
    public:
      typedef test_rosmaster::Empty _empty_type;
      _empty_type empty;

    RossrvBRequest():
      empty()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->empty.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->empty.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return ROSSRVB; };
    const char * getMD5(){ return "6aac6c697d5414bc0fcede8c33981d0e"; };

  };

  class RossrvBResponse : public ros::Msg
  {
    public:
      typedef test_rosmaster::Empty _empty_type;
      _empty_type empty;

    RossrvBResponse():
      empty()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->empty.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->empty.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return ROSSRVB; };
    const char * getMD5(){ return "6aac6c697d5414bc0fcede8c33981d0e"; };

  };

  class RossrvB {
    public:
    typedef RossrvBRequest Request;
    typedef RossrvBResponse Response;
  };

}
#endif
