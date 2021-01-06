#ifndef _PROFILE_TIME_H
#define _PROFILE_TIME_H

#include <time.h>
#include <stdint.h>

struct time_measurement {
    time_t timestamp;
    
    clock_t start;
    clock_t stop;

    uint64_t raw_result;
    double ms_result;
    double s_result;
};

struct time_measurement *create_measurement();


// In-place method for measuring runtime
void start_measurement(struct time_measurement *t);
void stop_measurement(struct time_measurement *t);

// Composite solutions
void print_runtime(void (*func)(void *), void *data);
struct time_measurement *measure_runtime(void (*func)(void *), void *data);

// Helpers
void print_measurement(struct time_measurement *t);
void populate_measurement(struct time_measurement *t);

#endif

