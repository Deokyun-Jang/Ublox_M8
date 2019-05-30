#include <ros/ros.h>
#include "ublox/ublox_node.h"

UBLOX_parser::UBLOX_parser() 
{
  nh_.param("port", port_, std::string("/dev/ttyACM0"));
  nh_.param("baud_rate", baud_rate_, 9600);
  nh_.param("frame_id", frame_id_, std::string("GPS"));
  
  Ublox_serial.SerialSetup(port_, baud_rate_);

}

void UBLOX_parser::poll()
{

    Receive_buff = Ublox_serial.ReadSerial();
    //std::cout << Receive_buff << std::endl;
  
    if (M8_Gps.encode(Receive_buff)) {
          gpsArray[0] = M8_Gps.altitude;
          gpsArray[1] = M8_Gps.latitude;
          gpsArray[2] = M8_Gps.longitude; 
          gpsArray[3] = M8_Gps.sats_in_use;
          gpsArray[4] = M8_Gps.fixtype;          
        }
    
    std::cout << "Altitude    : " << gpsArray[0] << std::endl;
    std::cout << "Latitude    : " << gpsArray[1] << std::endl;
    std::cout << "Longitude   : " << gpsArray[2] << std::endl;
    std::cout << "Sats in use : " << gpsArray[3] << std::endl;
    std::cout << "Fix type    : " << gpsArray[4] << std::endl;
    std::cout << "===============================" << std::endl;
    
    
}

int main(int argc, char* argv[])
{

  ros::init(argc, argv, "ublox_node");

  UBLOX_parser ublox;


  while (ros::ok())
  {
    ublox.poll();
  }

  //ublox.close();        

  return 0;
}