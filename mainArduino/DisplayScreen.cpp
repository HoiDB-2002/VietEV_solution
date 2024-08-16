#include "DisplayScreen.h"

DisplayScreen::DisplayScreen() {}

void DisplayScreen::displayScreenTest(){
  tft.fillScreen(color_White);
  //show batery percent
  // for (int i = 10; i <= 50; i++) {
  //   drawPowerUpdate(i);
  //   delay(1000);
  // }
  

  // draw_image(207, 107, 25, 39, gImage_clock);
  // tft.drawBitmap(207, 107, gImage_clock, 25, 39, 0xFFFF);
  // tft.drawRGBBitmap(207, 107, gImage_clock, 25, 39);
}

void DisplayScreen::initLCD(){
  Serial.println(F("TFT LCD test"));
  tft.reset();

  uint16_t identifier = tft.readID();
  if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x4535) {
    Serial.println(F("Found LGDP4535 LCD driver"));
  } else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9595) {
    Serial.println(F("Found HX8347-I LCD driver"));
  } else if(identifier == 0x4747) {
    Serial.println(F("Found HX8347-D LCD driver"));
  } else if(identifier == 0x8347) {
    Serial.println(F("Found HX8347-A LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if(identifier == 0x7783) {
    Serial.println(F("Found ST7781 LCD driver"));
  } else if(identifier == 0x8230) {
    Serial.println(F("Found UC8230 LCD driver"));  
  } else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if(identifier == 0x0101) {     
    identifier = 0x9341;
    Serial.println(F("Found 0x9341 LCD driver"));
  } else if(identifier == 0x7793) {     
    Serial.println(F("Found ST7793 LCD driver"));
  } else if(identifier == 0xB509) {     
    Serial.println(F("Found R61509 LCD driver"));
  } else if(identifier == 0x9486) {     
    Serial.println(F("Found ILI9486 LCD driver"));
  } else if(identifier == 0x9488) {     
    Serial.println(F("Found ILI9488 LCD driver"));
  } else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Adafruit 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_ADAFRUIT_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Adafruit_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    identifier = 0x9486; 
  }
  tft.begin(identifier);
  // Xoay màn hình ngang
  tft.setRotation(-1);
  tft.fillScreen(color_White);
}

void DisplayScreen::displayScreen_Welcome()
{
  tft.fillScreen(color_Blue);
  tft.fillRect(10, 10, 460, 300, color_White); 
  tft.setTextColor(color_Blue); // Đặt màu văn bản là trắng
  tft.setTextSize(4); // Đặt kích thước văn bản là 2
  // In dòng chữ "Nhập mã OTP của bạn hoặc quét mã bên cạnh" vào giữa hình chữ nhật
  tft.setCursor(60, 150); 
  tft.println("Welcome to EVCS");  
}

void DisplayScreen::displayScreen_ScanOTP()
{
  tft.fillScreen(color_White);
  // Vẽ hình chữ nhật màu blue cách lề trên và 2 lề bên 1 chút
  tft.fillRect(10, 10, 460, 50, color_Blue); 
  tft.setTextColor(color_White); // Đặt màu văn bản là trắng
  tft.setTextSize(2); // Đặt kích thước văn bản là 2
  // In dòng chữ "Nhập mã OTP của bạn hoặc quét mã bên cạnh" vào giữa hình chữ nhật
  tft.setCursor(50, 30); 
  tft.println("INPUT YOUR OTP OR SCAN QR CODE");

  tft.fillRect(65, 165, 150, 60, color_Blue);
  tft.fillRect(68, 168, 144, 54, color_White);
  tft.setTextColor(color_Blue);
  tft.setTextSize(3); 
  tft.setCursor(87, 185); 
  tft.println(strQRCode);

  // Vẽ QR code
  drawQRCodeBox();
  drawQRCode(strQRCode);
}

