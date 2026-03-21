/* --- Scheduler.cpp --- */

/* ------------------------------------------
author: Tyler
date: 3/21/2026
------------------------------------------ */

#include "Scheduler.h"

Scheduler::Scheduler() {
    // Constructor
}

Scheduler::~Scheduler() {
    // Destructor
}

bool Scheduler::hasWaited(unsigned long waitTime, unsigned long initWaitTime) {
    if (millis() - initWaitTime >= waitTime) {
        initWaitTime = millis();
        return true;
    } 
    return false;
}