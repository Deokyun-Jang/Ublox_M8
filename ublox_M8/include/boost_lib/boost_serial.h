#ifndef BOOST_SERIAL_H_
#define BOOST_SERIAL_H_

#include <boost/asio.hpp>
#include <string>

class SimpleSerial
{
public:
    /**
     * Constructor.
     * \param port device name, example "/dev/ttyUSB0" or "COM4"
     * \param baud_rate communication speed, example 9600 or 115200
     * \throws boost::system::system_error if cannot open the
     * serial device
     */

    SimpleSerial()
    : io(), serial(io) {}
 

    void SerialSetup(std::string port, int baudrate)
    {
        serial.open(port);
        serial.set_option(boost::asio::serial_port_base::baud_rate(baudrate));          
    }

/*
    SimpleSerial(std::string port, unsigned int baud_rate)
    : io(), serial(io,port)
    {
        serial.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
    }
*/

    /**
     * Write a string to the serial device.
     * \param s string to write
     * \throws boost::system::system_error on failure
     */
    void WriteSerial(std::string s)
    {
        boost::asio::write(serial,boost::asio::buffer(s.c_str(),s.size()));
    }


    /**
     * Blocks until a line is received from the serial device.
     * Eventual '\n' or '\r\n' characters at the end of the string are removed.
     * \return a string containing the received line
     * \throws boost::system::system_error on failure
     */
    char ReadSerial()
    {
        //Reading data char by char, code is optimized for simplicity, not speed
        
        char c;        
        boost::asio::read(serial, boost::asio::buffer(&c,1));      
        return c;

        /*
        std::string result;
        for(;;)
        {
            boost::asio::read(serial,asio::buffer(&c,1));
            switch(c)
            {
                case '\r':
                    break;
                case '\n':
                    return result;
                default:
                    result+=c;
            }
        }
        */
    }


private:
    boost::asio::io_service io;
    boost::asio::serial_port serial;
};

#endif