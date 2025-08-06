#pragma once

// You can use the file to define the pin configurations of your project.
// Some of the pin names are already defined below.

#define PIN_LED_INBUILT 8

// Analog Inputs --------
#define PIN_KNOB 0 // GPIO0 / ADC1_0

// Analog Outputs --------
#define PIN_ENC_A 0
#define PIN_ENC_B 1

// Digital Inputs --------
#define PIN_BUTTON_1 3
#define PIN_BUTTON_2 4
#define PIN_BUTTON_3 7
#define PIN_BUTTON_4 10
#define PIN_BUTTON_5 20
#define PIN_BUTTON_6 21

// I2C pins ---------------
#define PIN_SDA 5 // GPIO5
#define PIN_SCL 6 // GPIO6

// UART pins --------------
#define PIN_TX_0 20 // GPIO21
#define PIN_RX_0 21 // GPIO20

// Avoid using
// GPIO8 - internal flash
// GPIO9 - controls bootloader mode