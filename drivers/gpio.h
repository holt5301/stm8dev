#include <stdint.h>
#include <stdbool.h>
#include "registers.h"

#define PX_DDR_INPUTMODE 0x0
#define PX_DDR_OUTPUTMODE 0x1
#define PX_CR1_FLOAT_INPUT 0x0
#define PX_CR1_PU_INPUT 0x1
#define PX_CR1_PSU_OPEN_DRAIN_OUTPUT 0x0
#define PX_CR1_PUSHPULL_OUTPUT 0x1
#define PX_ODR_LOW 0x0
#define PX_ODR_HIGH 0x1
#define DIR_OUTPUT PX_DDR_OUTPUTMODE
#define DIR_INPUT PX_DDR_INPUTMODE

#define CTRL_IN_FLT PX_CR1_FLOAT_INPUT
#define CTRL_IN_PU PX_CR1_PU_INPUT
#define CTRL_OUT_POD PX_CR1_PSU_OPEN_DRAIN_OUTPUT
#define CTRL_OUT_PP PX_CR1_PUSHPULL_OUTPUT

#define OUTPUT_LOW PX_ODR_LOW
#define OUTPUT_HIGH PX_ODR_HIGH

void gpio_set_pin_dir(STM8GPIO_t* gpio, uint8_t bit, bool dir) {
    uint8_t ddrreg = gpio->DDR;
    ddrreg &= ~((uint8_t)(1 << bit)); // clear bit
    ddrreg |= (dir << bit);
    gpio->DDR = ddrreg;
    return;
}

void gpio_set_output(STM8GPIO_t* gpio, uint8_t bit, bool high) {
    uint8_t odrreg = gpio->ODR;
    odrreg &= ~((uint8_t)(1 << bit));
    odrreg |= (high << bit);
    gpio->ODR = odrreg;
    return;
}

void gpio_toggle_output(STM8GPIO_t* gpio, uint8_t bit) {
    gpio->ODR ^= 1 << bit;
    return;
}

bool gpio_get_output(STM8GPIO_t* gpio, uint8_t bit) {
    return (bool)(gpio->ODR & (1 >> bit));
}

void gpio_set_ctrl_mode(STM8GPIO_t* gpio, uint8_t bit, bool mode) {
    uint8_t cr1reg = gpio->CR1;
    cr1reg &= ~((uint8_t)(1 << bit)); // clear bit
    cr1reg |= (mode << bit);
    gpio->CR1 = cr1reg;
    return;
}

volatile static STM8GPIO_t* GPIOA = (STM8GPIO_t*)(0x005000);
volatile static STM8GPIO_t* GPIOB = (STM8GPIO_t*)(0x005005);
volatile static STM8GPIO_t* GPIOC = (STM8GPIO_t*)(0x00500A);
volatile static STM8GPIO_t* GPIOD = (STM8GPIO_t*)(0x00500F);
volatile static STM8GPIO_t* GPIOE = (STM8GPIO_t*)(0x005014);
volatile static STM8GPIO_t* GPIOF = (STM8GPIO_t*)(0x005019);
volatile static STM8GPIO_t* GPIOG = (STM8GPIO_t*)(0x00501E);
volatile static STM8GPIO_t* GPIOH = (STM8GPIO_t*)(0x005023);
volatile static STM8GPIO_t* GPIOI = (STM8GPIO_t*)(0x005028);