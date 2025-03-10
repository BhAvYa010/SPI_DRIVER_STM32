#include "stm32l432xx.h"
#include "SPI.h"
#include "Timer.h"

int main(void) {
    uint8_t data[4] = {187, 188, 189, 190};
    uint8_t rxd;
    
    initTim2();        // Initialize timer
    initSPI_SSM();     // Initialize SPI with software slave management
    
    while(1) {
        rxd = transferSPI_SSM(data[0]);  // Transfer data
        delay(50);                       // 50ms delay
    }
}
