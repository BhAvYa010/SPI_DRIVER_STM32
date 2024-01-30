#include "stm32l432xx.h"
#include "Timer.h"

void initTim2(void) 
{
    // Enable TIM2 clock
    RCC->APB1ENR1 |= (1u << 0);
    
    // Leave the counter frequency unchanged
    TIM2->PSC = 0;
    
    // Set timer reload value
    TIM2->ARR = (uint32_t)4000000;
    
    // Set initial counter value
    TIM2->CNT = 0;
    
    // Enable TIM2 counter
    TIM2->CR1 |= (1u << 0);
}

void delay1Sec(void)
{
    unsigned int counter = 0;
    unsigned int goalCount = 4000000;
    unsigned int currentCntVal = 0;
    unsigned int prevCntVal = 0;
    unsigned int countToAdd = 0;
    
    // Get initial value of CNT
    prevCntVal = TIM2->CNT; 
    
    // Loop until counter is equal or exceeds goal count
    while(counter < goalCount)
    {
        // Get newest count
        currentCntVal = TIM2->CNT;
        
        // Handle situation where TIM2_CNT resets
        if(currentCntVal < prevCntVal)
        {
            // Get the count before the CNT register reset and then 
            // add the count after it reset to get elapsed count
            countToAdd = (4000000 - prevCntVal) + currentCntVal;
        }
        else
        {
            // Subtract current count from previous count to get
            // elapsed count
            countToAdd = currentCntVal - prevCntVal;
        }
        
        // Add elapsed count to the counter
        counter += countToAdd;
        
        // Current count now becomes previous count
        prevCntVal = currentCntVal;
    }
}

void delay(unsigned int ms)
{
    unsigned int counter = 0;
    unsigned int goalCount = ms * 4000u;
    unsigned int currentCntVal = 0;
    unsigned int prevCntVal = 0;
    unsigned int countToAdd = 0;
    
    // Get initial value of CNT
    prevCntVal = TIM2->CNT; 
    
    // Loop until counter is equal or exceeds goal count
    while(counter < goalCount)
    {
        // Get newest count
        currentCntVal = TIM2->CNT;
        
        // Handle situation where TIM2_CNT resets
        if(currentCntVal < prevCntVal)
        {
            // Get the count before the CNT register reset and then 
            // add the count after it reset to get elapsed count
            countToAdd = (4000000 - prevCntVal) + currentCntVal;
        }
        else
        {
            // Subtract current count from previous count to get
            // elapsed count
            countToAdd = currentCntVal - prevCntVal;
        }
        
        // Add elapsed count to the counter
        counter += countToAdd;
        
        // Current count now becomes previous count
        prevCntVal = currentCntVal;
    }
}

void delayUs(unsigned int us)
{
    unsigned int counter = 0;
    unsigned int goalCount = us * 4;
    unsigned int currentCntVal = 0;
    unsigned int prevCntVal = 0;
    unsigned int countToAdd = 0;
    
    // Get initial value of CNT
    prevCntVal = TIM2->CNT; 
    
    // Loop until counter is equal or exceeds goal count
    while(counter < goalCount)
    {
        // Get newest count
        currentCntVal = TIM2->CNT;
        
        // Handle situation where TIM2_CNT resets
        if(currentCntVal < prevCntVal)
        {
            // Get the count before the CNT register reset and then 
            // add the count after it reset to get elapsed count
            countToAdd = (4000000 - prevCntVal) + currentCntVal;
        }
        else
        {
            // Subtract current count from previous count to get
            // elapsed count
            countToAdd = currentCntVal - prevCntVal;
        }
        
        // Add elapsed count to the counter
        counter += countToAdd;
        
        // Current count now becomes previous count
        prevCntVal = currentCntVal;
    }
}
