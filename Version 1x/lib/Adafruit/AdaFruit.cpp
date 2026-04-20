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

void AdaFruit::LightAction(ACTION action) {
    switch (action)
    {
    case NOTHING:
        fillStrip();
        break;
    case NEXT:
        nextColor();
    case UNIQUE_MODIFIER:
        triggerModiferSignal(action);
        setUniqueModifier();
    case BREATH_MODIFIER:
        triggerModiferSignal(action);
        setBreathModifier();
    case STROBE_MODIFIER:
        triggerModiferSignal(action);
        setStrobeModifier();
    case SHUTDOWN:
        shutDown();
    default:
        break;
    }
}

void AdaFruit::turnOn() {
    fillStrip();
}

void AdaFruit::shutDown() {
    isPowered = false;
    lastAciton = NOTHING;
    voltagToColor();
    strip.clear();
    strip.show();
}

void AdaFruit::nextColor() {
    if (isUniqueModifierActive && isPowered) {
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
    strip.rainbow(0, reps, 255, brightness, true);
}

void AdaFruit::setUniqueRainbowModifier() {
    if (scheduler.hasWaited(750, uniqueModiferWaitTime)) {
        uniqueModiferWaitTime = millis();
        reps = (reps + 1) % ledCount;
        reps = (reps == 0) ? 1 : reps;  
        strip.rainbow(0, reps, 255, brightness, true);
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
        strip.clear();
        strip.show();
    }
    if (scheduler.hasWaited(350, modifySignalWaitTime)) {
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

void AdaFruit::voltagToColor() {
    int rawADC = analogRead(ANALOG_PIN);
    float voltageOffset = 0.15;
    float voltage = ((rawADC / ADC_RESOLUTION) * AREF) - voltageOffset;
    float t = (voltage - V_MIN) / (V_MAX - V_MIN);
    uint8_t red   = (uint8_t)((1.0 - t) * 255);  // 255 at min → 0 at max
    uint8_t green = (uint8_t)(t * 255);           // 0 at min  → 255 at max
    uint8_t blue  = 0;
    if (voltage >= V_MAX) {
        green = 255;
        red = 0;
    }  
    if (voltage <= V_MIN) {
        green = 0;
        red = 255;
    }  


    strip.Color(0, 255, 0);
    strip.show();
    Serial.print("voltage");
    Serial.println(voltage);
    Serial.print('red');
    Serial.println(red);
    Serial.print('green');
    Serial.println(green);

    delay(1000);
}

