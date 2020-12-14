#include <stdint.h>
#include "led.h"
#include "tempsense.h"
#include "drivers/timers.h"

int main() {
    uint16_t ambt_deg;
    led_init();
    temp_sensor_init();
    msTimer_init(1000);
    msTimer_delay();
    while(1) {
        ambt_deg = temp_sensor_read_deg();
        msTimer_set_delay(10 * ambt_deg);
        msTimer_delay();
        led_toggle();
    }
    return 0;
}
