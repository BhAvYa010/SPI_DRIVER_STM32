# STM32 SPI Driver

This repository contains a simple C code implementation for configuring and using the SPI peripheral on STM32 microcontrollers. The code is designed to be used with the STM32F10x series.

## Overview

This project focuses on providing a lightweight SPI driver for STM32 microcontrollers. It includes functions for initializing the SPI peripheral, transmitting a single character, and sending a string message over SPI.

## Usage

To integrate this SPI driver into your STM32 project:

1. Copy the files `SPI.h` and `SPI.c` into your project directory.

2. Include `SPI.h` in your application code:

    ```c
    #include "SPI.h"
    ```

3. Call the provided functions to initialize and use the SPI peripheral:

    ```c
    // Example: Initialize SPI1
    initializeSPI(1);

    // Example: Transmit a single character over SPI1
    transmitSPI(1, 'A');

    // Example: Send a string message over SPI1
    char message[] = "Hello, SPI!";
    sendMessageSPI(1, message);
    ```

## Functions

- `initializeSPI(spiNumber)`: Initializes the SPI peripheral on the specified SPI number.
- `transmitSPI(spiNumber, txChar)`: Transmits a single character using SPI.
- `sendMessageSPI(spiNumber, message)`: Transmits a string message using SPI.

## Requirements

- STM32F10x microcontroller
- STM32 Standard Peripheral Library
- [Optional] STM32 development environment (e.g., STM32CubeIDE, STM32CubeMX)

