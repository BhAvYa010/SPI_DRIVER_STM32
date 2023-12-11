# STM32 GPIO and SPI Driver

This repository contains a set of C code files for configuring GPIO pins and using the SPI peripheral on STM32 microcontrollers. The code is designed to be used with the STM32F10x series.

## Table of Contents

- [Introduction](#introduction)
- [Requirements](#requirements)
- [Usage](#usage)
- [Functions](#functions)
- [Contributing](#contributing)
- [License](#license)

## Introduction

The code in this repository provides functions for configuring GPIO pins and interacting with the SPI peripheral on STM32 microcontrollers. It includes a GPIO driver (`GPIO_Driver.h`) and an SPI driver (`SPI.h`) with functions to initialize, transmit, and receive data.

## Requirements

- STM32F10x microcontroller
- STM32 Standard Peripheral Library
- [Optional] STM32 development environment (e.g., STM32CubeIDE, STM32CubeMX)

## Usage

1. Clone the repository:

    ```bash
    git clone https://github.com/yourusername/stm32-gpio-spi-driver.git
    cd stm32-gpio-spi-driver
    ```

2. Include the necessary files in your STM32 project:
    - Copy `GPIO_Driver.h`, `GPIO_Driver.c`, `SPI.h`, and `SPI.c` into your project directory.

3. Integrate the code into your project.

4. Configure your STM32 project to include the necessary files and build the project.

5. Use the provided functions in your application code.

## Functions

### GPIO Driver

- `configurePin(port, pin, direction, options)`: Configures a GPIO pin based on the specified parameters.
- `readPin(port, pin)`: Reads the current state of a GPIO pin.
- `writePin(port, pin, status)`: Writes a state to a GPIO pin.
- `togglePin(port, pin)`: Toggles the state of a GPIO pin.
- `controlPin(pin, status)`: Controls the state of a GPIO pin directly using the GPIOC register (assuming GPIOC is used for direct control).
- `initializeBlueLED()`: Initializes the blue LED on pin PC13.
- `controlBlueLED(state)`: Controls the state of the blue LED on pin PC13.
- `configureDigitalInput(port, pin)`: Configures a GPIO pin as a digital input.
- `configureDigitalOutput(port, pin)`: Configures a GPIO pin as a digital output.

### SPI Driver

- `initializeSPI(spiNumber)`: Initializes the SPI peripheral on the specified SPI number.
- `transmitSPI(spiNumber, txChar)`: Transmits a single character using SPI.
- `sendMessageSPI(spiNumber, message)`: Transmits a string message using SPI.

## Contributing

Feel free to contribute to this project by opening issues or submitting pull requests.

## License

This project is licensed under the [MIT License](LICENSE).
