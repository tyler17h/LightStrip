/* --- Task.cpp --- */

/* ------------------------------------------
author: Tyler
date: 4/19/2026
------------------------------------------ */

#include "Task.h"

Task::Task(unsigned int time, TASK task, unsigned int intervals = 1) {
    this->time = time;
    this->task = task;
    this->intervals = intervals;
}

Task::~Task() {
    // Destructor
}