void DisplayScreen::displayScreen_ChargingVehicle(){
  tft.fillScreen(color_White);
  // Vẽ hình chữ nhật màu blue cách lề trên và 2 lề bên 1 chút
  tft.fillRect(10, 10, 460, 50, color_Blue); 
  tft.setTextColor(color_White); // Đặt màu văn bản là trắng
  tft.setTextSize(2); // Đặt kích thước văn bản là 2
  // In dòng chữ "Nhập mã OTP của bạn hoặc quét mã bên cạnh" vào giữa hình chữ nhật
  tft.setCursor(130, 30); 
  tft.println("VERHICLE IS CHARGING");
  
  showCharging();  
}

void DisplayScreen::displayScreen_CompletedCharging(){
  tft.fillScreen(color_White);
  // Vẽ hình chữ nhật màu blue cách lề trên và 2 lề bên 1 chút
  tft.fillRect(10, 10, 460, 50, color_Blue); 
  tft.setTextColor(color_White); // Đặt màu văn bản là trắng
  tft.setTextSize(2); // Đặt kích thước văn bản là 2
  // In dòng chữ "Nhập mã OTP của bạn hoặc quét mã bên cạnh" vào giữa hình chữ nhật
  tft.setCursor(150, 30); 
  tft.println("COMPLETE CHARGING");

  drawClock(24);
  drawPower(125);
  showButtonEnd();
}

void DisplayScreen::displayScreen_Debugger()
{
  
}

void DisplayScreen::drawQRCodeBox(){
  int nBoxLocationWidth = 270;
  int nBoxLocationHeight = 100;
  int nBoxWidth = 188;
  int nBoxHeight = 188;
  String strMessage = "Scan me";

    // Vẽ vòng vuông đen
    tft.fillRect(nBoxLocationWidth, nBoxLocationHeight, nBoxWidth, nBoxHeight, color_Black);
    tft.fillRect(nBoxLocationWidth + 3, nBoxLocationHeight + 3, nBoxWidth - 6, nBoxHeight - 6, color_White);

    // Vẽ góc viền qr
    tft.fillRect(nBoxLocationWidth + 10, nBoxLocationHeight + 10, nBoxWidth - 20, nBoxHeight - 20, color_Black);
    tft.fillRect(nBoxLocationWidth + 10 + 3 , nBoxLocationHeight + 10 + 3, nBoxWidth - 20 - 6, nBoxHeight - 20 - 6, color_White);
    tft.fillRect(nBoxLocationWidth + 10 + 10 + 10, nBoxLocationHeight + 10, nBoxWidth - 20 - 40, nBoxHeight - 20, color_White);

    // Vẽ hình vuông đen in chữ Scan me
    tft.fillRect(nBoxLocationWidth + nBoxWidth / 4 - 10, nBoxLocationHeight - 12, nBoxWidth / 2 + 20, 26, color_Black);
    tft.setTextColor(color_White); // Đặt màu văn bản là trắng
    tft.setTextSize(2); // Đặt kích thước văn bản là 2
    // In dòng chữ "Nhập mã OTP của bạn hoặc quét mã bên cạnh" vào giữa hình chữ nhật
    tft.setCursor(325, 93); 
    tft.println(strMessage);
}

void DisplayScreen::drawQRCode(String qrData) {
  // Tạo một đối tượng QRCode
  QRCode qrcode;
  
  // Chuyển đổi dữ liệu sang mã QR
  uint8_t qrcodeData[qrcode_getBufferSize(5)];
  qrcode_initText(&qrcode, qrcodeData, 5, 0, qrData.c_str());
  
  // Xác định kích thước của mã QR
  int qrSize = qrcode.size;
  
  int qrStartX = 290;
  int qrStartY = 120;
  
  // Vẽ mã QR
  for (int y = 0; y < qrSize; y++) {
    for (int x = 0; x < qrSize; x++) {
      if (qrcode_getModule(&qrcode, x, y)) {
        tft.fillRect(qrStartX + x * 4, qrStartY + y * 4, 4, 4, color_Black); // Vẽ điểm đen cho mỗi module của mã QR
      } else {
        tft.fillRect(qrStartX + x * 4, qrStartY + y * 4, 4, 4, color_White); // Vẽ điểm trắng cho mỗi module của mã QR
      }
    }
  }
}

