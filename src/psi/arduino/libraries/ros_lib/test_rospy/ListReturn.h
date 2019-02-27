#ifndef _ROS_SERVICE_ListReturn_h
#define _ROS_SERVICE_ListReturn_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace test_rospy
{

static const char LISTRETURN[] = "test_rospy/ListReturn";

  class ListReturnRequest : public ros::Msg
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

    ListReturnRequest():
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

    const char * getType(){ return LISTRETURN; };
    const char * getMD5(){ return "55328e64986cccd71be7fe834e693c76"; };

  };

  class ListReturnResponse : public ros::Msg
  {
    public:
      uint32_t abcd_length;
      typedef int32_t _abcd_type;
      _abcd_type st_abcd;
      _abcd_type * abcd;

    ListReturnResponse():
      abcd_length(0), abcd(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->abcd_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->abcd_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->abcd_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->abcd_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->abcd_length);
      for( uint32_t i = 0; i < abcd_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_abcdi;
      u_abcdi.real = this->abcd[i];
      *(outbuffer + offset + 0) = (u_abcdi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_abcdi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_abcdi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_abcdi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->abcd[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t abcd_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      abcd_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      abcd_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      abcd_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->abcd_length);
      if(abcd_lengthT > abcd_length)
        this->abcd = (int32_t*)realloc(this->abcd, abcd_lengthT * sizeof(int32_t));
      abcd_length = abcd_lengthT;
      for( uint32_t i = 0; i < abcd_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_abcd;
      u_st_abcd.base = 0;
      u_st_abcd.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_abcd.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_abcd.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_abcd.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_abcd = u_st_abcd.real;
      offset += sizeof(this->st_abcd);
        memcpy( &(this->abcd[i]), &(this->st_abcd), sizeof(int32_t));
      }
     return offset;
    }

    const char * getType(){ return LISTRETURN; };
    const char * getMD5(){ return "f962153177b365e43b03cfe90160f33e"; };

  };

  class ListReturn {
    public:
    typedef ListReturnRequest Request;
    typedef ListReturnResponse Response;
  };

}
#endif
