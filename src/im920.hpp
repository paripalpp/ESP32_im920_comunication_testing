#pragma onece

#include <Arduino.h>

namespace IM920s {

    struct configs {
        uint16_t node_number    = null;       // Node number 0x0001 ~ 0xFFEF
        uint32_t group_nomber   = null;       // Group number read only
        uint32_t unique_id      = null;       // Unique ID read only
        uint8_t network_channel = null;       // Network channel 01 ~ 29
        uint8_t sending_power   = 2;          // Sending power 1 : 1.1 mW 2 : 10mW
        uint8_t network_mode    = 1;          // Network mode 1 : simple multihop 2 : tree 3 : mesh
        uint8_t maximum_hops    = 10;         // Maximum hops 01 ~ 10
        uint8_t rssi_threshold  = 0x00;       // RSSI threshold 0x00 ~ 0xff
        bool   ACK_enable       = true;       // ACK enable sending in unicast


    }

    enum commands{
        send_broadcast       = "txda" const,
        send_broadcast_fixed = "txdt" const,
        send_unicast         = "txdu" const,
        send_back            = "txsb" const,
        set_node_number      = "stnn" const,
        get_node_number      = "rdnn" const,
        set_group_number     = "stgn" const,
        get_group_number     = "rdgn" const,
        set_network_channel  = "stch" const,
        get_network_channel  = "rdch" const,
        set_sending_power    = "stpo" const,
        get_sending_power    = "rdpo" const,
        set_network_mode     = "stnm" const,
        get_network_mode     = "rdnm" const,
        set_maximum_hops     = "sttl" const,
        get_maximum_hops     = "rttl" const,
        set_rssi_threshold   = "stth" const,
        get_rssi_threshold   = "rdth" const,
        set_ACK_enable       = "enak" const,
        set_ACK_disable      = "dsak" const,
        reset             = "srst" const,
    }

    class IM920s
    {
        private:
            HardwareSerial* _serial;            // Serial port connected to IM920s
            unsigned long _serial_baude_rate;   // Serial port baud rate
            uint8_t _busy_pin;                  // Pin connected to IM920s busy pin
            uint8_t _reset_pin;                 // Pin connected to IM920s reset pin
            IM920s::configs _configs;           // IM920s configs
        public:
            IM920s(HardwareSerial* serial, unsigned long serial_baud_rate = 19200, uint8_t busy_pin = null, uint8_t reset_pin = null);
            IM920s(HardwareSerial* serial, unsigned long serial_baud_rate = 19200, uint8_t busy_pin = null, uint8_t reset_pin = null, im920::configs configs);
            ~IM920s();
            void reset();
            void send_broadcast(uint8_t* data, uint8_t length);
            void send_unicast(uint8_t* data, uint8_t length, uint8_t address);
            void send_back(uint8_t* data, uint8_t length, uint8_t address);
            //setters
            void set_configs(IM920s::configs configs);
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