void DisplayScreen::showCharging() {
  drawBattery(99);
  drawLightning(250, 30);
  drawClock(24);
  drawPower(125);
  showButtonPlay();
  showButtonPause();
}

void DisplayScreen::drawBattery(int nPinPercent) {
  int nPinLocationWidth = 35;
  int nPintLocationHeight = 100;

  int nPinWidth = 80;
  int nPinHeight = 40;

// draw batery
  tft.fillRect(nPinLocationWidth, nPintLocationHeight, nPinWidth, nPinHeight, color_Gray);
  tft.fillRect(nPinLocationWidth + 3, nPintLocationHeight + 3, nPinWidth - 6, nPinHeight - 6, color_White);
  // tft.fillRect(nPinLocationWidth + 6, nPintLocationHeight + 6, (nPinWidth - 6) * nPinPercent/100, nPinHeight - 9, color_Green);

//show batery percent
  tft.setTextColor(color_Black);
  tft.setTextSize(2); 
  tft.setCursor(nPinLocationWidth + nPinWidth + 10, nPintLocationHeight + 13); 
  // tft.print(nPinPercent);
  tft.print("NaN");
}

void DisplayScreen::drawLightning(int nVolteNum, int nAmpeNum) {

  // int nLightningLocationWidth = 35;
  // int nLightningLocationHeight = 200;

  // int nLightningWidth = 80;
  // int nLightningHeight = 40;
  // tft.setTextColor(color_Black);
  // tft.setTextSize(2); 
  // tft.setCursor(nLightningLocationWidth + nLightningWidth + 10, nLightningLocationHeight + 13);  
  // tft.print(nVolteNum);
  // tft.print("V");

  // tft.setCursor(nLightningLocationWidth + nLightningWidth + 10, nLightningLocationHeight + 33); 
  // tft.print(nAmpeNum);
  // tft.print("A");
}

void DisplayScreen::drawClock(int nTimeCharge){
  // int nClockLocationWidth = 200;
  // int nClockLocationHeight = 100;

  // int nClockWidth = 80;
  // int nClockHeight = 40;
  // tft.setTextColor(color_Black);
  // tft.setTextSize(2); 
  // tft.setCursor(nClockLocationWidth + nClockHeight + 10, nClockLocationHeight + 13);  
  // tft.print(nTimeCharge);
  // tft.print("h");  
}

void DisplayScreen::drawPower(int nPower){
  // int nPowerLocationWidth = 200;
  // int nPowerLocationHeight = 200;

  // int nPowerWidth = 80;
  // int nPowerHeight = 40;
  // tft.setTextColor(color_Black);
  // tft.setTextSize(2); 
  // tft.setCursor(nPowerLocationWidth + nPowerHeight + 10, nPowerLocationHeight + 13);  
  // tft.print(nPower);
  // tft.print("kWh");  
}

   int previousPower = 0; // Giá trị Power trước đó
