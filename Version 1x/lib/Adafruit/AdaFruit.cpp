/* --- AdaFruit.cpp --- */

/* ------------------------------------------
author: Tyler
date: 3/20/2026
------------------------------------------ */

#include "AdaFruit.h"

AdaFruit::AdaFruit(int _pin) {
    // Constructor
    pin = _pin;
    strip.begin();
}

AdaFruit::~AdaFruit() {
    // Destructor
}

void AdaFruit::turnOn() {
    fillStrip();
}

void AdaFruit::shutDown() {
    isPowered = false;
    strip.clear();
    strip.show();
}

void AdaFruit::nextColor() {
    if (isPowered) {
        lightmode = (lightmode + 1) % MODE_LIST_SIZE;
        fillStrip();
    }
    else {
        isPowered = true;
        fillStrip();
    } 
}

void AdaFruit::fillStrip() {
    switch (lightmode)
    {
    case SOLID:
        setSolid();
        strip.fill(currentColor);
        break;
    case RAINBOW:
        setRainbow();
        break;
    case CHASE:
        setTheaterChaseRainbow();
        break;
    default:
        break;
    }
    strip.show();
}

void AdaFruit::setSolid() {
    currentColor = strip.Color(100, 100, 100);
}

void AdaFruit::setRainbow() {
    strip.rainbow(0, 1, 255, 150, true);
}

void AdaFruit::setTheaterChaseRainbow() {
    // Hue of first pixel runs 5 complete loops through the color wheel.
    // Color wheel has a range of 65536 but it's OK if we roll over, so
    // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
    // means we'll make 5*65536/256 = 1280 passes through this loop:
    firstPixelHue = (firstPixelHue += 256) % maxFirstPixelHue;
    // strip.rainbow() can take a single argument (first pixel hue) or
    // optionally a few extras: number of rainbow repetitions (default 1),
    // saturation and value (brightness) (both 0-255, similar to the
    // ColorHSV() function, default 255), and a true/false flag for whether
    // to apply gamma correction to provide 'truer' colors (default true).
    strip.rainbow(firstPixelHue);
    // Above line is equivalent to:
    // strip.rainbow(firstPixelHue, 1, 255, 255, true);
    strip.show(); // Update strip with new contents
}