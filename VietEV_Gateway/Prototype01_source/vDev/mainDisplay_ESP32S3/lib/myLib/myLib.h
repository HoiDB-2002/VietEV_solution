// #include <avr/eeprom.h>
#pragma once
#include <Arduino.h>

#define GFX_BL                  DF_GFX_BL // default backlight pin
#define TFT_BL                  2
#define RX1                     17
#define TX1                     18

// Width of screen
#define size_WidthScreen        480
// Height of screen
#define size_HeightScreen       272

// ------------------------ Define color ----------------------------------
#define	color_Black             0x0000
#define	color_Blue              0x001F
#define	color_Red               0xF800
#define	color_Green             0x07E0
#define color_Cyan              0x07FF
#define color_Magenta           0xF81F
#define color_Yellow            0xFFE0
#define color_White             0xFFFF
#define color_Gray              0x7BEF

extern String strQRCode;
extern int previousPower;

// Các trạng thái màn hình
enum eStateDisplay
{
  stDefault,
  stWelcome,
  stDisplayOTP,
  stWaitingToChargeEV,
  stChargingEV,
  stChargingInfor,
  stChargingEVCompleted,
  stDebugger = 90,
  stTestKeypad,
  stTestPowerMeter
};

enum eDraw
{
  drawFasle,
  drawTrue,
  drawInfor
};

struct sPowerInfor
{
  float fVoltage;
  float fCurrent;
  float fPower;
  float fEnergy;
  float fFrequency;
};