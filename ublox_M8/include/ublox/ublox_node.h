#ifndef UBLOX_NODE_H_
#define UBLOX_NODE_H_
#include "boost_lib/boost_serial.h"
#include "ublox_lib/Ublox.cpp"

class UBLOX_parser
 {
 public:

	UBLOX_parser();


  ~UBLOX_parser() {};


  void poll();

  //void close();

  Ublox M8_Gps;

  // Altitude - Latitude - Longitude - N Satellites - fixtype
  float gpsArray[5] = {0, 0, 0, 0, 0};

 private:
  ros::NodeHandle nh_;

  ros::Publisher GPS_pub;

  std::string frame_id_;
  std::string port_;
  int baud_rate_;
  
  SimpleSerial Ublox_serial; 

  char Receive_buff;

  };
 

#endif