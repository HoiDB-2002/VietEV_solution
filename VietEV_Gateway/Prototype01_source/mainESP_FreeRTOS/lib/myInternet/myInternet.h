#pragma once

#include "myLib.h"
#include <WiFi.h>
#include <Ethernet.h>
#include <SPI.h>

// Define Ethernet information
#define ETHERNET_MAC                    "BA:E5:E3:B1:44:DD"             // Ethernet MAC address (have to be unique between devices in the same network)
#define ETHERNET_IP                     "192.168.1.15"                  // IP address of RoomHub when on Ethernet connection


class myInternet {
public:
    myInternet();
    // myInternet(const char* ssid, const char* password);
    bool connectWifi();
    bool connectEthernet();
    void macCharArrayToBytes(const char* str, byte* bytes);
    void ethernetWizReset(const uint8_t resetPin);
    Client& getClient();
    String getSSID();
    String getIPAdress();
private:
    WiFiClient wifiClient;
    // Define Wifi information
    // const char* ssid = "H&T";
    // const char* password = "a1234567890";
    String ssid = "H&T";
    String password = "a1234567890";
    EthernetClient ethernetClient;
    Client* client; // Generic Client pointer
};
