#ifndef _I2C_H
#define _I2C_H

#include <stdbool.h>
#include <stdint.h>

void i2c_init();
int8_t i2c_read_bytes(uint8_t s_addr, uint8_t* buf, uint8_t len);
int8_t i2c_write_bytes(uint8_t s_addr, uint8_t* buf, uint8_t len, bool stop);

#endif // _I2C_H
