#pragma onece

#include <iostream>
#include <string>

#include <Arduino.h>


namespace IM920 {

    struct configs {
        uint16_t node_number    = 0;       // Node number 0x0001 ~ 0xFFEF
        uint32_t group_nomber   = 0;       // Group number read only
        uint32_t unique_id      = 0;       // Unique ID read only
        uint8_t network_channel = 0;       // Network channel 01 ~ 29
        uint8_t sending_power   = 2;          // Sending power 1 : 1.1 mW 2 : 10mW
        uint8_t network_mode    = 1;          // Network mode 1 : simple multihop 2 : tree 3 : mesh
        uint8_t maximum_hops    = 10;         // Maximum hops 01 ~ 10
        uint8_t rssi_threshold  = 0x00;       // RSSI threshold 0x00 ~ 0xff
        bool   ACK_enable       = true;       // ACK enable sending in unicast


    };

    const configs default_configs;

    enum commands{
        send_broadcast,
        send_broadcast_fixed,
        send_unicast,
        send_back,
        set_node_number,
        get_node_number,
        set_group_number,
        get_group_number,
        set_network_channel,
        get_network_channel,
        set_sending_power,
        get_sending_power,
        set_network_mode,
        get_network_mode,
        set_maximum_hops,
        get_maximum_hops,
        set_rssi_threshold,
        get_rssi_threshold,
        set_ACK_enable,
        set_ACK_disable,
        reset,
    };

    class IM920s
    {
        private:
            HardwareSerial* _serial;            // Serial port connected to IM920s
            unsigned long _serial_baud_rate;   // Serial port baud rate
            uint8_t _busy_pin;                  // Pin connected to IM920s busy pin
            uint8_t _reset_pin;                 // Pin connected to IM920s reset pin
            IM920::configs _configs;           // IM920s configs
            String _get_command(IM920::commands command);
            //read from IM920s
            void _update_configs();
            void _update_node_number();
            void _update_group_number();
            void _update_network_channel();
            void _update_sending_power();
            void _update_network_mode();
            void _update_maximum_hops();
            void _update_rssi_threshold();
        public:
            IM920s(HardwareSerial* serial, unsigned long serial_baud_rate = 19200, uint8_t _busy_pin = 255, uint8_t reset_pin = 255, IM920::configs configs = default_configs);
            ~IM920s();
            void reset();
            void send_broadcast(uint8_t* data, uint8_t length);
            void send_unicast(uint8_t* data, uint8_t length, uint8_t address);
            void send_back(uint8_t* data, uint8_t length, uint8_t address);
            //setters
            void set_configs(IM920::configs configs);
            void set_configs(uint16_t node_number, uint8_t network_channel, uint8_t sending_power, uint8_t network_mode, uint8_t maximum_hops, uint8_t rssi_threshold, bool ACK_enable);
            void set_node_number(uint16_t node_number);
            void set_network_channel(uint8_t network_channel);
            void set_sending_power(uint8_t sending_power);
            void set_network_mode(uint8_t network_mode);
            void set_maximum_hops(uint8_t maximum_hops);
            void set_rssi_threshold(uint8_t rssi_threshold);
            void set_ACK_enable(bool ACK_enable);
            //getters
            configs get_configs();
            uint16_t get_node_number();
            uint32_t get_group_nomber();
            uint32_t get_unique_id();
            uint8_t get_network_channel();
            uint8_t get_sending_power();
            uint8_t get_network_mode();
            uint8_t get_maximum_hops();
            uint8_t get_rssi_threshold();
            bool get_ACK_enable();
        
    };
}
/*
= "txda"
= "txdt"
= "txdu"
= "txsb"
= "stnn"
= "rdnn"
= "stgn"
= "rdgn"
= "stch"
= "rdch"
= "stpo"
= "rdpo"
= "stnm"
= "rdnm"
= "sttl"
= "rttl"
= "stth"
= "rdth"
= "enak"
= "dsak"
= "srst"
*/