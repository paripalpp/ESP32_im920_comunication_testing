#include <Arduino.h>

#include "im920.hpp"

using namespace IM920;

IM920s::IM920s(HardwareSerial* serial, unsigned long serial_baud_rate, std::optional<uint8_t> busy_pin, std::optional<uint8_t> reset_pin)
{
    this->_serial = serial;
    this->_serial_baud_rate = serial_baud_rate;
    this->_busy_pin = busy_pin;
    this->_reset_pin = reset_pin;

    this->_serial->begin(this->_serial_baud_rate);
    this->_serial->setTimeout(10);
    this->reset();
    this->update_configs();
}

IM920s::IM920s(HardwareSerial* serial, unsigned long serial_baud_rate, std::optional<uint8_t> busy_pin, std::optional<uint8_t> reset_pin, Im920::configs configs)
{
    this->_serial = serial;
    this->_serial_baud_rate = serial_baud_rate;
    this->_busy_pin = busy_pin;
    this->_reset_pin = reset_pin;

    this->_serial->begin(this->_serial_baud_rate);
    this->_serial->setTimeout(10);
    this->reset();
    this->update_configs(configs);
    this->set_configs(configs);
}

IM920s::~IM920s()
{
    IM920s::_serial->end();
}

IM920s::get_command(commands command)
{
    match(command,
        [](commands::send_broadcast)        {return "txda"},
        [](commands::send_broadcast_fixed)  {return "txdt"},
        [](commands::send_unicast)          {return "txdu"},
        [](commands::send_back)             {return "txsb"},
        [](commands::set_node_number)       {return "stnn"},
        [](commands::get_node_number)       {return "rdnn"},
        [](commands::set_group_number)      {return "stgn"},
        [](commands::get_group_number)      {return "rdgn"},
        [](commands::set_network_channel)   {return "stch"},
        [](commands::get_network_channel)   {return "rdch"},
        [](commands::set_sending_power)     {return "stpo"},
        [](commands::get_sending_power)     {return "rdpo"},
        [](commands::set_network_mode)      {return "stnm"},
        [](commands::get_network_mode)      {return "rdnm"},
        [](commands::set_maximum_hops)      {return "sttl"},
        [](commands::get_maximum_hops)      {return "rttl"},
        [](commands::set_rssi_threshold)    {return "stth"},
        [](commands::get_rssi_threshold)    {return "rdth"},
        [](commands::set_ACK_disable)       {return "enak"},
        [](commands::set_ACK_disable)       {return "dsak"},
        [](commands::reset)             {return "srst"}
        )
}

IM920s::reset()
{
    match(this->_reset_pin,
        [](uint8_t pin) {
            pinMode(pin, OUTPUT);
            digitalWrite(pin, LOW);
            delay(10);
            digitalWrite(pin, HIGH);
            delay(10);
        },
        [](std::nullopt_t) {
            this->_serial->println(this->get_command(IM920::commands::reset));
            delay(10);
        });
}

IM920s::send_broadcast(uint8_t* data, uint8_t len)
{
    IM920s::_serial->print(this->get_command(IM920::commands::send_broadcast));
    for (uint8_t i = 0; i < len; i++)
    {
        IM920s::_serial->print(",");
        IM920s::_serial->print(data[i], HEX);
    }
    IM920s::_serial->print("\r\n");
}

IM920s::send_unicast(uint8_t* data, uint8_t len, uint8_t address)
{
    IM920s::_serial->print(this->get_command(IM920::commands::send_unicast));
    IM920s::_serial->print(address, HEX);
    for (uint8_t i = 0; i < len; i++)
    {
        IM920s::_serial->print(",");
        IM920s::_serial->print(data[i], HEX);
    }
    IM920s::_serial->print("\r\n");
}

IM920s::send_back(uint8_t* data, uint8_t len, uint8_t address)
{
    IM920s::_serial->print("txsb ");
    IM920s::_serial->print(address, HEX);
    for (uint8_t i = 0; i < len; i++)
    {
        IM920s::_serial->print(" ");
        IM920s::_serial->print(data[i], HEX);
    }
    IM920s::_serial->print("\r\n");
}
