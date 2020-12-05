#include <stdint.h>
#include "led.h"
#include "drivers/timers.h"

int main() {
    led_init();
    msTimer_init(500);
    while(1) {
        msTimer_delay();
        led_toggle();
    }
    return 0;
}
