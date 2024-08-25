#include <myKeypad.h>

myKeypad::myKeypad() {}

myKeypad::~myKeypad() {}

void myKeypad::initKeypad()
{
    if (!pcf.begin(0x20, &Wire))
    {
        // Serial.println("Couldn't find PCF8574");
        while (1)
            ;
    }
    pcf.pinMode(R1, OUTPUT);
    pcf.pinMode(R2, OUTPUT);
    pcf.pinMode(R3, OUTPUT);
    pcf.pinMode(R4, OUTPUT);

    pcf.pinMode(C1, INPUT_PULLUP);
    pcf.pinMode(C2, INPUT_PULLUP);
    pcf.pinMode(C3, INPUT_PULLUP);
    pcf.pinMode(C4, INPUT_PULLUP);
}

int myKeypad::scanMatrix()
{
    int codeMatrix = -1;

    // Scan row 1
    pcf.digitalWrite(R1, LOW);
    pcf.digitalWrite(R2, HIGH);
    pcf.digitalWrite(R3, HIGH);
    pcf.digitalWrite(R4, HIGH);
    if (pcf.digitalRead(C1) == LOW)
        codeMatrix = 1;
    if (pcf.digitalRead(C2) == LOW)
        codeMatrix = 2;
    if (pcf.digitalRead(C3) == LOW)
        codeMatrix = 3;
    if (pcf.digitalRead(C4) == LOW)
        codeMatrix = 'A';

    // Scan row 2
    pcf.digitalWrite(R1, HIGH);
    pcf.digitalWrite(R2, LOW);
    pcf.digitalWrite(R3, HIGH);
    pcf.digitalWrite(R4, HIGH);
    if (pcf.digitalRead(C1) == LOW)
        codeMatrix = 4;
    if (pcf.digitalRead(C2) == LOW)
        codeMatrix = 5;
    if (pcf.digitalRead(C3) == LOW)
        codeMatrix = 6;
    if (pcf.digitalRead(C4) == LOW)
        codeMatrix = 'B';

    // Scan row 3
    pcf.digitalWrite(R1, HIGH);
    pcf.digitalWrite(R2, HIGH);
    pcf.digitalWrite(R3, LOW);
    pcf.digitalWrite(R4, HIGH);
    if (pcf.digitalRead(C1) == LOW)
        codeMatrix = 7;
    if (pcf.digitalRead(C2) == LOW)
        codeMatrix = 8;
    if (pcf.digitalRead(C3) == LOW)
        codeMatrix = 9;
    if (pcf.digitalRead(C4) == LOW)
        codeMatrix = 'C';

    // Scan row 4
    pcf.digitalWrite(R1, HIGH);
    pcf.digitalWrite(R2, HIGH);
    pcf.digitalWrite(R3, HIGH);
    pcf.digitalWrite(R4, LOW);
    if (pcf.digitalRead(C1) == LOW)
        codeMatrix = '*';
    if (pcf.digitalRead(C2) == LOW)
        codeMatrix = 0;
    if (pcf.digitalRead(C3) == LOW)
        codeMatrix = '#';
    if (pcf.digitalRead(C4) == LOW)
        codeMatrix = 'D';

    return codeMatrix;
}