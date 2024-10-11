#include "myDisplayScreen.h"

myDisplayScreen::myDisplayScreen() {}

void myDisplayScreen::initLCD()
{

    gfx->begin();
    gfx->fillScreen(WHITE);

// DO NOT CHANGE THIS
// *************************************************************************
#ifdef TFT_BL
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
#endif
}

void myDisplayScreen::displayScreen_Test()
{
    int width = gfx->width();
    int height = gfx->height();

    Serial.print("Width: ");
    Serial.println(width);

    Serial.print("Height: ");
    Serial.println(height);
}

void myDisplayScreen::displayScreen_Welcome()
{
    gfx->fillScreen(color_Blue);
    gfx->fillRect(nSpaceSurround, nSpaceSurround, size_WidthScreen - 2 * nSpaceSurround, size_HeightScreen - 2 * nSpaceSurround, color_White);
    gfx->setTextColor(color_Blue);
    int nTextSize = 4;
    gfx->setTextSize(nTextSize);
    gfx->setCursor(75, (size_HeightScreen - 2 * nSpaceSurround) / 2 - (nTextSize / 2) * 8);
    gfx->println("Welcome VietEV");
    gfx->setCursor(15, (size_HeightScreen - 2 * nSpaceSurround) / 2 + (nTextSize / 2) * 8 + 8);
    gfx->println("Gateway Prototype 1");
}

// void myDisplayScreen::displayScreen_ScanOTP()
// {
//     // Initialize the QRCode structure
//     QRCode qrcode;
//     uint8_t qrcodeData[qrcode_getBufferSize(3)]; // version 3 (29x29 QR code)

//     // Create the QR code
//     qrcode_initText(&qrcode, qrcodeData, 3, ECC_LOW, "https://www.example.com");

//     // Calculate the size and position to center the QR code on the screen
//     int qrSize = qrcode.size * 5; // each QR code module will be 5x5 pixels
//     int xOffset = (gfx->width() - qrSize) / 2;
//     int yOffset = (gfx->height() - qrSize) / 2;

//     // Draw the QR code on the screen
//     drawQRCode(&qrcode, xOffset, yOffset, 5);
// }

void myDisplayScreen::displayScreen_ScanOTP()
{

    gfx->fillScreen(color_White);
    drawTitleBox("INPUT YOUR OTP OR SCAN QR CODE");

    // Draw OTP box
    int nOTPBoxStartWidth = size_WidthScreen / 8;
    int nOTPBoxStartHeight = size_HeightScreen / 2;
    int nOTPBoxWidth = 150;
    int nOTPBoxHeight = 60;
    int nOTPBoxBorderSize = 3;
    drawRectEmpty(nOTPBoxStartWidth, nOTPBoxStartHeight, nOTPBoxWidth, nOTPBoxHeight, nOTPBoxBorderSize, color_Blue, color_White);

    // Print OTP
    gfx->setTextColor(color_Blue);
    gfx->setTextSize(3);
    gfx->setCursor(nOTPBoxStartWidth + 23, nOTPBoxStartHeight + 23);
    gfx->println(strQRCode);

    // Print QR code
    drawQRCodeBox();
    drawQRCode(strQRCode);
}

void myDisplayScreen::displayScreen_ChargingVehicle()
{
    gfx->fillScreen(color_White);
    drawTitleBox("VERHICLE IS CHARGING");
    showCharging();
}

void myDisplayScreen::displayScreen_CompletedCharging() 
{
    gfx->fillScreen(color_White);
    drawTitleBox("CHARGING COMPLETED");
}

void myDisplayScreen::displayScreen_Debugger() {}

void myDisplayScreen::showCharging() 
{
  drawBattery(99);
}

void myDisplayScreen::drawTitleBox(String strTitle)
{
    int nBoxTitleWidth = size_WidthScreen - 2 * nSpaceSurround;
    int nBoxTitleHeight = 40;
    gfx->fillRect(nSpaceSurround, nSpaceSurround, nBoxTitleWidth, nBoxTitleHeight, color_Blue);
    gfx->setTextColor(color_White);
    gfx->setTextSize(2);

    // Estimate the width of a single character (in pixels) at text size 2
    int16_t charWidth = 6 * 2; // 6 pixels * text size 2

    // Calculate the width of the text
    int16_t textWidth = strTitle.length() * charWidth;

    // Calculate the x position to center the text
    int16_t xPosition = nSpaceSurround + (nBoxTitleWidth - textWidth) / 2;

    // Set the cursor to the calculated position
    gfx->setCursor(xPosition, 20);
    gfx->println(strTitle);
}


void myDisplayScreen::drawRectEmpty(int nRectStartWidth, int nRectStartHeight, int nRectWidth, int nRectHeight, int nBorderSize, int nBorderColor, int nBoxColor)
{
    gfx->fillRect(nRectStartWidth, nRectStartHeight,
                  nRectWidth, nRectHeight,
                  nBorderColor);
    gfx->fillRect(nRectStartWidth + nBorderSize, nRectStartHeight + nBorderSize,
                  nRectWidth - 2 * nBorderSize, nRectHeight - 2 * nBorderSize,
                  nBoxColor);
}

