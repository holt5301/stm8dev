#ifndef _TIMERS_H
#define _TIMERS_H

#include <stdint.h>

// TODO: add interrupt support
void msTimer_init(uint16_t n_ms);
uint16_t msTimer_get_ms_elapsed();
void msTimer_delay();
void msTimer_set_delay(uint16_t n_ms);

#endif // _TIMERS_H
