#pragma once
#include "Lib.h"
#include "image.h"


class DisplayScreen {
public:
  MCUFRIEND_kbv tft;
  DisplayScreen();

  // Khởi tạo màn hình LCD
  void initLCD();

  void displayScreenTest();
  void displayScreenDefault();

  // Hiển thị màn hình bắt đầu
  void displayScreen_Welcome();

  // Hiển thị màn hình nhập OTP hoặc quét mã QR
  void displayScreen_ScanOTP();

  // Hiển thị màn hình thiết bị đang sạc
  void displayScreen_ChargingVehicle();

  // Hiển thị màn hình thiết bị đã sạc xong
  void displayScreen_CompletedCharging();

  // Show all received information from software serial
  void displayScreen_Debugger();

  void showCharging();
  // void drawTitleBox(string strTitle);
  void drawQRCodeBox();
  void drawQRCode(String qrData);
  void drawBattery(int nPinPercent);
  void drawLightning(int nVolteNum, int nAmpeNum);
  void drawClock(int nTimeCharge);
  void drawPower(int nPower);
  void showButtonPlay();
  void showButtonPause();
  void showButtonEnd();
  void drawDataUpdate(sPowerInfor sData);
  String showTime(unsigned int nTime);
  // void draw_image(int x, int y, int width, int height, byte image_array[]);
};
