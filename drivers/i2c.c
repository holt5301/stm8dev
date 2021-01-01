#include "i2c.h"
#include "registers.h"

#define I2C_CR1_NOSTRETCH           (uint8_t)(0x01 << 7)
#define I2C_CR1_ENGC_ENABLED        (uint8_t)(0x01 << 6)
#define I2C_CR1_PE_ENABLED          (uint8_t)(0x01 << 0)

#define I2C_CR2_START               (uint8_t)(0x01 << 0)
#define I2C_CR2_STOP                (uint8_t)(0x01 << 1)
#define I2C_CR2_ACK                 (uint8_t)(0x01 << 2)
#define I2C_CR2_POS                 (uint8_t)(0x01 << 3)
#define I2C_CR2_SWRST               (uint8_t)(0x01 << 7)

#define I2C_CCRH_FS_SLOW            (uint8_t)(0x00 << 7)
#define I2C_CCRH_FS_Fast            (uint8_t)(0x01 << 7)
#define I2C_CCRH_FMDC_2             (uint8_t)(0x00 << 6)
#define I2C_CCRH_FMDC_16_9          (uint8_t)(0x01 << 6)

#define I2C_SR1_TXE_DR_EMPTY        (uint8_t)(0x01 << 7)
#define I2C_SR1_RXNE_DR_NOTEMPTY    (uint8_t)(0x01 << 6)
#define I2C_SR1_STOPF               (uint8_t)(0x01 << 4)
#define I2C_SR1_ADD10               (uint8_t)(0x01 << 3)
#define I2C_SR1_BTF                 (uint8_t)(0x01 << 2)
#define I2C_SR1_ADDR_SENT           (uint8_t)(0x01 << 1)
#define I2C_SR1_SB                  (uint8_t)(0x01 << 0)

#define I2C_SR3_DUALF               (uint8_t)(0x01 << 7)
#define I2C_SR3_GENCALL             (uint8_t)(0x01 << 4)
#define I2C_SR3_TRA                 (uint8_t)(0x01 << 2)
#define I2C_SR3_BUSY                (uint8_t)(0x01 << 1)
#define I2C_SR3_MSL                 (uint8_t)(0x01 << 0)

volatile static STM8I2C_t* I2C = (STM8I2C_t*)(0x005210);

void i2c_init() {
    static bool initialized = false;
    if(initialized) {
        return;
    }

    // Disable the peripheral and reset other bits (just in case)
    I2C->CR1 = 0x00;
    // Disable interrupts for now ... just working by polling
    I2C->ITR = 0x00;
    // Program peripheral input cloce I2C_FREQR to generate proper timings
    // Default is 2MHz
    I2C->FREQR = (uint8_t)(F_MASTER / 1000000UL);
    // Configure clock control registers
    // Period(I2C) = 2 * CCR * t_master
    // 1/(100KHz) = 10us = 2 * (10) * 500ns (1/(2MHz) = 500ns)
    I2C->CCRH = I2C_CCRH_FS_SLOW | I2C_CCRH_FMDC_2 | 0x00;
    I2C->CCRL = 0x0A;
    // configure rise time register
    I2C->TRISER = 0x03;
    // Program I2C_CR1 to enable the peripheral
    I2C->CR1 = I2C_CR1_PE_ENABLED;
    
    initialized = true;
    return;
}

int8_t i2c_write_bytes(uint8_t s_addr, uint8_t* buf, uint8_t len, bool stop) {
    uint8_t status;
    int i;
    I2C->CR2 = I2C_CR2_ACK | I2C_CR2_START;

    // When the start bit is set in the status register, the
    // start condition has been generated and we can move on ...
    while(!(I2C->SR1 & I2C_SR1_SB)) {}

    // Now need to write the address into the DR
    // For 7 bit addressing:
    //      - DR[7:1] - Address to read from
    //      - DR[0] - Set to 0 to indicate Transmission mode 
    I2C->DR = (s_addr << 1) | 0x00;

    // Sit around polling until the hardware hasnt reported the address
    // sent
    while(!(I2C->SR1 & I2C_SR1_ADDR_SENT)) {}
    
    // Once it has, read SR3 to clear ADDR and verify the state
    // is what we expect (Receiver and master mode)
    status = I2C->SR3;
    if(!(status & I2C_SR3_TRA) || !(status & I2C_SR3_MSL)) {
        return -1;
    }

    for(i = 0; i < len; i++) {
        // Wait for TXE to put next byte in DR
        while(!(I2C->SR1 & I2C_SR1_TXE_DR_EMPTY)) {}
        I2C->DR = buf[i];
    }
    // Done writing, wait until DR and shift register are empty
    while(!(I2C->SR1 & I2C_SR1_TXE_DR_EMPTY) && !(I2C->SR1 & I2C_SR1_BTF)) {}
    
    // All done.
    if(stop) {
        I2C->CR2 |= I2C_CR2_STOP;
    }
    
    return 0;
}


