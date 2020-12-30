#ifndef _LIS3DH_H
#define _LIS3DH_H

#include <stdint.h>

int8_t lis3dh_init();
void lis3dh_read_accel(int16_t* buf);

#endif // _LIS3DH_H