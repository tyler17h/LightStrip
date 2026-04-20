/* --- Mode.cpp --- */

/* ------------------------------------------
author: Tyler
date: 4/19/2026
------------------------------------------ */

#include "Mode.h"

Mode::Mode() {
}

Mode::~Mode() {
    // Destructor
}

void Mode::setColor() {
    color = (red << 16) | (green << 8) | blue;
    light->setColor(color);
    Serial.println("Setting color");
    return;
}