void DisplayScreen::drawDataUpdate(sPowerInfor sData){

  // float nVolteNum = sData.fVoltage;
  // float nPower = sData.fPower;
  // float nAmpeNum = sData.fCurrent;

  // int nPowerLocationWidth = 200;
  // int nPowerLocationHeight = 200;
  
  // int nPowerWidth = 80;
  // int nPowerHeight = 40;

  // int nLightningLocationWidth = 35;
  // int nLightningLocationHeight = 200;

  // int nLightningWidth = 80;
  // int nLightningHeight = 40;

  // Nếu giá trị Power trước đó khác với giá trị hiện tại thì xóa giá trị cũ
  if (previousPower != 0) {
    tft.fillRect(250, 213, 90, 15, color_White); // Energy box
    tft.fillRect(125, 233, 90, 15, color_White); // Current box
    tft.fillRect(125, 213, 90, 15, color_White); // Voltage box
    tft.fillRect(250, 113, 90, 15, color_White); // Time box
  }

  // Vẽ giá trị mới
  tft.setTextColor(color_Black);
  tft.setTextSize(2); 

  tft.setCursor(125, 213);  
  tft.print(sData.fVoltage);
  tft.print("V");
  tft.setCursor(125, 233); 
  tft.print(sData.fCurrent);
  tft.print("A");
  tft.setCursor(250, 213);  
  tft.print(sData.fEnergy);
  tft.print("Wh");
  tft.setCursor(250, 113);
  String strTime = showTime(previousPower);
  tft.print(strTime);
  // tft.print("h");

  previousPower+=10; // Cập nhật giá trị Power trước đó
}


void DisplayScreen::showButtonPlay(){
  int nButtonLocationWidth = 340;
  int nButtonLocationHeight = 100;
  int nButtonWidth = 120;
  int nButtonHeight = 80;

  tft.fillRect(nButtonLocationWidth, nButtonLocationHeight, nButtonWidth, nButtonHeight, color_Gray);
  tft.setTextColor(color_White);
  tft.setTextSize(1); 
  tft.setCursor(nButtonLocationWidth + 7, nButtonLocationHeight + 40);  
  tft.print("Press OK to charge");
 
}

void DisplayScreen::showButtonPause(){
  int nButtonLocationWidth = 340;
  int nButtonLocationHeight = 200;
  int nButtonWidth = 120;
  int nButtonHeight = 80;

  tft.fillRect(nButtonLocationWidth, nButtonLocationHeight, nButtonWidth, nButtonHeight, color_Gray);
  tft.setTextColor(color_White);
  tft.setTextSize(1); 
  tft.setCursor(nButtonLocationWidth + 4, nButtonLocationHeight + 40);  
  tft.print("Press Back to pause");
}

void DisplayScreen::showButtonEnd(){
  int nButtonLocationWidth = 340;
  int nButtonLocationHeight = 100;
  int nButtonWidth = 120;
  int nButtonHeight = 80;

  tft.fillRect(nButtonLocationWidth, nButtonLocationHeight, nButtonWidth, nButtonHeight, color_Gray);
  tft.setTextColor(color_White);
  tft.setTextSize(1); 
  tft.setCursor(nButtonLocationWidth + 7, nButtonLocationHeight + 40);  
  tft.print("Press OK to complete");
}

// void DisplayScreen::draw_image(int x, int y, int width, int height, byte image_array[]) {
//   // draw an image
//   // digitalWrite(CS, LOW);
  
//   Address_set(x, y, x + width - 1, y + height - 1);
//   for (int i = 0; i < (width * height * 2); i++) {
//     //Lcd_Write_Data(gImage_shifter_digit_R_24x28px[i]);  // not PROGMEM
//     Lcd_Write_Data(pgm_read_byte_near(image_array + i)); // PROGMEM

//   }
//   digitalWrite(CS, HIGH);
//   // end draw an image
// }

String DisplayScreen::showTime(unsigned int nTime)
{
  // Tính số giờ, phút, giây từ nTime
  // int hours = nTime / 3600;
  // int minutes = (nTime % 3600) / 60;
  // int seconds = nTime % 60;

  // Tạo chuỗi thời gian với định dạng hh:mm:ss
  String strTime = String(nTime / 3600) + ":" + 
                   ((nTime % 3600) / 60 < 10 ? "0" : "") + String((nTime % 3600) / 60) + ":" +
                   (nTime % 60 < 10 ? "0" : "") + String(nTime % 60);

  return strTime;
}