#include "SPI.h"

// Clock Initialization
void initClocks(void) {
    RCC->AHB2ENR |= (1u << 1) | (1u << 0);  // Enable GPIOA and GPIOB clocks
    RCC->APB2ENR |= (1u << 12);             // Enable SPI1 clock
}

/********************** Hardware Slave Management **********************/
static void configSpi1Pins_HSM(void) {
    // Configure GPIO modes
    GPIOA->MODER &= ~(GPIO_MODER_MODE1 | GPIO_MODER_MODE11 | GPIO_MODER_MODE12);
    GPIOB->MODER &= ~GPIO_MODER_MODE0;
    
    GPIOA->MODER |= (2u << GPIO_MODER_MODE1_Pos)  |  // PA1: AF mode
                    (2u << GPIO_MODER_MODE11_Pos) |  // PA11: AF mode
                    (2u << GPIO_MODER_MODE12_Pos);   // PA12: AF mode
    GPIOB->MODER |= (2u << GPIO_MODER_MODE0_Pos);    // PB0: AF mode

    // Configure alternate functions (AF5 for SPI1)
    GPIOA->AFR[0] = (GPIOA->AFR[0] & ~GPIO_AFRL_AFSEL1) | (5u << GPIO_AFRL_AFSEL1_Pos);
    GPIOA->AFR[1] = (GPIOA->AFR[1] & ~(GPIO_AFRH_AFSEL11 | GPIO_AFRH_AFSEL12)) |
                    (5u << GPIO_AFRH_AFSEL11_Pos) | (5u << GPIO_AFRH_AFSEL12_Pos);
    GPIOB->AFR[0] = (GPIOB->AFR[0] & ~GPIO_AFRL_AFSEL0) | (5u << GPIO_AFRL_AFSEL0_Pos);
}

static void configSpi_HSM(void) {
    // SPI configuration
    SPI1->CR1 = SPI_CR1_BR_2 | SPI_CR1_BR_0 |  // Baud rate: fPCLK/32 (0b101)
                SPI_CR1_MSTR |                 // Master mode
                SPI_CR1_CPOL |                 // CPOL = 1
                SPI_CR1_CPHA;                  // CPHA = 1

    SPI1->CR2 = SPI_CR2_FRXTH |                // RXNE event on 8-bit reception
                (7u << SPI_CR2_DS_Pos);        // 8-bit data size (0b0111)
}

void initSPI_HSM(void) {
    initClocks();
    configSpi1Pins_HSM();
    configSpi_HSM();
    SPI1->CR1 |= SPI_CR1_SPE;  // Enable SPI
}

uint8_t transferSPI_HSM(uint8_t tx_data) {
    SPI1->DR = tx_data;  // Start transmission
    
    // Wait for transmission complete
    while(SPI1->SR & SPI_SR_BSY); 
    while(!(SPI1->SR & SPI_SR_RXNE));
    
    return (uint8_t)SPI1->DR;
}

/********************** Software Slave Management **********************/
static void configSpi1Pins_SSM(void) {
    // Configure GPIO modes
    GPIOA->MODER &= ~(GPIO_MODER_MODE1 | GPIO_MODER_MODE11 | GPIO_MODER_MODE12);
    GPIOB->MODER &= ~GPIO_MODER_MODE0;
    
    GPIOA->MODER |= (2u << GPIO_MODER_MODE1_Pos)  |  // PA1: AF mode
                    (2u << GPIO_MODER_MODE11_Pos) |  // PA11: AF mode
                    (2u << GPIO_MODER_MODE12_Pos);   // PA12: AF mode
    GPIOB->MODER |= (1u << GPIO_MODER_MODE0_Pos);   // PB0: Output mode

    // Configure alternate functions (AF5 for SPI1)
    GPIOA->AFR[0] = (GPIOA->AFR[0] & ~GPIO_AFRL_AFSEL1) | (5u << GPIO_AFRL_AFSEL1_Pos);
    GPIOA->AFR[1] = (GPIOA->AFR[1] & ~(GPIO_AFRH_AFSEL11 | GPIO_AFRH_AFSEL12)) |
                    (5u << GPIO_AFRH_AFSEL11_Pos) | (5u << GPIO_AFRH_AFSEL12_Pos);
}

static void configSpi_SSM(void) {
    // SPI configuration
    SPI1->CR1 = SPI_CR1_SSM |                  // Software slave management
                SPI_CR1_SSI |                  // Internal slave select
                SPI_CR1_BR_2 | SPI_CR1_BR_0 |  // Baud rate: fPCLK/32
                SPI_CR1_MSTR |                 // Master mode
                SPI_CR1_CPOL |                 // CPOL = 1
                SPI_CR1_CPHA;                  // CPHA = 1

    SPI1->CR2 = SPI_CR2_FRXTH |                // RXNE event on 8-bit reception
                (7u << SPI_CR2_DS_Pos);        // 8-bit data size (0b0111)
}

void initSPI_SSM(void) {
    initClocks();
    configSpi1Pins_SSM();
    configSpi_SSM();
    GPIOB->ODR |= (1u << 0);  // Initialize NSS high
    SPI1->CR1 |= SPI_CR1_SPE; // Enable SPI
}

uint8_t transferSPI_SSM(uint8_t tx_data) {
    GPIOB->ODR &= ~(1u << 0);  // Assert NSS (low)
    
    SPI1->DR = tx_data;         // Start transmission
    
    // Wait for transmission complete
    while(SPI1->SR & SPI_SR_BSY);
    while(!(SPI1->SR & SPI_SR_RXNE));
    
    GPIOB->ODR |= (1u << 0);   // Release NSS (high)
    return (uint8_t)SPI1->DR;
}
