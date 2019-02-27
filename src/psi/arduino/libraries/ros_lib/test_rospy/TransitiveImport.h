#ifndef _ROS_test_rospy_TransitiveImport_h
#define _ROS_test_rospy_TransitiveImport_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "test_rospy/EmbedTest.h"

namespace test_rospy
{

  class TransitiveImport : public ros::Msg
  {
    public:
      typedef test_rospy::EmbedTest _data_type;
      _data_type data;

    TransitiveImport():
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

    const char * getType(){ return "test_rospy/TransitiveImport"; };
    const char * getMD5(){ return "27665539bacd6d2d02a7538692d3d3d0"; };

  };

}
#endif
