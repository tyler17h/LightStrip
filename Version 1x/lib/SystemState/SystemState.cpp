/* --- SystemState.cpp --- */

/* ------------------------------------------
author: Tyler
date: 4/26/2026
------------------------------------------ */

#include "SystemState.h"

SystemManager::SystemManager() {
    // Constructor
}

SystemManager::~SystemManager() {
    // Destructor
}

void SystemManager::powerOffSystem() {
    systemState = OFFLINE;
    return;
}

void SystemManager::powerOnSystem() {
    systemState = ONLINE;
    return;
}