int8_t i2c_read_gt2bytes(uint8_t s_addr, uint8_t* buf, uint8_t len) {
    return 0;
}

int8_t i2c_read_1byte(uint8_t s_addr, uint8_t* buf) {
    uint8_t status;

    // Turn on ACK and start up the communication as master
    I2C->CR2 = I2C_CR2_ACK | I2C_CR2_START;

    // When the start bit is set in the status register, the
    // start condition has been generated and we can move on ...
    while(!(I2C->SR1 & I2C_SR1_SB)) {}

    // Now need to write the address into the DR
    // For 7 bit addressing:
    //      - DR[7:1] - Address to read from
    //      - DR[0] - Set to 1 to indicate Receiver mode 
    I2C->DR = (s_addr << 1) | 0x01;

    // Sit around polling until the hardware has reported the address
    // sent
    while(!(I2C->SR1 & I2C_SR1_ADDR_SENT)) {}    

    I2C->CR2 &= ~I2C_CR2_ACK;    

    // Once it has, read SR3 to clear ADDR and verify the state
    // is what we expect (Receiver and master mode)
    status = I2C->SR3;    

    // Once DR and the shift register are filled, then just program stop
    I2C->CR2 |= I2C_CR2_STOP;

    while(!(I2C->SR1 & I2C_SR1_RXNE_DR_NOTEMPTY)) {}
    
    buf[0] = I2C->DR;

    return 0;
}

int8_t i2c_read_2bytes(uint8_t s_addr, uint8_t* buf) {
    uint8_t status;
    // Turn on ACK and start up the communication as master
    I2C->CR2 = I2C_CR2_ACK | I2C_CR2_START;

    // When the start bit is set in the status register, the
    // start condition has been generated and we can move on ...
    while(!(I2C->SR1 & I2C_SR1_SB)) {}

    // Now need to write the address into the DR
    // For 7 bit addressing:
    //      - DR[7:1] - Address to read from
    //      - DR[0] - Set to 1 to indicate Receiver mode 
    I2C->DR = (s_addr << 1) | 0x01;

    // If only reading 2 bytes, follow this sequence:
    I2C->CR2 |= I2C_CR2_POS;
    // Sit around polling until the hardware has reported the address
    // sent
    while(!(I2C->SR1 & I2C_SR1_ADDR_SENT)) {}
    
    // Once it has, read SR3 to clear ADDR and verify the state
    // is what we expect (Receiver and master mode)
    status = I2C->SR3;
    //if((status & I2C_SR3_TRA) || !(status & I2C_SR3_MSL)) {
    //    return -1;
    //}
    // just set NACK now since POS bit will cause NACK
    // to happen only after second byte is transferred.
    I2C->CR2 &= ~I2C_CR2_ACK;
    // While the BTR and RXNE flags are not set, just wait
    while(!(I2C->SR1 & I2C_SR1_BTF)) {}
    // Once DR and the shift register are filled, then just program stop
    I2C->CR2 |= I2C_CR2_STOP;
    // Now read DR twice to get both bytes
    buf[0] = I2C->DR;
    buf[1] = I2C->DR;
    return 0;
}

// Process for reading various numbers of bytes is significantly different, so
// need to dispatch to different functions 
int8_t i2c_read_bytes(uint8_t s_addr, uint8_t* buf, uint8_t len) {
    if(len == 0) {
        return -3;
    }
    else if (len == 1) {
        return i2c_read_1byte(s_addr, buf);
    }
    else if(len == 2) {
        return i2c_read_2bytes(s_addr, buf);
    }
    else {
        return i2c_read_gt2bytes(s_addr, buf, len);
    }
}