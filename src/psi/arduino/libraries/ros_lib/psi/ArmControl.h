#ifndef _ROS_psi_ArmControl_h
#define _ROS_psi_ArmControl_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace psi
{

  class ArmControl : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef const char* _arm_type_type;
      _arm_type_type arm_type;
      typedef uint64_t _servo_hinge_position_type;
      _servo_hinge_position_type servo_hinge_position;
      typedef uint64_t _servo_nozzle_position_type;
      _servo_nozzle_position_type servo_nozzle_position;
      typedef float _horizontal_distance_type;
      _horizontal_distance_type horizontal_distance;
      typedef float _vertical_distance_type;
      _vertical_distance_type vertical_distance;
      typedef const char* _wormgear_direction_type;
      _wormgear_direction_type wormgear_direction;

    ArmControl():
      header(),
      arm_type(""),
      servo_hinge_position(0),
      servo_nozzle_position(0),
      horizontal_distance(0),
      vertical_distance(0),
      wormgear_direction("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      uint32_t length_arm_type = strlen(this->arm_type);
      varToArr(outbuffer + offset, length_arm_type);
      offset += 4;
      memcpy(outbuffer + offset, this->arm_type, length_arm_type);
      offset += length_arm_type;
      *(outbuffer + offset + 0) = (this->servo_hinge_position >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->servo_hinge_position >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->servo_hinge_position >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->servo_hinge_position >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (this->servo_hinge_position >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (this->servo_hinge_position >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (this->servo_hinge_position >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (this->servo_hinge_position >> (8 * 7)) & 0xFF;
      offset += sizeof(this->servo_hinge_position);
      *(outbuffer + offset + 0) = (this->servo_nozzle_position >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->servo_nozzle_position >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->servo_nozzle_position >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->servo_nozzle_position >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (this->servo_nozzle_position >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (this->servo_nozzle_position >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (this->servo_nozzle_position >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (this->servo_nozzle_position >> (8 * 7)) & 0xFF;
      offset += sizeof(this->servo_nozzle_position);
      offset += serializeAvrFloat64(outbuffer + offset, this->horizontal_distance);
      offset += serializeAvrFloat64(outbuffer + offset, this->vertical_distance);
      uint32_t length_wormgear_direction = strlen(this->wormgear_direction);
      varToArr(outbuffer + offset, length_wormgear_direction);
      offset += 4;
      memcpy(outbuffer + offset, this->wormgear_direction, length_wormgear_direction);
      offset += length_wormgear_direction;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t length_arm_type;
      arrToVar(length_arm_type, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_arm_type; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_arm_type-1]=0;
      this->arm_type = (char *)(inbuffer + offset-1);
      offset += length_arm_type;
      this->servo_hinge_position =  ((uint64_t) (*(inbuffer + offset)));
      this->servo_hinge_position |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->servo_hinge_position |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->servo_hinge_position |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->servo_hinge_position |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      this->servo_hinge_position |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      this->servo_hinge_position |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      this->servo_hinge_position |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      offset += sizeof(this->servo_hinge_position);
      this->servo_nozzle_position =  ((uint64_t) (*(inbuffer + offset)));
      this->servo_nozzle_position |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->servo_nozzle_position |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->servo_nozzle_position |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->servo_nozzle_position |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      this->servo_nozzle_position |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      this->servo_nozzle_position |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      this->servo_nozzle_position |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      offset += sizeof(this->servo_nozzle_position);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->horizontal_distance));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->vertical_distance));
      uint32_t length_wormgear_direction;
      arrToVar(length_wormgear_direction, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_wormgear_direction; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_wormgear_direction-1]=0;
      this->wormgear_direction = (char *)(inbuffer + offset-1);
      offset += length_wormgear_direction;
     return offset;
    }

    const char * getType(){ return "psi/ArmControl"; };
    const char * getMD5(){ return "43cb151aa61b216fb49ab9835394f414"; };

  };

}
#endif
