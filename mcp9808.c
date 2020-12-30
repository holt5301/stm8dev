#include "mcp9808.h"
#include "drivers/i2c.h"
#include "math.h"

#define MCP9808_CONFIG_REG      0x01
#define MCP9808_TUPPER_REG      0x02
#define MCP9808_TLOWER_REG      0x03
#define MCP9808_TCRIT_REG       0x04
#define MCP9808_TA_REG          0x05
#define MCP9808_MFRID_REG       0x06
#define MCP9808_DEVID_REG       0x07
#define MCP9808_RESOLUTION_REG  0x08

// Current address assumes A2 is tied high so that the address = 0x18 + 0x04 = 0x1C

void mcp9808_init() {
    uint8_t buf[1];
    // Init I2C communication
    i2c_init();
    // Configure the MCP9808.  Right now that only involves
    // writing to the MCP9808 pointer register so that ambient temp is read
    buf[0] = MCP9808_TA_REG;
    i2c_write_bytes(0x1C, buf, 1, true);
    return;
}

// Reads out whole number temperature (positive only) in degrees 
uint16_t mcp9808_read_deg() {
    uint8_t buf[2];
    uint16_t temp = 0;

    i2c_read_bytes(0x1C, buf, 2);

    // Only take the lower nibble from the MSB
    temp |= ((uint16_t)(buf[0] & 0x0F)) << 8;
    temp |= (uint16_t) buf[1];
    // Cut off the bottom 4 bits as they represent fractional values
    return temp >> 4;
}