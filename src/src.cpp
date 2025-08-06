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
    PIN_BUTTON_6};

bool lastState[6];

// Rotary encoder state
volatile int encoderState = 1; // valid range 1-7
volatile int lastEncoded = 0;
volatile bool encoderMoved = false;

void IRAM_ATTR updateEncoder()
{
    int msb = digitalRead(PIN_ENC_A);
    int lsb = digitalRead(PIN_ENC_B);
    int encoded = (msb << 1) | lsb;
    int sum = (lastEncoded << 2) | encoded;

    if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011)
    {
        if (encoderState < 7)
        {
            encoderState++;
            encoderMoved = true;
        }
    }
    else if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000)
    {
        if (encoderState > 1)
        {
            encoderState--;
            encoderMoved = true;
        }
    }

    lastEncoded = encoded;
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Mini Bluetooth Key Drive starting...");

    // Initialize button pins with pull-ups
    for (size_t i = 0; i < 6; i++)
    {
        pinMode(buttonPins[i], INPUT_PULLUP);
        lastState[i] = false;
    }

    // Initialize rotary encoder pins and interrupts
    pinMode(PIN_ENC_A, INPUT_PULLUP);
    pinMode(PIN_ENC_B, INPUT_PULLUP);
    lastEncoded = (digitalRead(PIN_ENC_A) << 1) | digitalRead(PIN_ENC_B);
    attachInterrupt(digitalPinToInterrupt(PIN_ENC_A), updateEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_ENC_B), updateEncoder, CHANGE);

    // Initialize I2C and display
    Wire.begin(PIN_SDA, PIN_SCL);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println("SSD1306 allocation failed");
    }
    display.clearDisplay();
    display.display();

    // Start BLE services
    bleKeyboard.begin();
    bleMouse.begin();
}

void loop()
{
    if (bleKeyboard.isConnected())
    {
        for (size_t i = 0; i < 6; i++)
        {
            bool pressed = digitalRead(buttonPins[i]) == LOW;
            if (pressed && !lastState[i])
            {
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

    if (encoderMoved)
    {
        noInterrupts();
        int value = encoderState;
        encoderMoved = false;
        interrupts();

        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.print("State ");
        display.print(value);
        display.display();
    }
    delay(10);
}

#endif // UNIT_TEST
