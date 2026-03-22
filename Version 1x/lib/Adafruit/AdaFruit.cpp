/* --- AdaFruit.cpp --- */

/* ------------------------------------------
author: Tyler
date: 3/20/2026
------------------------------------------ */

#include "AdaFruit.h"

AdaFruit::AdaFruit() {
    // Constructor
    strip.begin();
    strip.setBrightness(baseBrightness);
}

AdaFruit::~AdaFruit() {
    // Destructor
}

void AdaFruit::turnOn() {
    fillStrip();
}

void AdaFruit::shutDown() {
    isPowered = false;
    lastAciton = NOTHING;
    strip.clear();
    strip.show();
}

void AdaFruit::nextColor() {
    if (isUniqueModifierActive) {
        isUniqueModifierActive = false;
        return;
    }
    if (isPowered) {
        lastAciton = NOTHING;
        reps = 1;
        isUniqueModifierActive = false;
        isBreathModifierActive = false;
        isStrobeModifierActive = false;
        brightness = baseBrightness;
        strip.setBrightness(brightness);
        lightmode = (lightmode + 1) % MODE_LIST_SIZE;
        setModeColor();
    }
    else {
        isPowered = true;
        fillStrip();
    } 
}

void AdaFruit::setModeColor() {
    switch (lightmode)
        {
        case SOLID:
            setSolid();
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
}

void AdaFruit::fillStrip() {
    if (scheduler.hasWaited(10, fillWaitTime)) {
        fillWaitTime = millis();
        if (isBreathModifierActive) {
            breathEffect();
        }
        if (isStrobeModifierActive) {
            strobeEffect();
        }

        switch (lightmode)
        {
        case SOLID:
            if (isUniqueModifierActive) {
                setUniqueSolidModifier();
            }
            strip.fill(currentColor);
            break;
        case RAINBOW:
            if (isUniqueModifierActive) {
                setUniqueRainbowModifier();
            } else {
                setRainbow();
            }
            break;
        case CHASE:
            if (isUniqueModifierActive) {
                setUniqueChaseModifier();
            }
            setTheaterChaseRainbow();
            break;
        default:
            break;
        }
        strip.show();
    }
}

void AdaFruit::setSolid() {
    currentColor = strip.Color(100, 100, 100);
}

void AdaFruit::setUniqueSolidModifier() {

    if (scheduler.hasWaited(20, uniqueModiferWaitTime)) {
        uniqueModiferWaitTime = millis();
        currentColor = strip.gamma32(strip.ColorHSV(currentHue));
        currentHue += rainbowHueStep;
    }
}

void AdaFruit::setRainbow() {
    strip.rainbow(0, reps, 255, 150, true);
}

void AdaFruit::setUniqueRainbowModifier() {
    if (scheduler.hasWaited(750, uniqueModiferWaitTime)) {
        uniqueModiferWaitTime = millis();
        reps = (reps + 1) % ledCount;
        reps = (reps == 0) ? 1 : reps;  
        strip.rainbow(0, reps, 255, 150, true);
    }
}

void AdaFruit::setTheaterChaseRainbow() {
    // Hue of first pixel runs 5 complete loops through the color wheel.
    // Color wheel has a range of 65536 but it's OK if we roll over, so
    // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
    // means we'll make 5*65536/256 = 1280 passes through this loop:
    firstPixelHue = (firstPixelHue += chaseHue) % maxFirstPixelHue;
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

void AdaFruit::setUniqueChaseModifier() {
    if (scheduler.hasWaited(750, uniqueModiferWaitTime)) {
        uniqueModiferWaitTime = millis();
        if (isHueIncrementing) {
            chaseHue += chaseHueStep;
            
            isHueIncrementing = (chaseHue >= maxchaseHueStep) ? false : true;
        } else {
            chaseHue -= chaseHueStep;
            isHueIncrementing = (chaseHue <= 0) ? true : false;
        } 
    } 
}

void AdaFruit::breathEffect() {
    if (scheduler.hasWaited(25, breathModiferWaitTime)) {
        if (isIncremneting) {
            brightness++;
            strip.setBrightness(brightness);
            
            isIncremneting = (brightness >= maxBrightness) ? false : true;
        } else {
            brightness--;
            strip.setBrightness(brightness);
            
            isIncremneting = (brightness <= 0) ? true : false;
        }
    }
}

void AdaFruit::strobeEffect() {
    if (scheduler.hasWaited(10, strobeModiferWaitTime)) {
        if (isIncremneting) {
            brightness = maxBrightness;
            strip.setBrightness(brightness);
            
            isIncremneting = (brightness == maxBrightness) ? false : true;
        } else {
            brightness = 0;
            strip.setBrightness(brightness);
            
            isIncremneting = (brightness == 0) ? true : false;
        }
    }
}

void AdaFruit::triggerModiferSignal(ACTION action) {
    if (lastAciton != action) {
        lastAciton = action;
        modifySignalWaitTime = millis();
        Serial.println("clear");
        strip.clear();
        strip.show();
    }
    if (scheduler.hasWaited(350, modifySignalWaitTime)) {
        Serial.println("lit");
        fillStrip();
    }
}

void AdaFruit::setUniqueModifier() {
    lastAciton = NOTHING;
    isUniqueModifierActive = !isUniqueModifierActive;
}


void AdaFruit::setBreathModifier() { 
    lastAciton = NOTHING;
    isStrobeModifierActive = false;
    isBreathModifierActive = !isBreathModifierActive;
}

void AdaFruit::setStrobeModifier() {
    isBreathModifierActive = false;
    lastAciton = NOTHING;
    isStrobeModifierActive = !isStrobeModifierActive;
}

