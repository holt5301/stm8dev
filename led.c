#include "drivers/gpio.h"
#include "led.h"
void led_init() {
    gpio_set_pin_dir(GPIOD, 0, DIR_OUTPUT);
    gpio_set_ctrl_mode(GPIOD, 0, CTRL_OUT_POD);
    gpio_set_output(GPIOD, 0, OUTPUT_HIGH);
    return;
}

void led_toggle() {
    gpio_toggle_output(GPIOD, 0);
    return;
}