#ifndef _ROS_SERVICE_EmptyRespSrv_h
#define _ROS_SERVICE_EmptyRespSrv_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace test_rospy
{

static const char EMPTYRESPSRV[] = "test_rospy/EmptyRespSrv";

  class EmptyRespSrvRequest : public ros::Msg
  {
    public:
      typedef int32_t _fake_secret_type;
      _fake_secret_type fake_secret;

    EmptyRespSrvRequest():
      fake_secret(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_fake_secret;
      u_fake_secret.real = this->fake_secret;
      *(outbuffer + offset + 0) = (u_fake_secret.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_fake_secret.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_fake_secret.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_fake_secret.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->fake_secret);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_fake_secret;
      u_fake_secret.base = 0;
      u_fake_secret.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_fake_secret.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_fake_secret.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_fake_secret.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->fake_secret = u_fake_secret.real;
      offset += sizeof(this->fake_secret);
     return offset;
    }

    const char * getType(){ return EMPTYRESPSRV; };
    const char * getMD5(){ return "1280578cbe4073963a4321b9248d566e"; };

  };

  class EmptyRespSrvResponse : public ros::Msg
  {
    public:

    EmptyRespSrvResponse()
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

    const char * getType(){ return EMPTYRESPSRV; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class EmptyRespSrv {
    public:
    typedef EmptyRespSrvRequest Request;
    typedef EmptyRespSrvResponse Response;
  };

}
#endif
