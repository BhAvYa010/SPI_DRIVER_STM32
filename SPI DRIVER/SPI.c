#include "stm32f10x.h" 
#include "GPIO.h" 
#include "SPI.h"
void configurePinSPI(unsigned short port, unsigned short pin, unsigned short direction, unsigned short options) {
    volatile unsigned long *configRegister;
    unsigned short adjustedPin = pin;
    unsigned short offset = 0x00;

    // If the pin number is greater than 7, adjust the values accordingly.
    if (pin > 7) {
        adjustedPin -= 8;
        offset = 0x01;
    }

    // Enable the clock for the selected GPIO port.
    if (port == 1) {
        RCC_APBENR |= 0x4;
        configRegister = (volatile unsigned long *)(&GPIO_A + offset);
    } else if (port == 2) {
        RCC_APBENR |= 0x8;
        configRegister = (volatile unsigned long *)(&GPIO_B + offset);
    } else if (port == 3) {
        RCC_APBENR |= 0x10;
        configRegister = (volatile unsigned long *)(&GPIO_C + offset);
    }

    // Clear the bits corresponding to the selected pin and set the desired configuration.
    *configRegister &= ~(0xf << (adjustedPin * 4));
    *configRegister |= ((direction << (adjustedPin * 4)) | (options << (adjustedPin * 4 + 2)));
}

int readPinSPI(unsigned short port, unsigned short pin) {
    volatile unsigned long *inputDataRegister;
    unsigned long offset = 0x02;
    int state;

    // Select the appropriate GPIO port.
    if (port == 1) {
        inputDataRegister = (volatile unsigned long *)(&GPIO_A + offset);
    } else if (port == 2) {
        inputDataRegister = (volatile unsigned long *)(&GPIO_B + offset);
    } else if (port == 3) {
        inputDataRegister = (volatile unsigned long *)(&GPIO_C + offset);
    }

    // Read the state of the specified pin.
    state = ((*inputDataRegister & (1 << pin)) >> pin);

    return state;
}

void writePinSPI(unsigned short port, unsigned short pin, unsigned short status) {
    volatile unsigned long *outputDataRegister;
    unsigned long offset = 0x03;

    // Select the appropriate GPIO port.
    if (port == 1) {
        outputDataRegister = (volatile unsigned long *)(&GPIO_A + offset);
    } else if (port == 2) {
        outputDataRegister = (volatile unsigned long *)(&GPIO_B + offset);
    } else if (port == 3) {
        outputDataRegister = (volatile unsigned long *)(&GPIO_C + offset);
    }

    // Set or clear the specified pin based on the status.
    status ? (*outputDataRegister |= (status << pin)) : (*outputDataRegister &= ~(1 << pin));
}

void togglePinSPI(unsigned short port, unsigned short pin) {
    if (readPinSPI(port, pin)) {
        writePinSPI(port, pin, 0);
    } else {
        writePinSPI(port, pin, 1);
    }

}

void controlPinSPI(unsigned short pin, unsigned short status) {
    // Set or clear the specified pin based on the status.
    status ? (GPIOC->ODR |= (status << pin)) : (GPIOC->ODR &= ~(1 << pin));
}

void initializeBlueLEDSPI(void) {
    configurePinSPI(PC, 13, PIN_OUTPUT_50, OUTPUT_PUSH_PULL);
}

void controlBlueLEDSPI(unsigned short state) {
    writePinSPI(PC, 13, state);
}

void configureDigitalInputSPI(unsigned short port, unsigned short pin) {
    configurePinSPI(port, pin, PIN_INPUT, INPUT_PULL);
}

void configureDigitalOutputSPI(unsigned short port, unsigned short pin) {
    configurePinSPI(port, pin, PIN_OUTPUT_50, OUTPUT_PUSH_PULL);
}
