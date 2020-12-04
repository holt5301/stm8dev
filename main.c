#include <stdint.h>
#include "led.h"

int main() {
    uint32_t i;
    led_init();
    while(1) {
        for (i = 0; i < 30000UL; i++) {
            __asm__("nop");
        }
        led_toggle();
    }
    return 0;
}