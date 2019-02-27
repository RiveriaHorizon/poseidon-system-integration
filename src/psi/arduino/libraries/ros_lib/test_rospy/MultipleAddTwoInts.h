#ifndef _ROS_SERVICE_MultipleAddTwoInts_h
#define _ROS_SERVICE_MultipleAddTwoInts_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace test_rospy
{

static const char MULTIPLEADDTWOINTS[] = "test_rospy/MultipleAddTwoInts";

  class MultipleAddTwoIntsRequest : public ros::Msg
  {
    public:
      typedef int32_t _a_type;
      _a_type a;
      typedef int32_t _b_type;
      _b_type b;
      typedef int32_t _c_type;
      _c_type c;
      typedef int32_t _d_type;
      _d_type d;

    MultipleAddTwoIntsRequest():
      a(0),
      b(0),
      c(0),
      d(0)
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
      union {
        int32_t real;
        uint32_t base;
      } u_b;
      u_b.real = this->b;
      *(outbuffer + offset + 0) = (u_b.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_b.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_b.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_b.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->b);
      union {
        int32_t real;
        uint32_t base;
      } u_c;
      u_c.real = this->c;
      *(outbuffer + offset + 0) = (u_c.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_c.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_c.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_c.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->c);
      union {
        int32_t real;
        uint32_t base;
      } u_d;
      u_d.real = this->d;
      *(outbuffer + offset + 0) = (u_d.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_d.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_d.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_d.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->d);
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
      union {
        int32_t real;
        uint32_t base;
      } u_b;
      u_b.base = 0;
      u_b.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_b.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_b.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_b.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->b = u_b.real;
      offset += sizeof(this->b);
      union {
        int32_t real;
        uint32_t base;
      } u_c;
      u_c.base = 0;
      u_c.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_c.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_c.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_c.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->c = u_c.real;
      offset += sizeof(this->c);
      union {
        int32_t real;
        uint32_t base;
      } u_d;
      u_d.base = 0;
      u_d.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_d.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_d.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_d.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->d = u_d.real;
      offset += sizeof(this->d);
     return offset;
    }

    const char * getType(){ return MULTIPLEADDTWOINTS; };
    const char * getMD5(){ return "55328e64986cccd71be7fe834e693c76"; };

  };

  class MultipleAddTwoIntsResponse : public ros::Msg
  {
    public:
      typedef int32_t _ab_type;
      _ab_type ab;
      typedef int32_t _cd_type;
      _cd_type cd;

    MultipleAddTwoIntsResponse():
      ab(0),
      cd(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_ab;
      u_ab.real = this->ab;
      *(outbuffer + offset + 0) = (u_ab.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ab.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_ab.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_ab.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ab);
      union {
        int32_t real;
        uint32_t base;
      } u_cd;
      u_cd.real = this->cd;
      *(outbuffer + offset + 0) = (u_cd.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_cd.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_cd.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_cd.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->cd);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_ab;
      u_ab.base = 0;
      u_ab.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ab.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_ab.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_ab.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ab = u_ab.real;
      offset += sizeof(this->ab);
      union {
        int32_t real;
        uint32_t base;
      } u_cd;
      u_cd.base = 0;
      u_cd.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_cd.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_cd.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_cd.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->cd = u_cd.real;
      offset += sizeof(this->cd);
     return offset;
    }

    const char * getType(){ return MULTIPLEADDTWOINTS; };
    const char * getMD5(){ return "e6fcb876df417a4130d2c7eb2d1b2436"; };

  };

  class MultipleAddTwoInts {
    public:
    typedef MultipleAddTwoIntsRequest Request;
    typedef MultipleAddTwoIntsResponse Response;
  };

}
#endif
