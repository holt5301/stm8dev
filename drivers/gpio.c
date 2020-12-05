#include "gpio.h"

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
