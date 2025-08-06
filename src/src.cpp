#include <Arduino.h>
#include "define.h"

#include <BleKeyboard.h>
#include <BleMouse.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#ifndef UNIT_TEST

// BLE peripherals
BleKeyboard bleKeyboard("Mini Key Drive");
BleMouse bleMouse("Mini Key Drive");

// OLED display configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Button pins - defined in pins.h
const uint8_t buttonPins[] = {
    PIN_BUTTON_1,
    PIN_BUTTON_2,
    PIN_BUTTON_3,
    PIN_BUTTON_4,
    PIN_BUTTON_5,
    PIN_BUTTON_6
};

bool lastState[6];

void setup() {
    Serial.begin(115200);
    Serial.println("Mini Bluetooth Key Drive starting...");

    // Initialize button pins with pull-ups
    for (size_t i = 0; i < 6; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP);
        lastState[i] = false;
    }

    // Initialize I2C and display
    Wire.begin(PIN_SDA, PIN_SCL);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("SSD1306 allocation failed");
    }
    display.clearDisplay();
    display.display();

    // Start BLE services
    bleKeyboard.begin();
    bleMouse.begin();
}

void loop() {
    if (bleKeyboard.isConnected()) {
        for (size_t i = 0; i < 6; i++) {
            bool pressed = digitalRead(buttonPins[i]) == LOW;
            if (pressed && !lastState[i]) {
                // Send number keystroke corresponding to button
                bleKeyboard.write('1' + i);

                // Show pressed button on OLED
                display.clearDisplay();
                display.setTextSize(2);
                display.setTextColor(SSD1306_WHITE);
                display.setCursor(0, 0);
                display.print("Button ");
                display.print(i + 1);
                display.display();
            }
            lastState[i] = pressed;
        }
    }
    delay(10);
}

#endif // UNIT_TEST

