
typedef struct {
    volatile uint8_t ODR; // GPIO Output Data Latch Register Offset: 0x0
    volatile uint8_t IDR; // GPIO Input Pin Value Register Offset: 0x1
    volatile uint8_t DDR; // GPIO Data Direction Register Offset: 0x2
    volatile uint8_t CR1; // GPIO Control Register 1 Offset: 0x3
    volatile uint8_t CR2; // GPIO Control Register 2 Offset: 0x4
} STM8GPIO_t;