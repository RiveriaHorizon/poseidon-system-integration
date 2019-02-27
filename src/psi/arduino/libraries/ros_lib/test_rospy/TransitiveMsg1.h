#ifndef _ROS_test_rospy_TransitiveMsg1_h
#define _ROS_test_rospy_TransitiveMsg1_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "test_rospy/TransitiveMsg2.h"

namespace test_rospy
{

  class TransitiveMsg1 : public ros::Msg
  {
    public:
      typedef test_rospy::TransitiveMsg2 _msg2_type;
      _msg2_type msg2;

    TransitiveMsg1():
      msg2()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->msg2.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->msg2.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "test_rospy/TransitiveMsg1"; };
    const char * getMD5(){ return "72751523a989ee2c7a44c006464315e9"; };

  };

}
#endif
