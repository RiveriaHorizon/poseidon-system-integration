#ifndef _ROS_test_rostopic_TVals_h
#define _ROS_test_rostopic_TVals_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "ros/time.h"
#include "ros/duration.h"

namespace test_rostopic
{

  class TVals : public ros::Msg
  {
    public:
      typedef ros::Time _t_type;
      _t_type t;
      typedef ros::Duration _d_type;
      _d_type d;

    TVals():
      t(),
      d()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->t.sec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->t.sec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->t.sec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->t.sec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->t.sec);
      *(outbuffer + offset + 0) = (this->t.nsec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->t.nsec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->t.nsec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->t.nsec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->t.nsec);
      *(outbuffer + offset + 0) = (this->d.sec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->d.sec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->d.sec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->d.sec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->d.sec);
      *(outbuffer + offset + 0) = (this->d.nsec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->d.nsec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->d.nsec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->d.nsec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->d.nsec);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->t.sec =  ((uint32_t) (*(inbuffer + offset)));
      this->t.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->t.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->t.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->t.sec);
      this->t.nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->t.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->t.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->t.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->t.nsec);
      this->d.sec =  ((uint32_t) (*(inbuffer + offset)));
      this->d.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->d.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->d.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->d.sec);
      this->d.nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->d.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->d.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->d.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->d.nsec);
     return offset;
    }

    const char * getType(){ return "test_rostopic/TVals"; };
    const char * getMD5(){ return "ae4d4f9600b9ab683a5dc9372c031758"; };

  };

}
#endif
