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
      typedef uint16_t _servo_hinge_position_type;
      _servo_hinge_position_type servo_hinge_position;
      typedef uint16_t _servo_nozzle_position_type;
      _servo_nozzle_position_type servo_nozzle_position;
      typedef float _wormgear_theta_in_type;
      _wormgear_theta_in_type wormgear_theta_in;
      typedef const char* _wormgear_direction_type;
      _wormgear_direction_type wormgear_direction;

    ArmControl():
      header(),
      arm_type(""),
      servo_hinge_position(0),
      servo_nozzle_position(0),
      wormgear_theta_in(0),
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
      offset += sizeof(this->servo_hinge_position);
      *(outbuffer + offset + 0) = (this->servo_nozzle_position >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->servo_nozzle_position >> (8 * 1)) & 0xFF;
      offset += sizeof(this->servo_nozzle_position);
      union {
        float real;
        uint32_t base;
      } u_wormgear_theta_in;
      u_wormgear_theta_in.real = this->wormgear_theta_in;
      *(outbuffer + offset + 0) = (u_wormgear_theta_in.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_wormgear_theta_in.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_wormgear_theta_in.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_wormgear_theta_in.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->wormgear_theta_in);
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
      this->servo_hinge_position =  ((uint16_t) (*(inbuffer + offset)));
      this->servo_hinge_position |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->servo_hinge_position);
      this->servo_nozzle_position =  ((uint16_t) (*(inbuffer + offset)));
      this->servo_nozzle_position |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->servo_nozzle_position);
      union {
        float real;
        uint32_t base;
      } u_wormgear_theta_in;
      u_wormgear_theta_in.base = 0;
      u_wormgear_theta_in.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_wormgear_theta_in.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_wormgear_theta_in.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_wormgear_theta_in.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->wormgear_theta_in = u_wormgear_theta_in.real;
      offset += sizeof(this->wormgear_theta_in);
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
    const char * getMD5(){ return "7de6ffac39a4184e3cc87af2b16160fa"; };

  };

}
#endif
