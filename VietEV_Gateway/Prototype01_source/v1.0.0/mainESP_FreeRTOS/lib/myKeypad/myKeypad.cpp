#include <myKeypad.h>

// myKeypad::myKeypad() {}

myKeypad::myKeypad() : pcf8575(0x27) {}
myKeypad::~myKeypad() {}


void myKeypad::initKeypad()
{
    Wire.begin();  // Initialize I2C communication
    pcf8575.begin();  // Initialize the PCF8575 module
    for (int i = 0; i < 16; i++) {
        pcf8575.pinMode(i, INPUT);  // Set all pins to input mode
    }
}

int myKeypad::scanMatrix() {
    for (int i = 0; i < 16; i++) {
        if (pcf8575.digitalRead(i) == LOW) {  // Check if the button is pressed
            return i;  // Return the index of the pressed button
        }
    }
    return -1;  // Return -1 if no button is pressed
}