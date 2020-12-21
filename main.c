#include <stdint.h>
#include "led.h"
#include "mcp9808.h"
#include "drivers/timers.h"

int main() {
    uint16_t ambt_deg;
    led_init();
    mcp9808_init();
    msTimer_init(1000);
    msTimer_delay();
    while(1) {
        ambt_deg = mcp9808_read_deg();
        msTimer_set_delay(10 * ambt_deg);
        msTimer_delay();
        led_toggle();
    }
    return 0;
}
