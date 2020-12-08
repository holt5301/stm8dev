#ifndef _REGISTERS_H
#define _REGISTERS_H

#define F_MASTER 2000000UL // 2MHz 
#define F_CK_PSC F_MASTER
typedef struct STM8GPIO {
    volatile uint8_t ODR; // GPIO Output Data Latch Register Offset: 0x0
    volatile uint8_t IDR; // GPIO Input Pin Value Register Offset: 0x1
    volatile uint8_t DDR; // GPIO Data Direction Register Offset: 0x2
    volatile uint8_t CR1; // GPIO Control Register 1 Offset: 0x3
    volatile uint8_t CR2; // GPIO Control Register 2 Offset: 0x4
} STM8GPIO_t;

typedef struct STM8I2C {
    volatile uint8_t CR1;
    volatile uint8_t CR2;
    volatile uint8_t FREQR;
    volatile uint8_t OARL;
    volatile uint8_t OARH;
    volatile uint8_t RES;
    volatile uint8_t DR;
    volatile uint8_t SR1;
    volatile uint8_t SR2;
    volatile uint8_t SR3;
    volatile uint8_t ITR;
    volatile uint8_t CCRL;
    volatile uint8_t CCRH;
    volatile uint8_t TRISER;
} STM8I2C_t;

// 16 Bit Advanced Control
typedef struct STM8_16BIT_ADV_TIM {
    volatile uint8_t CR1;
    volatile uint8_t CR2;
    volatile uint8_t SMCR;
    volatile uint8_t ETR;
    volatile uint8_t IER;
    volatile uint8_t SR1;
    volatile uint8_t SR2;
    volatile uint8_t EGR;
    volatile uint8_t CCMR1;
    volatile uint8_t CCMR2;
    volatile uint8_t CCMR3;
    volatile uint8_t CCMR4;
    volatile uint8_t CCER1;
    volatile uint8_t CCER2;
    volatile uint8_t CNTRH;
    volatile uint8_t CNTRL;
    volatile uint8_t PSCRH;
    volatile uint8_t PSCRL;
    volatile uint8_t ARRH;
    volatile uint8_t ARRL;
    volatile uint8_t RCR;
    volatile uint8_t CCR1H;
    volatile uint8_t CCR1L;
    volatile uint8_t CCR2H;
    volatile uint8_t CCR2L;
    volatile uint8_t CCR3H;
    volatile uint8_t CCR3L;
    volatile uint8_t CCR4H;
    volatile uint8_t CCR4L;
    volatile uint8_t BKR;
    volatile uint8_t DTR;
    volatile uint8_t OISR;
} STM8S105X4_TIM1_t;

// 16 Bit Basic - 3 CAPCOM Channels
typedef struct STM8_16BIT_3CH_TIM {
    volatile uint8_t CR1;
    volatile uint8_t IER;
    volatile uint8_t SR1;
    volatile uint8_t SR2;
    volatile uint8_t EGR;
    volatile uint8_t CCMR1;
    volatile uint8_t CCMR2;
    volatile uint8_t CCMR3;
    volatile uint8_t CCER1;
    volatile uint8_t CCER2;
    volatile uint8_t CNTRH;
    volatile uint8_t CNTRL;
    volatile uint8_t PSCR;
    volatile uint8_t ARRH;
    volatile uint8_t ARRL;
    volatile uint8_t CCR1H;
    volatile uint8_t CCR1L;
    volatile uint8_t CCR2H;
    volatile uint8_t CCR2L;
    volatile uint8_t CCR3H;
    volatile uint8_t CCR3L;
} STM8S105X4_TIM2_t;

// 16 Bit Basic - 2 CAPCOM Channels
typedef struct STM8_16BIT_2CH_TIM {
    volatile uint8_t CR1;
    volatile uint8_t IER;
    volatile uint8_t SR1;
    volatile uint8_t SR2;
    volatile uint8_t EGR;
    volatile uint8_t CCMR1;
    volatile uint8_t CCMR2;
    volatile uint8_t CCER1;
    volatile uint8_t CNTRH;
    volatile uint8_t CNTRL;
    volatile uint8_t PSCR;
    volatile uint8_t ARRH;
    volatile uint8_t ARRL;
    volatile uint8_t CCR1H;
    volatile uint8_t CCR1L;
    volatile uint8_t CCR2H;
    volatile uint8_t CCR2L;
} STM8S105X4_TIM3_t;

// 8 Bit Basic
typedef struct STM8_8Bit_TIM {
    volatile uint8_t CR1;
    volatile uint8_t IER;
    volatile uint8_t SR;
    volatile uint8_t EGR;
    volatile uint8_t CNTR;
    volatile uint8_t PSCR;
    volatile uint8_t ARR;
} STM8S105X4_TIM4_t;

#endif // _REGISTERS_H
