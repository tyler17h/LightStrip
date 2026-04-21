/* --- Light.cpp --- */

/* ------------------------------------------
author: Tyler
date: 4/19/2026
------------------------------------------ */

#include "Light.h"

Light::Light() {
    strip.begin();
    strip.clear();
    strip.setBrightness(brightness);

    return;
}

Light::~Light() {
    // Destructor
}

void Light::clearStrip() {
    strip.clear();
}

void Light::showStrip() {
    strip.show();
}

void Light::setColor(uint32_t color) {
    strip.fill(color);
    strip.show();
    return;
}

void Light::setBrightness(int _brightness) {
    brightness = _brightness;
    strip.setBrightness(brightness);
    
    return;
}