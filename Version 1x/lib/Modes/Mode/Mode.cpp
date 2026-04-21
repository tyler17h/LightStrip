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

void Mode::setLight(Light &light) {
    light_ptr = &light;
}

void Mode::setColor() {
    color = light_ptr->getRGBColor(red, blue, green);
    light_ptr->setColor(color);
    return;
}

void Mode::uniqueModifier() {

}
