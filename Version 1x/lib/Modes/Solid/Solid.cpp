/* --- Solid.cpp --- */

/* ------------------------------------------
author: Tyler
date: 4/17/2026
------------------------------------------ */

#include "Solid.h"

Solid::Solid(Light &_light) {
    light = &_light;
    red = 100;
    green = 100;
    blue = 100;
    hue = 0;
    setColor();
}

Solid::~Solid() {
    // Destructor
}

void Solid::uniqueModifier() {
    if (scheduler->hasWaited(20, uniqueModiferWaitTime)) {
        uniqueModiferWaitTime = millis();
        color = light->getColor(hue);
        hue += hueStep;
        setColor();
    }

    return;
}

