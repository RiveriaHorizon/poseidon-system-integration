#ifndef _ROS_test_rospy_TransitiveMsg2_h
#define _ROS_test_rospy_TransitiveMsg2_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "test_rosmaster/Composite.h"

namespace test_rospy
{

  class TransitiveMsg2 : public ros::Msg
  {
    public:
      typedef test_rosmaster::Composite _data_type;
      _data_type data;

    TransitiveMsg2():
      data()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->data.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->data.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "test_rospy/TransitiveMsg2"; };
    const char * getMD5(){ return "eb1fa3c8b51b0e31f74e89c2eecc441e"; };

  };

}
#endif
