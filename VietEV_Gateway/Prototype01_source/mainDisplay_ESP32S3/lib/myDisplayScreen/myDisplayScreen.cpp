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
    gfx->setCursor(random(gfx->width()), random(gfx->height()));
    gfx->setTextColor(random(0xffff), random(0xffff));
    gfx->setTextSize(random(6), random(6), random(2));
    gfx->println("Hello World!");

    delay(1000); // 1 second delay
}

void myDisplayScreen::displayScreen_ScanOTP()
{
    // Initialize the QRCode structure
    QRCode qrcode;
    uint8_t qrcodeData[qrcode_getBufferSize(3)]; // version 3 (29x29 QR code)

    // Create the QR code
    qrcode_initText(&qrcode, qrcodeData, 3, ECC_LOW, "https://www.example.com");

    // Calculate the size and position to center the QR code on the screen
    int qrSize = qrcode.size * 5; // each QR code module will be 5x5 pixels
    int xOffset = (gfx->width() - qrSize) / 2;
    int yOffset = (gfx->height() - qrSize) / 2;

    // Draw the QR code on the screen
    drawQRCode(&qrcode, xOffset, yOffset, 5);
}

void myDisplayScreen::drawQRCode(QRCode *qrcode, int x, int y, int pixelSize)
{
    for (int i = 0; i < qrcode->size; i++)
    {
        for (int j = 0; j < qrcode->size; j++)
        {
            if (qrcode_getModule(qrcode, i, j))
            {
                gfx->fillRect(x + i * pixelSize, y + j * pixelSize, pixelSize, pixelSize, BLACK);
            }
            else
            {
                gfx->fillRect(x + i * pixelSize, y + j * pixelSize, pixelSize, pixelSize, WHITE);
            }
        }
    }
}