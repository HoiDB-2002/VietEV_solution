# VietEV_Solution

VietEV solution is an intergrated IoT solution for charging station system.

This solution is studied and developed by VietEV team: Dao Ba Hoi, Phan Thi Linh Ngan

This repository includes the following components and directories:
+ VietEV_data include list of charging station collected by VietEV team
+ VietEV_gateway is an open-source of gateway (two part: mainESP for control center unit - esp32, and display - esp32se for prototype 1 and arduino for prototype 2)

![Prototype 1](image.png)
Prototype 1
![Prototype 2](image-2.png)
Prototype 2

Hardware requirement: ESP32 Wroom, Module Ethernet W5500 connect to SPI of ESP32 (CS pin = P5), Module CAN MCP2515 connect to SPI of ESP32 (CS pin = P4), Module RS232/RS422/RS485 connect to UART2 of ESP32, Module relay connect to GPIO 14, Display (3.5 tft + arduino) connect to UART1 of ESP32, Keypad + module I/O expander (PCF8574) connect to I2C of ESP32

Installation: Arduino IDE or PlatformIO: Ensure that you have the latest version installed. ESP32 Board Package: Install the ESP32 board package in Arduino IDE or PlatformIO.

Required Libraries: WiFi.h, PubSubClient.h for MQTT communication, Wire.h for I2C communication, SPI.h for SPI communication

Setup: Clone the Repository.

Configure the Firmware: Upload firmware of arduino and lcd via cabble, Open the Internet.h file and update the Wi-Fi credentials, MQTT server settings, and other necessary configurations.

Upload the Firmware: Connect the VietEV Gateway to your computer via USB.
