#ifndef _TEMPSENSE_H
#define _TEMPSENSE_H

#include <stdint.h>

void temp_sensor_init();
uint16_t temp_sensor_read_deg();

#endif //_TEMPSENSE_H