void myDisplayScreen::drawQRCodeBox()
{
    int nBoxLocationWidth = 270;
    int nBoxLocationHeight = 80;
    int nBoxWidth = 170;
    int nBoxHeight = 170;
    String strMessage = "Scan me";

    // Vẽ vòng vuông đen
    gfx->fillRect(nBoxLocationWidth, nBoxLocationHeight, nBoxWidth, nBoxHeight, color_Black);
    gfx->fillRect(nBoxLocationWidth + 3, nBoxLocationHeight + 3, nBoxWidth - 6, nBoxHeight - 6, color_White);

    // Vẽ góc viền qr
    gfx->fillRect(nBoxLocationWidth + 10, nBoxLocationHeight + 10, nBoxWidth - 20, nBoxHeight - 20, color_Black);
    gfx->fillRect(nBoxLocationWidth + 10 + 3, nBoxLocationHeight + 10 + 3, nBoxWidth - 20 - 6, nBoxHeight - 20 - 6, color_White);
    gfx->fillRect(nBoxLocationWidth + 10 + 10 + 10, nBoxLocationHeight + 10, nBoxWidth - 20 - 40, nBoxHeight - 20, color_White);

    // Vẽ hình vuông đen in chữ Scan me
    gfx->fillRect(nBoxLocationWidth + nBoxWidth / 4 - 10, nBoxLocationHeight - 12, nBoxWidth / 2 + 20, 26, color_Black);
    gfx->setTextColor(color_White); // Đặt màu văn bản là trắng
    gfx->setTextSize(2);            // Đặt kích thước văn bản là 2
    // In dòng chữ "Nhập mã OTP của bạn hoặc quét mã bên cạnh" vào giữa hình chữ nhật
    gfx->setCursor(315, 72);
    gfx->println(strMessage);
}

void myDisplayScreen::drawQRCode(String qrData)
{
    // Tạo một đối tượng QRCode
    QRCode qrcode;

    // Chuyển đổi dữ liệu sang mã QR
    uint8_t qrcodeData[qrcode_getBufferSize(5)];
    qrcode_initText(&qrcode, qrcodeData, 4, 0, qrData.c_str());

    // Xác định kích thước của mã QR
    int qrSize = qrcode.size;

    int qrStartX = 290;
    int qrStartY = 100;

    // Vẽ mã QR
    for (int y = 0; y < qrSize; y++)
    {
        for (int x = 0; x < qrSize; x++)
        {
            if (qrcode_getModule(&qrcode, x, y))
            {
                gfx->fillRect(qrStartX + x * 4, qrStartY + y * 4, 4, 4, color_Black); // Vẽ điểm đen cho mỗi module của mã QR
            }
            else
            {
                gfx->fillRect(qrStartX + x * 4, qrStartY + y * 4, 4, 4, color_White); // Vẽ điểm trắng cho mỗi module của mã QR
            }
        }
    }
}

void myDisplayScreen::drawBattery(int nPinPercent)
{
    int nPinLocationWidth = 35;
    int nPintLocationHeight = 100;

    int nPinWidth = 80;
    int nPinHeight = 40;

    // draw batery
    gfx->fillRect(nPinLocationWidth, nPintLocationHeight, nPinWidth, nPinHeight, color_Gray);
    gfx->fillRect(nPinLocationWidth + 3, nPintLocationHeight + 3, nPinWidth - 6, nPinHeight - 6, color_White);
    // gfx->fillRect(nPinLocationWidth + 6, nPintLocationHeight + 6, (nPinWidth - 6) * nPinPercent/100, nPinHeight - 9, color_Green);

    // show batery percent
    gfx->setTextColor(color_Black);
    gfx->setTextSize(2);
    gfx->setCursor(nPinLocationWidth + nPinWidth + 10, nPintLocationHeight + 13);
    // gfx->print(nPinPercent);
    gfx->print("NaN");
}

void myDisplayScreen::drawLightning(int nVolteNum, int nAmpeNum) {}
void myDisplayScreen::drawClock(int nTimeCharge) {}
void myDisplayScreen::drawPower(int nPower) {}
void myDisplayScreen::showButtonPlay() {}
void myDisplayScreen::showButtonPause() {}
void myDisplayScreen::showButtonEnd() {}
int previousPower = 0;
void myDisplayScreen::drawDataUpdate(sPowerInfor sData)
{
    if (previousPower != 0)
    {
        gfx->fillRect(250, 213, 90, 15, color_White); // Energy box
        gfx->fillRect(125, 233, 90, 15, color_White); // Current box
        gfx->fillRect(125, 213, 90, 15, color_White); // Voltage box
        gfx->fillRect(250, 113, 90, 15, color_White); // Time box
    }

    // Vẽ giá trị mới
    gfx->setTextColor(color_Black);
    gfx->setTextSize(2);

    gfx->setCursor(125, 213);
    gfx->print(sData.fVoltage);
    gfx->print("V");
    gfx->setCursor(125, 233);
    gfx->print(sData.fCurrent);
    gfx->print("A");
    gfx->setCursor(250, 213);
    gfx->print(sData.fEnergy);
    gfx->print("kWh");
    gfx->setCursor(250, 113);
    String strTime = showTime(previousPower);
    gfx->print(strTime);
    // gfx->print("h");

    previousPower += 10;
}
String myDisplayScreen::showTime(unsigned int nTime)
{
    String strTime = String(nTime / 3600) + ":" +
                     ((nTime % 3600) / 60 < 10 ? "0" : "") + String((nTime % 3600) / 60);
    //  + ":" + (nTime % 60 < 10 ? "0" : "") + String(nTime % 60);
    return strTime;
}

// void myDisplayScreen::drawQRCode(QRCode *qrcode, int x, int y, int pixelSize)
// {
//     for (int i = 0; i < qrcode->size; i++)
//     {
//         for (int j = 0; j < qrcode->size; j++)
//         {
//             if (qrcode_getModule(qrcode, i, j))
//             {
//                 gfx->fillRect(x + i * pixelSize, y + j * pixelSize, pixelSize, pixelSize, BLACK);
//             }
//             else
//             {
//                 gfx->fillRect(x + i * pixelSize, y + j * pixelSize, pixelSize, pixelSize, WHITE);
//             }
//         }
//     }
// }