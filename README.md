# VietEV_Solution

This repository include three parts:

mainArduino include firmware of arduino with 3.5 TFT LCD

mainESP_FreeRTOS include firmware of esp32

dat.csv include data of charging stations


Hardware requirement:

ESP32 Wroom

Module Ethernet W5500 connect to SPI of ESP32 (CS pin = P5)

Module CAN MCP2515 connect to SPI of ESP32 (CS pin = P4)

Module RS232/RS422/RS485 connect to UART2 of ESP32

Module relay connect to GPIO 14

Display (3.5 tft + arduino) connect to UART1 of ESP32

Keypad + module I/O expander (PCF8574) connect to I2C of ESP32


Installation

Prerequisites

Arduino IDE or PlatformIO: Ensure that you have the latest version installed.

ESP32 Board Package: Install the ESP32 board package in Arduino IDE or PlatformIO.


Required Libraries:

WiFi.h

PubSubClient.h for MQTT communication

Wire.h for I2C communication

SPI.h for SPI communication


Setup

Clone the Repository:

sh

Sao chép mã

git clone https://github.com/HoiDB-2002/VietEV_Firmware.git

cd VietEV_Firmware


Configure the Firmware:

Upload firmware of arduino and lcd via cabble

Open the config.h file and update the Wi-Fi credentials, MQTT server settings, and other necessary configurations.

Upload the Firmware:

Connect the VietEV Gateway to your computer via USB.
