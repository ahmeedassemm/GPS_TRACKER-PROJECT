#include <stdint.h>

#include "tm4c123gh6pm.h"

void SysTick_Init(void) {
    NVIC_ST_CTRL_R = 0; // 1) disable SysTick during setup
    NVIC_ST_RELOAD_R = 0x00FFFFFF; // 2) maximum reload value
    NVIC_ST_CURRENT_R = 0; // 3) any write to current clears it
    NVIC_ST_CTRL_R = 0x00000005; // 4) enable SysTick with core clock
}

void SysTick_Wait(uint32_t delay) {
    NVIC_ST_RELOAD_R = delay - 1; // number of counts to wait
    NVIC_ST_CURRENT_R = 0; // any value written to CURRENT clears
    while ((NVIC_ST_CTRL_R & 0x00010000) == 0); // wait for count flag
}

void SysTick_Wait1s(uint32_t delay) {
    uint32_t i;
    for (i = 0; i < delay; i++) {
        SysTick_Wait(16e6); // Assuming 16MHz clock
    }
}

void SysTick_Wait1ms(uint32_t delay) {
    uint32_t i;
    for (i = 0; i < delay; i++) {
        SysTick_Wait(16e3); // Assuming 16MHz clock
    }
}

void SysTick_Wait1us(uint32_t delay) {
    uint32_t i;
    for (i = 0; i < delay; i++) {
        SysTick_Wait(16); // Assuming 16MHz clock
    }
}
