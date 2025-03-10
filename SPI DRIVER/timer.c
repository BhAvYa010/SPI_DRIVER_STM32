#include "Timer.h"
#include "stm32l432xx.h"

void initTim2(void) {
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;  // Enable TIM2 clock
    TIM2->PSC = 79;                         // Prescaler for 1 MHz clock (assuming 80 MHz system clock)
    TIM2->ARR = 0xFFFFFFFF;                 // Auto-reload at max value
    TIM2->CR1 |= TIM_CR1_CEN;               // Enable timer
}

void delay(uint32_t ms) {
    uint32_t start = TIM2->CNT;
    while((TIM2->CNT - start) < (ms * 1000));  // Wait for specified milliseconds
}
