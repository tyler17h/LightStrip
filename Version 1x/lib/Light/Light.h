/* --- Light.h --- */

/* ------------------------------------------
Author: Tyler
Date: 4/19/2026
------------------------------------------ */

#ifndef LIGHT_H
#define LIGHT_H
#include <Adafruit_NeoPixel.h>

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

class Light {
public:
    Light();
    ~Light();
    void setColor(uint32_t);
    void setBrightness(int _brightness);
    uint32_t getColor(uint16_t hue) { return strip.gamma32(strip.ColorHSV(hue)); }
private:
    int pin = 4;
    uint16_t ledCount = 20;
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(ledCount, pin, NEO_GRB + NEO_KHZ800);
    
    uint32_t currentColor = strip.Color(100, 100, 100);
    int baseBrightness = 150;
    int brightness = 150;
    int maxBrightness = 200;
};

#endif // LIGHT_H
