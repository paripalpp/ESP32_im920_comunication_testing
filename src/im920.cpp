#include <Arduino.h>

#include "im920.hpp"

using namespace IM920;

IM920s::IM920s(HardwareSerial* serial, unsigned long serial_baud_rate, uint8_t busy_pin, uint8_t reset_pin, configs configs)
{
    this->_serial = serial;
    this->_serial_baud_rate = serial_baud_rate;
    this->_busy_pin = busy_pin;
    this->_reset_pin = reset_pin;

    this->_serial->begin(this->_serial_baud_rate);
    this->_serial->setTimeout(10);
    this->reset();
    this->_update_configs();
    this->set_configs(configs);
}

IM920s::~IM920s()
{
    IM920s::_serial->end();
}

String IM920s::_get_command(commands command)
{
    switch (command)
    {
        case commands::send_broadcast:        return String("txda");
        case commands::send_broadcast_fixed:  return String("txdt");
        case commands::send_unicast:          return String("txdu");
        case commands::send_back:             return String("txsb");
        case commands::set_node_number:       return String("stnn");
        case commands::get_node_number:       return String("rdnn");
        case commands::set_group_number:      return String("stgn");
        case commands::get_group_number:      return String("rdgn");
        case commands::set_network_channel:   return String("stch");
        case commands::get_network_channel:   return String("rdch");
        case commands::set_sending_power:     return String("stpo");
        case commands::get_sending_power:     return String("rdpo");
        case commands::set_network_mode:      return String("stnm");
        case commands::get_network_mode:      return String("rdnm");
        case commands::set_maximum_hops:      return String("sttl");
        case commands::get_maximum_hops:      return String("rttl");
        case commands::set_rssi_threshold:    return String("stth");
        case commands::get_rssi_threshold:    return String("rdth");
        case commands::set_ACK_enable:       return String("enak");
        case commands::set_ACK_disable:       return String("dsak");
        case commands::reset:                 return String("srst");
        default:                              return String("");
    }
}

void IM920s::reset()
{
    switch (this->_reset_pin)
    {
        case 255:
            IM920s::_serial->print(this->_get_command(commands::reset));
            break;
        default:
            digitalWrite(this->_reset_pin, LOW);
            delay(100);
            digitalWrite(this->_reset_pin, HIGH);
            break;
    }
}

void IM920s::send_broadcast(uint8_t* data, uint8_t len)
{
    IM920s::_serial->print(this->_get_command(IM920::commands::send_broadcast));
    for (uint8_t i = 0; i < len; i++)
    {
        IM920s::_serial->print(",");
        IM920s::_serial->print(data[i], HEX);
    }
    IM920s::_serial->print("\r\n");
}

void IM920s::send_unicast(uint8_t* data, uint8_t len, uint8_t address)
{
    IM920s::_serial->print(this->_get_command(IM920::commands::send_unicast));
    IM920s::_serial->print(address, HEX);
    for (uint8_t i = 0; i < len; i++)
    {
        IM920s::_serial->print(",");
        IM920s::_serial->print(data[i], HEX);
    }
    IM920s::_serial->print("\r\n");
}

void IM920s::send_back(uint8_t* data, uint8_t len, uint8_t address)
{
    IM920s::_serial->print("txsb ");
    IM920s::_serial->print(address, HEX);
    for (uint8_t i = 0; i < len; i++)
    {
        IM920s::_serial->print(",");
        IM920s::_serial->print(data[i], HEX);
    }
    IM920s::_serial->print("\r\n");
}
