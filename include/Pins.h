#pragma once

#include <Arduino.h>

// ESP32-S3 DevKitC-1 pin map.
// GPIO19/20 are reserved for native USB; GPIO26-37 may be used by flash/PSRAM.
// Shared SPI bus: TFT + nRF24 #1 + nRF24 #2 + CC1101.
#define SCK_PIN   12
#define MOSI_PIN  11
#define MISO_PIN  13

// nRF24 #1
#define NRF1_CE_PIN   4
#define NRF1_CSN_PIN  6

// nRF24 #2
#define NRF2_CE_PIN   5
#define NRF2_CSN_PIN  7

// Backwards-compatible aliases. Existing scanner code uses CE_PIN/CSN_PIN.
#define CE_PIN   NRF1_CE_PIN
#define CSN_PIN  NRF1_CSN_PIN

// TFT SPI display
#define TFT_CS_PIN   10
#define TFT_RST_PIN  8
#define TFT_DC_PIN   9
#define TFT_LED_PIN  3

// Buttons, wired to GND when pressed
#define BTN_UP    1
#define BTN_OK    2
#define BTN_DOWN  21

// M5Stack IR Unit, verified with this module:
// module OUT is driven from ESP32 for TX, module IN is read by ESP32 for RX.
#define IR_TX_PIN 14
#define IR_RX_PIN 15

// CC1101 sub-GHz radio, sharing the SPI bus with TFT and nRF24 modules.
#define CC1101_CSN_PIN  16
#define CC1101_GDO0_PIN 38
#define CC1101_GDO2_PIN -1
// Optional lab TX data line for CC1101 async OOK replay.
// Wire CC1101 GDO0 to this GPIO as an extra jumper; keep GPIO38 for RX.
#define CC1101_TX_DATA_PIN 39

#define OK_LONGPRESS_MS 650

static inline bool waitOkReleaseWasLong(unsigned long holdMs = OK_LONGPRESS_MS) {
    unsigned long start = millis();
    bool wasLong = false;
    while (digitalRead(BTN_OK) == LOW) {
        if (millis() - start >= holdMs) wasLong = true;
        delay(5);
    }
    return wasLong;
}

// No buzzer pin is assigned in this wiring, so sound is disabled.
#define BUZZER_PIN -1
