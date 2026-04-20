/* --- Light.cpp --- */

/* ------------------------------------------
author: Tyler
date: 4/19/2026
------------------------------------------ */

#include "Light.h"

Light::Light() {
    strip.begin();
    strip.clear();
    strip.setBrightness(baseBrightness);

    return;
}

Light::~Light() {
    // Destructor
}

void Light::setColor(uint32_t color) {
    strip.fill(color);
    Serial.print("color: ");
    Serial.println(color);
    return;
}

void Light::setBrightness(int _brightness) {
    brightness = _brightness;
    strip.setBrightness(brightness);
    
    return;
}