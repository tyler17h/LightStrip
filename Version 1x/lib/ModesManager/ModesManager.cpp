/* --- ModesManager.cpp --- */

/* ------------------------------------------
author: Tyler
date: 4/19/2026
------------------------------------------ */

#include "ModesManager.h"

ModesManager::ModesManager() {
    // Constructor
}

ModesManager::~ModesManager() {
    // Destructor
}

LIGHTMODE ModesManager::nextMode() {
    currMode = (currMode + 1) % MODE_LIST_SIZE;
    return lightModes[currMode];
}