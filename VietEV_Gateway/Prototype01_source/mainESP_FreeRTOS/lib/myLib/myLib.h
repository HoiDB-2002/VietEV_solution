#pragma once
#include <Arduino.h>
#include <vector>

// Declare hardware serial to use in all file
// #include <HardwareSerial.h>
// extern HardwareSerial serialScreen;

// Define topic MQTT publish and subscribe
#define topic_subscribe_subOTP          "testtopic/subOTP"
#define topic_subscribe_publichStatus   "testtopic/publichStatus"
#define topic_subscribe_screen          "testtopic/screen"
#define topic_publish                   "testtopic/sentData"
#define strMessageSentToServer          "c4:de:e2:1e:3c:a4"
#define esp32MACAddress                 "c4:de:e2:1e:3c:a4"
#define deviceName                      "box1"

// Define GPIO device
#define relayPin                        12
#define ETHERNET_RESET_PIN              15                              // ESP32 pin where reset pin from W5500 is connected
#define ETHERNET_CS_PIN                 5                               // ESP32 pin where CS pin from W5500 is connected
#define RX1                             26                              // UART port RX1
#define TX1                             27                              // UART port TX1
#define RX2                             16
#define TX2                             17

// Define Keypad I2C GPIO
#define R1 7
#define R2 6
#define R3 5
#define R4 4
#define C1 3
#define C2 2
#define C3 1
#define C4 0

// Struct of MQTT message (topic, message)
struct sCommand
{
    String strTopic;
    String strMessage;
};

// Struct vector include part of strMessage
struct sMessage {
  std::vector<String> parts;
};

// Struct of Power information
struct sPowerInfor
{
    float fVoltage;
    float fCurrent;
    float fPower;
    float fEnergy;
    float fFrequency;
};

// extern int nState;
// All state of main program
enum eStateProgram
{
    stateDefault,
    stateInitProgram,
    stateReadyToChargeEV,
    stateWaitingToChargeEV,
    stateChargingEV,
    stateChargingEVCompleted,
    stateDebugger = 90,
    stateTestKeypad,
    stateTestPowerMeter
};

// Mode Program
enum eModeProgram
{
    modeUser,
    modeTechnicalSupport,
    modeDebugger
};

// State get power infor
enum eStateGetPowerInfor
{
    Off,
    On
};

// Button keypad
enum eButton
{
    btNull = -1,
    btZero,
    btOne,
    btTwo,
    btThree,
    btFour,
    btFive,
    btSix,
    btSeven,
    btEight,
    btNine,
    btAster,
    btHash,
    btA,
    btB,
    btC,
    btD,
    btDev
};

// Parts of message
enum eMessage
{
    pDeviceName = 0,
    pCommand
};