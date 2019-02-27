#ifndef _ROS_SERVICE_ConstantsMultiplex_h
#define _ROS_SERVICE_ConstantsMultiplex_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace test_rospy
{

static const char CONSTANTSMULTIPLEX[] = "test_rospy/ConstantsMultiplex";

  class ConstantsMultiplexRequest : public ros::Msg
  {
    public:
      typedef int8_t _selection_type;
      _selection_type selection;
      enum { BYTE_X = 0 };
      enum { BYTE_Y = 15 };
      enum { BYTE_Z = 5 };
      enum { INT32_X = 0 };
      enum { INT32_Y = -12345678 };
      enum { INT32_Z = 12345678 };
      enum { UINT32_X = 0 };
      enum { UINT32_Y = 12345678 };
      enum { UINT32_Z = 1 };
      enum { FLOAT32_X = 0.0 };
      enum { FLOAT32_Y = -3.14159 };
      enum { FLOAT32_Z = 12345.78 };
      enum { SELECT_X = 1 };
      enum { SELECT_Y = 2 };
      enum { SELECT_Z = 3 };

    ConstantsMultiplexRequest():
      selection(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_selection;
      u_selection.real = this->selection;
      *(outbuffer + offset + 0) = (u_selection.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->selection);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_selection;
      u_selection.base = 0;
      u_selection.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->selection = u_selection.real;
      offset += sizeof(this->selection);
     return offset;
    }

    const char * getType(){ return CONSTANTSMULTIPLEX; };
    const char * getMD5(){ return "3e3b2ecf5f3e7d25830bd97a7fd13b17"; };

  };

  class ConstantsMultiplexResponse : public ros::Msg
  {
    public:
      typedef int8_t _select_confirm_type;
      _select_confirm_type select_confirm;
      typedef int8_t _ret_byte_type;
      _ret_byte_type ret_byte;
      typedef int32_t _ret_int32_type;
      _ret_int32_type ret_int32;
      typedef uint32_t _ret_uint32_type;
      _ret_uint32_type ret_uint32;
      typedef float _ret_float32_type;
      _ret_float32_type ret_float32;
      enum { CONFIRM_X = 1 };
      enum { CONFIRM_Y = 2 };
      enum { CONFIRM_Z = 3 };

    ConstantsMultiplexResponse():
      select_confirm(0),
      ret_byte(0),
      ret_int32(0),
      ret_uint32(0),
      ret_float32(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_select_confirm;
      u_select_confirm.real = this->select_confirm;
      *(outbuffer + offset + 0) = (u_select_confirm.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->select_confirm);
      union {
        int8_t real;
        uint8_t base;
      } u_ret_byte;
      u_ret_byte.real = this->ret_byte;
      *(outbuffer + offset + 0) = (u_ret_byte.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->ret_byte);
      union {
        int32_t real;
        uint32_t base;
      } u_ret_int32;
      u_ret_int32.real = this->ret_int32;
      *(outbuffer + offset + 0) = (u_ret_int32.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ret_int32.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_ret_int32.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_ret_int32.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ret_int32);
      *(outbuffer + offset + 0) = (this->ret_uint32 >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->ret_uint32 >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->ret_uint32 >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->ret_uint32 >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ret_uint32);
      union {
        float real;
        uint32_t base;
      } u_ret_float32;
      u_ret_float32.real = this->ret_float32;
      *(outbuffer + offset + 0) = (u_ret_float32.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ret_float32.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_ret_float32.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_ret_float32.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ret_float32);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_select_confirm;
      u_select_confirm.base = 0;
      u_select_confirm.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->select_confirm = u_select_confirm.real;
      offset += sizeof(this->select_confirm);
      union {
        int8_t real;
        uint8_t base;
      } u_ret_byte;
      u_ret_byte.base = 0;
      u_ret_byte.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->ret_byte = u_ret_byte.real;
      offset += sizeof(this->ret_byte);
      union {
        int32_t real;
        uint32_t base;
      } u_ret_int32;
      u_ret_int32.base = 0;
      u_ret_int32.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ret_int32.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_ret_int32.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_ret_int32.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ret_int32 = u_ret_int32.real;
      offset += sizeof(this->ret_int32);
      this->ret_uint32 =  ((uint32_t) (*(inbuffer + offset)));
      this->ret_uint32 |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->ret_uint32 |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->ret_uint32 |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->ret_uint32);
      union {
        float real;
        uint32_t base;
      } u_ret_float32;
      u_ret_float32.base = 0;
      u_ret_float32.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ret_float32.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_ret_float32.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_ret_float32.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ret_float32 = u_ret_float32.real;
      offset += sizeof(this->ret_float32);
     return offset;
    }

    const char * getType(){ return CONSTANTSMULTIPLEX; };
    const char * getMD5(){ return "012320975f41b58dcffb5b0e7a154691"; };

  };

  class ConstantsMultiplex {
    public:
    typedef ConstantsMultiplexRequest Request;
    typedef ConstantsMultiplexResponse Response;
  };

}
#endif
