#ifndef _ROS_test_rospy_HeaderHeaderVal_h
#define _ROS_test_rospy_HeaderHeaderVal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "test_rospy/HeaderVal.h"

namespace test_rospy
{

  class HeaderHeaderVal : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef test_rospy::HeaderVal _val_type;
      _val_type val;

    HeaderHeaderVal():
      header(),
      val()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->val.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->val.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "test_rospy/HeaderHeaderVal"; };
    const char * getMD5(){ return "ae71c365b9bafbc4abaf37150c80a6b5"; };

  };

}
#endif
