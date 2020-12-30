#include <stdint.h>
#include "led.h"
#include "mcp9808.h"
#include "lis3dh.h"
#include "drivers/timers.h"

int main() {
    uint16_t ambt_deg;
    uint16_t accel_mg[3];
    led_init();
    mcp9808_init();
    lis3dh_init();
    msTimer_init(1000);
    msTimer_delay();
    while(1) {
        ambt_deg = mcp9808_read_deg();
        lis3dh_read_accel(accel_mg);
        msTimer_set_delay(25);
        msTimer_delay();
        led_toggle();
    }
    return 0;
}
