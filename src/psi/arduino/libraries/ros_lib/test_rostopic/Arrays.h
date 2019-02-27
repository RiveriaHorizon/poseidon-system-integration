#ifndef _ROS_test_rostopic_Arrays_h
#define _ROS_test_rostopic_Arrays_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "ros/time.h"

namespace test_rostopic
{

  class Arrays : public ros::Msg
  {
    public:
      uint32_t int8_arr_length;
      typedef int8_t _int8_arr_type;
      _int8_arr_type st_int8_arr;
      _int8_arr_type * int8_arr;
      uint32_t uint8_arr_length;
      typedef uint8_t _uint8_arr_type;
      _uint8_arr_type st_uint8_arr;
      _uint8_arr_type * uint8_arr;
      uint32_t int32_arr_length;
      typedef int32_t _int32_arr_type;
      _int32_arr_type st_int32_arr;
      _int32_arr_type * int32_arr;
      uint32_t uint32_arr_length;
      typedef uint32_t _uint32_arr_type;
      _uint32_arr_type st_uint32_arr;
      _uint32_arr_type * uint32_arr;
      uint32_t string_arr_length;
      typedef char* _string_arr_type;
      _string_arr_type st_string_arr;
      _string_arr_type * string_arr;
      uint32_t time_arr_length;
      typedef ros::Time _time_arr_type;
      _time_arr_type st_time_arr;
      _time_arr_type * time_arr;

