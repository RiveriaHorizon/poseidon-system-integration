#ifndef _ROS_SERVICE_TransitiveSrv_h
#define _ROS_SERVICE_TransitiveSrv_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "test_rospy/TransitiveMsg1.h"

namespace test_rospy
{

static const char TRANSITIVESRV[] = "test_rospy/TransitiveSrv";

  class TransitiveSrvRequest : public ros::Msg
  {
    public:
      typedef test_rospy::TransitiveMsg1 _msg_type;
      _msg_type msg;

    TransitiveSrvRequest():
      msg()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->msg.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->msg.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return TRANSITIVESRV; };
    const char * getMD5(){ return "c9627b8665f2e2514f3d19406d2ed17d"; };

  };

  class TransitiveSrvResponse : public ros::Msg
  {
    public:
      typedef int32_t _a_type;
      _a_type a;

    TransitiveSrvResponse():
      a(0)
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
     return offset;
    }

    const char * getType(){ return TRANSITIVESRV; };
    const char * getMD5(){ return "5c9fb1a886e81e3162a5c87bf55c072b"; };

  };

  class TransitiveSrv {
    public:
    typedef TransitiveSrvRequest Request;
    typedef TransitiveSrvResponse Response;
  };

}
#endif
