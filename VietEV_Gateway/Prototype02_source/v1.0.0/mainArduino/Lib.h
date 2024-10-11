#include <avr/eeprom.h>
#pragma once

#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <qrcode.h>
#include <string.h>

#define LCD_RESET A4 //A4 // Can alternately just connect to Arduino's reset pin
#define LCD_CS    A3   // Chip Select goes to Analog 3
#define LCD_CD    A2  // Command/Data goes to Analog 2
#define LCD_WR    A1  // LCD Write goes to Analog 1
#define LCD_RD    A0 // LCD Read goes to Analog 0

// Định nghĩa các màu
#define	color_Black   0x0000
#define	color_Blue    0x001F
#define	color_Red     0xF800
#define	color_Green   0x07E0
#define color_Cyan    0x07FF
#define color_Magenta 0xF81F
#define color_Yellow  0xFFE0
#define color_White   0xFFFF
#define color_Gray    0x7BEF

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