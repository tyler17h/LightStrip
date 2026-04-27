/* --- Scheduler.h --- */

/* ------------------------------------------
Author: Tyler
Date: 3/21/2026
------------------------------------------ */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <Arduino.h>
#include <Task.h>

class Scheduler {
public:
    Scheduler();
    ~Scheduler();
    bool hasWaited(unsigned long waitTime, unsigned long initWaitTime);
    void newTask(unsigned int time, TASK task, unsigned int intervals = 1);
    bool checkTask();

private:
    struct task {
        unsigned int time;
        TASK task;
        unsigned int intervals;
    };
};

#endif // SCHEDULER_H
