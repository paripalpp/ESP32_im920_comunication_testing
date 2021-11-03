#include <Arduino.h>

#include "im920.hpp"

using namespace IM920s;

IM920s::IM920s(HardwareSerial* serial, unsigned long serial_baud_rate = 19200, uint8_t busy_pin = null, uint8_t reset_pin = null)   //if you change the serial pins, call begin() again after this
{
    _serial = serial;
    _serial_baud_rate = serial_baud_rate;
    _busy_pin = busy_pin;
    _reset_pin = reset_pin;

    _serial->begin(_serial_baud_rate);
    IM920s::reset();
}

IM920s::IM920s(HardwareSerial* serial, unsigned long serial_baud_rate = 19200, uint8_t busy_pin = null, uint8_t reset_pin = null, im920::configs configs )   //if you change the serial pins, call begin() again after this
{
    _serial = serial;
    _serial_baud_rate = serial_baud_rate;
    _busy_pin = busy_pin;
    _reset_pin = reset_pin;

    _serial->begin(_serial_baud_rate);
    IM920s::reset();
    IM920s::setConfigs(configs);
}

IM920s::~IM920s()
{
    _serial->end();
}

IM920s::reset()
{
    if (_reset_pin != null)
    {
        pinMode(_reset_pin, OUTPUT);
        digitalWrite(_reset_pin, LOW);
        delay(10);
        digitalWrite(_reset_pin, HIGH);
        delay(10);
    }else{
        _serial->print("srst\r\n");
        delay(10);
    }
}

IM920s::send_broadcast(uint8_t* data, uint8_t len)
{
    _serial->print("txda ");
    for (uint8_t i = 0; i < len; i++)
    {
        _serial->print(" ");
        _serial->print(data[i], HEX);
    }
    _serial->print("\r\n");
}

IM920s::send_unicast(uint8_t* data, uint8_t len, uint8_t address)
{
    _serial->print("txdu ");
    _serial->print(address, HEX);
    for (uint8_t i = 0; i < len; i++)
    {
        _serial->print(" ");
        _serial->print(data[i], HEX);
    }
    _serial->print("\r\n");
}

IM920s::send_back(uint8_t* data, uint8_t len, uint8_t address)
{
    _serial->print("txsb ");
    _serial->print(address, HEX);
    for (uint8_t i = 0; i < len; i++)
    {
        _serial->print(" ");
        _serial->print(data[i], HEX);
    }
    _serial->print("\r\n");
}
