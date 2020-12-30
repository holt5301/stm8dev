#include "lis3dh.h"
#include "drivers/i2c.h"

// Register mapping
#define LIS3DH_STATUS_REG_AUX 0x07
#define LIS3DH_OUT_ADC1_L 0x08
#define LIS3DH_OUT_ADC1_H 0x09
#define LIS3DH_OUT_ADC2_L 0x0A
#define LIS3DH_OUT_ADC2_H 0x0B
#define LIS3DH_OUT_ADC3_L 0x0C
#define LIS3DH_OUT_ADC3_H 0x0D
#define LIS3DH_WHO_AM_I 0x0F
#define LIS3DH_CTRL_REG0 0x1E
#define LIS3DH_TEMP_CFG_REG 0x1F
#define LIS3DH_CTRL_REG1 0x20
#define LIS3DH_CTRL_REG2 0x21
#define LIS3DH_CTRL_REG3 0x22
#define LIS3DH_CTRL_REG4 0x23
#define LIS3DH_CTRL_REG5 0x24
#define LIS3DH_CTRL_REG6 0x25
#define LIS3DH_STATUS_REG 0x27
#define LIS3DH_OUT_X_L 0x28
#define LIS3DH_OUT_X_H 0x29
#define LIS3DH_OUT_Y_L 0x2A
#define LIS3DH_OUT_Y_H 0x2B
#define LIS3DH_OUT_Z_L 0x2C
#define LIS3DH_OUT_Z_H 0x2D
#define LIS3DH_FIFO_CTRL_REG 0x2E
#define LIS3DH_FIFO_SRC_REG 0x2F
#define LIS3DH_INT1_CFG 0x30
#define LIS3DH_INT1_SRC 0x31
#define LIS3DH_INT1_THS 0x32
#define LIS3DH_INT1_DURATION 0x33
#define LIS3DH_INT2_CFG 0x34
#define LIS3DH_INT2_SRC 0x35
#define LIS3DH_INT2_THS 0x36
#define LIS3DH_INT2_DURATION 0x37
#define LIS3DH_CLICK_CFG 0x38
#define LIS3DH_CLICK_SRC 0x39
#define LIS3DH_CLICK_THS 0x3A
#define LIS3DH_TIME_LIMIT 0x3C
#define LIS3DH_TIME_LATENCY 0x3B
#define LIS3DH_TIME_WINDOW 0x3D
#define LIS3DH_ACT_THS 0x3E
#define LIS3DH_ACT_DUR 0x3F

#define REG_AUTOINC_ON 0x80
#define REG_AUTOINC_OFF 0x00

int8_t lis3dh_init() {
    uint8_t buf[9];

    // Init I2C communication (if not done already)
    i2c_init();
    
    // Configure the LIS3DH starting at CTRL_REG0 and continuing
    // for the next 8 registers (i.e. autoincrement on for subsequent
    // writes after the first)
    buf[0] = REG_AUTOINC_ON | LIS3DH_CTRL_REG0;

    // CTRL_REG0
    // Disable SDO internal pull up resistor
    // We have one outside the chip
    buf[1] = 0x90;

    // TEMP_CFG_REG
    // Ensure ADC and temp sensors are disabled.
    buf[2] = 0x00;

    // CTRL_REG1
    // Configure modes
    // |ODR3|ODR2|ODR1|ODR0|LPEN|ZEN|YEN|XEN
    // |0   |0   |1   |1   |0   |1  |1  |1
    // This combination of ODR sets 25Hz sampling
    buf[3] = 0x37;

    // CTRL_REG2
    // Disable highpass filtering
    buf[4] = 0x00;

    // CTRL_REG3
    // Disable all interrupts
    buf[5] = 0x00;

    // CTRL_REG4
    // |BDU|BLE|FS1|FS0|HR|ST1|ST0|SIM
    // |1  |0  |0  |0  |0 |0  |0  |0
    buf[6] = 0x80;
    buf[7] = 0x00;
    buf[8] = 0x00;

    // Write 9 bytes (writing start register and 8 bytes to 8
    // registers beginning with start register)
    return i2c_write_bytes(0x18, buf, 9, true);
}

void lis3dh_read_accel(int16_t* accel) {
    uint8_t buf[6];
    uint8_t write_reg[1];

    i2c_write_bytes(0x18, write_reg, 1, false);
    i2c_read_bytes(0x18, buf, 6);
    
    // cast upper byte to 16 bit, shift, then add lower byte so that
    // everything is represented as uint16.  Then reinterpret as int16
    // and shift right so that sign is extended
    accel[0] = ((int16_t) ((((uint16_t) buf[1]) << 8) + buf[0])) >> 4;
    accel[1] = ((int16_t) ((((uint16_t) buf[3]) << 8) + buf[2])) >> 4;
    accel[2] = ((int16_t) ((((uint16_t) buf[5]) << 8) + buf[4])) >> 4;
    
    return;
}


