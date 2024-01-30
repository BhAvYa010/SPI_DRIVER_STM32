#include "stm32l432xx.h"
#include "SPI.h"

// Initialize peripheral clocks for SPI1
void initClocks(void)
{
  RCC->AHB2ENR |= (1u << 1) | (1u << 0); // ENABLE GPIOA and GPIOB CLOCK
  RCC->APB2ENR |= (1u << 12);             // ENABLE SPI1 CLOCK
}

/************************ Hardware Slave Management SPI Code ************************/

// Initialize SPI1 peripheral with hardware slave management
void initSPI_HSM(void)
{
    // Initialize clocks for SPI1
    initClocks();

    // Configure pins for SPI1
    configSpi1Pins_HSM();

    // Configure SPI1
    configSpi_HSM();
}

// Configure pin modes for SPI1 (hardware slave management)
void setPinMode_HSM(void)
{
    // Reset pin modes
    GPIOA->MODER &= ~((3u << (2 * 1)) | (3u << (2 * 11)) | (3u << (2 * 12)));
    GPIOB->MODER &= ~(3u << (2 * 0)); // CLEAR PB0

    // Configure pin modes
    GPIOA->MODER |= (2u << (2 * 1)) | (2u << (2 * 11)) | (2u << (2 * 12));
    GPIOB->MODER |= (2u << (2 * 0)); // SET PB0 TO AF
}

// Set alternate function for pins (hardware slave management)
void setAF_HSM(void)
{
    // Reset pin alternate function
    GPIOA->AFR[0] &= ~(15u << (4 * 1));
    GPIOA->AFR[1] &= ~(15u << (4 * 3) | 15u << (4 * 4));
    GPIOB->AFR[0] &= ~(15u << (4 * 0));

    // Set pin alternate function
    GPIOA->AFR[0] |= (5u << (4 * 1));
    GPIOA->AFR[1] |= (5u << (4 * 3) | 5u << (4 * 4));
    GPIOB->AFR[0] |= (5u << (4 * 0)); // SET SPI1 SSEL (PB0);
}

// Configure SPI1 pins (hardware slave management)
void configSpi1Pins_HSM(void)
{
    // Set pins to alternate function mode
    setPinMode_HSM();

    // Set alternate function to be SPI1
    setAF_HSM();
}

// Configure SPI1 (hardware slave management)
void configSpi_HSM(void)
{
    // Configure SPI1_CR1 register
    SPI1->CR1 &= ~((1u << 15) | (1u << 13) | (1u << 10) | (1u << 9) | (1u << 7) | (7u << 3));
    SPI1->CR1 |= (5u << 3) | (1u << 2) | (1u << 1) | (1u << 0);

    // Configure SPI1_CR2 register
    SPI1->CR2 &= ~((1u << 12) | (7u << 5) | (1u << 4) | (1u << 3) | (3u << 0));
    SPI1->CR2 |= (15u << 8) | (1u << 2);
}

// Perform SPI transaction with hardware slave management
uint8_t transferSPI_HSM(uint8_t tx_data)
{
    uint8_t rx_data = 0;

    // Enable SPI
    SPI1->CR1 |= (1u << 6);

    // Write data and dummy byte to data register
    SPI1->DR = (uint16_t)tx_data;

    // Wait until SPI is not busy and RX buffer is not empty
    while ((SPI1->SR) & (1u << 7) || !((SPI1->SR) & (1u << 0)))
        ;

    // Read a byte from the RX buffer
    rx_data = (uint8_t)SPI1->DR;

    // Disable SPI
    SPI1->CR1 &= ~(1u << 6);

    return rx_data;
}

/************************ Software Slave Management SPI Code ************************/

// Configure SPI1 pins (software slave management)
void configSpi1Pins_SSM(void)
{
    // Set pins to alternate function mode
    setPinMode_SSM();

    // Set alternate function to be SPI1
    setAF_SSM();
}

// Configure pin modes for SPI1 (software slave management)
void setPinMode_SSM(void)
{
    // Reset pin modes
    GPIOA->MODER &= ~((3u << (2 * 1)) | (3u << (2 * 11)) | (3u << (2 * 12)));
    GPIOB->MODER &= ~(3u << (2 * 0)); // CLEAR PB0

    // Configure pin modes
    GPIOA->MODER |= (2u << (2 * 1)) | (2u << (2 * 11)) | (2u << (2 * 12));
    GPIOB->MODER |= (1u << (2 * 0)); // SET PB0 TO OUTPUT MODE
}

// Set alternate function for pins (software slave management)
void setAF_SSM(void)
{
    // Reset pin alternate function
    GPIOA->AFR[0] &= ~(15u << (4 * 1));
    GPIOA->AFR[1] &= ~(15u << (4 * 3) | 15u << (4 * 4));

    // Set pin alternate function
    GPIOA->AFR[0] |= (5u << (4 * 1));
    GPIOA->AFR[1] |= (5u << (4 * 3) | 5u << (4 * 4));
}

// Initialize SPI1 peripheral with software slave management
void initSPI_SSM(void)
{
    // Initialize clocks for SPI1
    initClocks();

    // Configure pins for SPI1
    configSpi1Pins_SSM();

    // Initialize slave select high
    GPIOB->ODR |= (1u << 0);

    // Configure SPI1
    configSpi_SSM();
}

// Configure SPI1 (software slave management)
void configSpi_SSM(void)
{
    // Configure SPI1_CR1 register
    SPI1->CR1 &= ~((1u << 15) | (1u << 13) | (1u << 10) | (1u << 7) | (7u << 3));
    SPI1->CR1 |= (1u << 9) | (1u << 8) | (5u << 3) | (1u << 2) | (1u << 1) | (1u << 0);

    // Configure SPI1_CR2 register
    SPI1->CR2 &= ~((1u << 12) | (7u << 5) | (1u << 

4) | (1u << 3) | (3u << 0));
    SPI1->CR2 |= 15u << 8;

    // Enable SPI1
    SPI1->CR1 |= 1u << 6;
}

// Perform SPI transaction with software slave management
uint8_t transferSPI_SSM(uint8_t tx_data)
{
    uint8_t rx_data = 0;

    // Set slave select low
    GPIOB->ODR &= ~(1u << 0);

    // Write data and dummy byte to data register
    SPI1->DR = (uint16_t)(tx_data << 8);

    // Wait until SPI is not busy and RX buffer is not empty
    while ((SPI1->SR) & (1u << 7) || !((SPI1->SR) & (1u << 0)))
        ;

    // Read a byte from the RX buffer
    rx_data = (uint8_t)SPI1->DR;

    // Set slave select high
    GPIOB->ODR |= (1u << 0);

    return rx_data;
}
```
