#include "timers.h"
#include <math.h>

#define TIMX_CR1_CEN    0x01
#define TIMX_CR1_UDIS   0x02
#define TIMX_CR1_URS    0x04
#define TIMX_CR1_OPM    0x08
#define TIMX_CR1_ARPE   0x80
#define TIMX_EGR_UG     0x01

volatile static STM8S105X4_TIM1_t* TIM1 = (STM8S105X4_TIM1_t*)(0x005250);
volatile static STM8S105X4_TIM2_t* TIM2 = (STM8S105X4_TIM2_t*)(0x005300);
volatile static STM8S105X4_TIM3_t* TIM3 = (STM8S105X4_TIM3_t*)(0x005320);
volatile static STM8S105X4_TIM4_t* TIM4 = (STM8S105X4_TIM4_t*)(0x005340);

void msTimer_init(uint16_t n_ms) {

    TIM3->CR1 = (uint8_t)(TIMX_CR1_ARPE);
    // Assuming 2MHz = f_master = f_ck_psc, then log2(f_master/1000) = 11
    // f_ck_cnt = f_ck_psc / (2^PSCR) ---> 1000Hz counter freq = 2MHz master freq / (2^11)
    TIM3->PSCR = (uint8_t)11;
    TIM3->ARRH = (uint8_t)((n_ms & 0xFF00) >> 8);
    TIM3->ARRL = (uint8_t)(n_ms & 0x00FF);
    TIM3->CNTRH = (uint8_t) 0;
    TIM3->CNTRL = (uint8_t) 0;
    TIM3->CR1 |= TIMX_CR1_CEN;

    return;
}
uint16_t msTimer_get_ms_elapsed() {
    return 0;
}
void msTimer_delay() {
    // Trigger update manually (clearing counter and ensuring pscr and arr are loaded)
    TIM3->EGR |= 0x01;
    // clear the interrupt flag
    TIM3->SR1 &= 0xFE;
    // Wait until update interrupt flag is set
    while(!(TIM3->SR1 & 0x1)) {
        __asm__("nop");
    }
    return;
}
void msTimer_set_delay(uint16_t n_ms) {
    TIM3->ARRH = (uint8_t)((n_ms & 0xFF00) >> 8);
    TIM3->ARRL = (uint8_t)(n_ms & 0x00FF);
    return;
}
