
#include <Arduino.h>
#include "define.h"

// This is to hide non-test related source code.
// https://docs.platformio.org/en/latest/plus/unit-testing.html
#ifndef UNIT_TEST

void setup()
{
    // put your setup code here, to run once:

    // Enables Serial Communication with baudRate of 115200
    // Serial.begin(115200);
    // Serial.println("PlatformIO ESP32 Boilerplate started...");

    pinMode(PIN_LED_INBUILT, OUTPUT);

    pinMode(PIN_KEY_0, INPUT_PULLUP);
    pinMode(PIN_KEY_1, INPUT_PULLUP);
    pinMode(PIN_KEY_2, INPUT_PULLUP);
    pinMode(PIN_KEY_3, INPUT_PULLUP);
    pinMode(PIN_KEY_4, INPUT_PULLUP);
    pinMode(PIN_KEY_5, INPUT_PULLUP);

    pinMode(PIN_KNOB, INPUT);

    pinMode(PIN_ENC_A, INPUT_PULLUP);
    pinMode(PIN_ENC_B, INPUT_PULLUP);
}

void loop()
{
    // put your main code here, to run repeatedly:

    digitalWrite(PIN_LED_INBUILT, HIGH);
    delay(1000);
    digitalWrite(PIN_LED_INBUILT, LOW);
    delay(1000);
}

#endif