    Arrays():
      int8_arr_length(0), int8_arr(NULL),
      uint8_arr_length(0), uint8_arr(NULL),
      int32_arr_length(0), int32_arr(NULL),
      uint32_arr_length(0), uint32_arr(NULL),
      string_arr_length(0), string_arr(NULL),
      time_arr_length(0), time_arr(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->int8_arr_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->int8_arr_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->int8_arr_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->int8_arr_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->int8_arr_length);
      for( uint32_t i = 0; i < int8_arr_length; i++){
      union {
        int8_t real;
        uint8_t base;
      } u_int8_arri;
      u_int8_arri.real = this->int8_arr[i];
      *(outbuffer + offset + 0) = (u_int8_arri.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->int8_arr[i]);
      }
      *(outbuffer + offset + 0) = (this->uint8_arr_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->uint8_arr_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->uint8_arr_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->uint8_arr_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->uint8_arr_length);
      for( uint32_t i = 0; i < uint8_arr_length; i++){
      *(outbuffer + offset + 0) = (this->uint8_arr[i] >> (8 * 0)) & 0xFF;
      offset += sizeof(this->uint8_arr[i]);
      }
      *(outbuffer + offset + 0) = (this->int32_arr_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->int32_arr_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->int32_arr_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->int32_arr_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->int32_arr_length);
      for( uint32_t i = 0; i < int32_arr_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_int32_arri;
      u_int32_arri.real = this->int32_arr[i];
      *(outbuffer + offset + 0) = (u_int32_arri.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_int32_arri.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_int32_arri.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_int32_arri.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->int32_arr[i]);
      }
      *(outbuffer + offset + 0) = (this->uint32_arr_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->uint32_arr_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->uint32_arr_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->uint32_arr_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->uint32_arr_length);
      for( uint32_t i = 0; i < uint32_arr_length; i++){
      *(outbuffer + offset + 0) = (this->uint32_arr[i] >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->uint32_arr[i] >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->uint32_arr[i] >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->uint32_arr[i] >> (8 * 3)) & 0xFF;
      offset += sizeof(this->uint32_arr[i]);
      }
      *(outbuffer + offset + 0) = (this->string_arr_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->string_arr_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->string_arr_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->string_arr_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->string_arr_length);
      for( uint32_t i = 0; i < string_arr_length; i++){
      uint32_t length_string_arri = strlen(this->string_arr[i]);
      varToArr(outbuffer + offset, length_string_arri);
      offset += 4;
      memcpy(outbuffer + offset, this->string_arr[i], length_string_arri);
      offset += length_string_arri;
      }
      *(outbuffer + offset + 0) = (this->time_arr_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->time_arr_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->time_arr_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->time_arr_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->time_arr_length);
      for( uint32_t i = 0; i < time_arr_length; i++){
      *(outbuffer + offset + 0) = (this->time_arr[i].sec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->time_arr[i].sec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->time_arr[i].sec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->time_arr[i].sec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->time_arr[i].sec);
      *(outbuffer + offset + 0) = (this->time_arr[i].nsec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->time_arr[i].nsec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->time_arr[i].nsec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->time_arr[i].nsec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->time_arr[i].nsec);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t int8_arr_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      int8_arr_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      int8_arr_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      int8_arr_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->int8_arr_length);
      if(int8_arr_lengthT > int8_arr_length)
        this->int8_arr = (int8_t*)realloc(this->int8_arr, int8_arr_lengthT * sizeof(int8_t));
      int8_arr_length = int8_arr_lengthT;
      for( uint32_t i = 0; i < int8_arr_length; i++){
      union {
        int8_t real;
        uint8_t base;
      } u_st_int8_arr;
      u_st_int8_arr.base = 0;
      u_st_int8_arr.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->st_int8_arr = u_st_int8_arr.real;
      offset += sizeof(this->st_int8_arr);
        memcpy( &(this->int8_arr[i]), &(this->st_int8_arr), sizeof(int8_t));
      }
      uint32_t uint8_arr_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      uint8_arr_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      uint8_arr_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      uint8_arr_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->uint8_arr_length);
      if(uint8_arr_lengthT > uint8_arr_length)
        this->uint8_arr = (uint8_t*)realloc(this->uint8_arr, uint8_arr_lengthT * sizeof(uint8_t));
      uint8_arr_length = uint8_arr_lengthT;
      for( uint32_t i = 0; i < uint8_arr_length; i++){
      this->st_uint8_arr =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->st_uint8_arr);
        memcpy( &(this->uint8_arr[i]), &(this->st_uint8_arr), sizeof(uint8_t));
      }
      uint32_t int32_arr_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      int32_arr_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      int32_arr_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      int32_arr_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->int32_arr_length);
      if(int32_arr_lengthT > int32_arr_length)
        this->int32_arr = (int32_t*)realloc(this->int32_arr, int32_arr_lengthT * sizeof(int32_t));
      int32_arr_length = int32_arr_lengthT;
      for( uint32_t i = 0; i < int32_arr_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_int32_arr;
      u_st_int32_arr.base = 0;
      u_st_int32_arr.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_int32_arr.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_int32_arr.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_int32_arr.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_int32_arr = u_st_int32_arr.real;
      offset += sizeof(this->st_int32_arr);
        memcpy( &(this->int32_arr[i]), &(this->st_int32_arr), sizeof(int32_t));
      }
      uint32_t uint32_arr_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      uint32_arr_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      uint32_arr_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      uint32_arr_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->uint32_arr_length);
      if(uint32_arr_lengthT > uint32_arr_length)
        this->uint32_arr = (uint32_t*)realloc(this->uint32_arr, uint32_arr_lengthT * sizeof(uint32_t));
      uint32_arr_length = uint32_arr_lengthT;
      for( uint32_t i = 0; i < uint32_arr_length; i++){
      this->st_uint32_arr =  ((uint32_t) (*(inbuffer + offset)));
      this->st_uint32_arr |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->st_uint32_arr |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->st_uint32_arr |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->st_uint32_arr);
        memcpy( &(this->uint32_arr[i]), &(this->st_uint32_arr), sizeof(uint32_t));
      }
      uint32_t string_arr_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      string_arr_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      string_arr_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      string_arr_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->string_arr_length);
      if(string_arr_lengthT > string_arr_length)
        this->string_arr = (char**)realloc(this->string_arr, string_arr_lengthT * sizeof(char*));
      string_arr_length = string_arr_lengthT;
      for( uint32_t i = 0; i < string_arr_length; i++){
      uint32_t length_st_string_arr;
      arrToVar(length_st_string_arr, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_string_arr; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_string_arr-1]=0;
      this->st_string_arr = (char *)(inbuffer + offset-1);
      offset += length_st_string_arr;
        memcpy( &(this->string_arr[i]), &(this->st_string_arr), sizeof(char*));
      }
      uint32_t time_arr_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      time_arr_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      time_arr_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      time_arr_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->time_arr_length);
      if(time_arr_lengthT > time_arr_length)
        this->time_arr = (ros::Time*)realloc(this->time_arr, time_arr_lengthT * sizeof(ros::Time));
      time_arr_length = time_arr_lengthT;
      for( uint32_t i = 0; i < time_arr_length; i++){
      this->st_time_arr.sec =  ((uint32_t) (*(inbuffer + offset)));
      this->st_time_arr.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->st_time_arr.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->st_time_arr.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->st_time_arr.sec);
      this->st_time_arr.nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->st_time_arr.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->st_time_arr.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->st_time_arr.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->st_time_arr.nsec);
        memcpy( &(this->time_arr[i]), &(this->st_time_arr), sizeof(ros::Time));
      }
     return offset;
    }

    const char * getType(){ return "test_rostopic/Arrays"; };
    const char * getMD5(){ return "c5a1f18379b10bdd4df210944f6007a4"; };

  };

}
#endif
