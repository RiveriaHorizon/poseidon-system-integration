#ifndef _ROS_SERVICE_RossrvA_h
#define _ROS_SERVICE_RossrvA_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace test_rosmaster
{

static const char ROSSRVA[] = "test_rosmaster/RossrvA";

  class RossrvARequest : public ros::Msg
  {
    public:
      typedef int32_t _areq_type;
      _areq_type areq;

    RossrvARequest():
      areq(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_areq;
      u_areq.real = this->areq;
      *(outbuffer + offset + 0) = (u_areq.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_areq.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_areq.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_areq.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->areq);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_areq;
      u_areq.base = 0;
      u_areq.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_areq.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_areq.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_areq.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->areq = u_areq.real;
      offset += sizeof(this->areq);
     return offset;
    }

    const char * getType(){ return ROSSRVA; };
    const char * getMD5(){ return "0217cf2f145df7686492b0471b5ecf7a"; };

  };

  class RossrvAResponse : public ros::Msg
  {
    public:
      typedef int32_t _aresp_type;
      _aresp_type aresp;

    RossrvAResponse():
      aresp(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_aresp;
      u_aresp.real = this->aresp;
      *(outbuffer + offset + 0) = (u_aresp.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_aresp.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_aresp.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_aresp.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->aresp);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_aresp;
      u_aresp.base = 0;
      u_aresp.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_aresp.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_aresp.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_aresp.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->aresp = u_aresp.real;
      offset += sizeof(this->aresp);
     return offset;
    }

    const char * getType(){ return ROSSRVA; };
    const char * getMD5(){ return "7714078796589731036f4da799e23357"; };

  };

  class RossrvA {
    public:
    typedef RossrvARequest Request;
    typedef RossrvAResponse Response;
  };

}
#endif
