#ifndef SPI_H
#define SPI_H

#include "stm32l432xx.h"

// Clock Initialization
void initClocks(void);

// Hardware Slave Management (HSM)
void initSPI_HSM(void);
uint8_t transferSPI_HSM(uint8_t tx_data);

// Software Slave Management (SSM)
void initSPI_SSM(void);
uint8_t transferSPI_SSM(uint8_t tx_data);

#endif
