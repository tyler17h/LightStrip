/* --- Scheduler.h --- */

/* ------------------------------------------
Author: Tyler
Date: 3/21/2026
------------------------------------------ */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <Arduino.h>

class Scheduler {
public:
    Scheduler();
    ~Scheduler();
    bool hasWaited(unsigned long waitTime, unsigned long initWaitTime);

private:

};

#endif // SCHEDULER_H
