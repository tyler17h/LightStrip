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

#include "ActionEnum.h"

#define ANALOG_PIN A2     // Voltage divider input

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
    void setModeColor();
    void fillStrip();
    void setSolid();
    void setUniqueSolidModifier();
    void setRainbow();
    void setUniqueRainbowModifier();
    void setTheaterChaseRainbow();
    void setUniqueChaseModifier();
    void breathEffect();
    void strobeEffect();
    void triggerModiferSignal(ACTION action);
    void setUniqueModifier();
    void setBreathModifier();
    void setStrobeModifier();
    void voltagToColor();

    bool getPowerState() {return isPowered;}

private:
    int pin = 4;
    uint16_t ledCount = 20;
    Scheduler scheduler;
    LIGHTMODE lightModeList[MODE_LIST_SIZE] = { SOLID, RAINBOW, CHASE };
    int lightmode = 0;
    bool isPowered = false;
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(ledCount, pin, NEO_GRB + NEO_KHZ800);
    uint32_t currentColor = strip.Color(100, 100, 100);
    unsigned long fillWaitTime = 0;
    unsigned long modifySignalWaitTime = 0;
    unsigned long uniqueModiferWaitTime = 0;
    unsigned long breathModiferWaitTime = 0;
    unsigned long strobeModiferWaitTime = 0;

    ACTION lastAciton = NOTHING;
    bool isUniqueModifierActive = false;
    bool isBreathModifierActive =false;
    bool isStrobeModifierActive =false;

    bool isIncremneting = false;
    int baseBrightness = 200;
    int brightness = 100;
    int maxBrightness = 200;

    //solid modifier
    long currentHue = 0;
    const int rainbowHueStep = 128;      // smaller = slower fade, larger = faster

    //rainbow modifier
    int reps = 1;

    //rainbow chase
    bool isHueIncrementing = false;
    long firstPixelHue = 0;
    int minchaseHueStep = 64;
    int maxchaseHueStep = 1024;
    long chaseHue = 256;
    int chaseHueStep = 64;
    long maxFirstPixelHue = 5*65536;

    // Voltage range
    const float V_MAX = 3.7;  // Green
    const float V_MIN = 2.7;  // Red

    // Arduino ADC reference voltage (5V board = 5.0, 3.3V board = 3.3)
    const float AREF = 5.0;
    const float ADC_RESOLUTION = 1023.0;
};

#endif // ADAFRUIT_H
