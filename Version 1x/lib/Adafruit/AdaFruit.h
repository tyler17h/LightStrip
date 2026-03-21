/* --- AdaFruit.h --- */

/* ------------------------------------------
Author: Tyler
Date: 3/20/2026
------------------------------------------ */

#ifndef ADAFRUIT_H
#define ADAFRUIT_H
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Scheduler.h>

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

enum LIGHTMODE {SOLID, RAINBOW, CHASE, MODE_LIST_SIZE};

class AdaFruit {
public:
    AdaFruit();
    ~AdaFruit();
    void turnOn();
    void shutDown();
    void nextColor();
    void fillStrip();
    void setSolid();
    void setRainbow();
    void setTheaterChaseRainbow();
    void modify_1_Effect();
    void modify_2_Effect();
    void triggerModify_1_signal();
    void SetModifier_1();
    void triggerModify_2_signal();
    void SetModifier_2();


private:
    int pin = 4;
    Scheduler scheduler;
    LIGHTMODE lightModeList[MODE_LIST_SIZE] = { SOLID, RAINBOW, CHASE };
    int lightmode = 0;
    bool isPowered = false;
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, pin, NEO_GRB + NEO_KHZ800);
    uint32_t currentColor = strip.Color(100, 100, 100);
    unsigned long fillWaitTime = 0;
    unsigned long modifySignalWaitTime = 0;
    unsigned long modifer_1_WaitTime = 0;
    unsigned long modifer_2_WaitTime = 0;

    bool initModify_1_Trigger = false;
    bool modify_1_activeFlag =false;
    bool initModify_2_Trigger = false;
    bool modify_2_activeFlag =false;

    bool isIncremneting = false;
    int baseBrightness = 200;
    int brightness = 100;
    int maxBrightness = 200;

    //rainbow chase
    long firstPixelHue = 0;
    long maxFirstPixelHue = 5*65536;
};

#endif // ADAFRUIT_H
