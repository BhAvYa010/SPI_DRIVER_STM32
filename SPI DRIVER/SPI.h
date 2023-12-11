void initializeSPI(unsigned short spiNumber);
void transmitSPI(unsigned short spiNumber, char txChar);
void sendMessageSPI(unsigned short spiNumber, char message[]);
/*
Actual setup
SPI - 1
--> 
PA4 --> SS
PA5 --> SCLK
PA6 --> MISO
PA7 --> MOSI
SP2 - 2
PB12 --> SS
PB13 --> SCLK
PB14 --> MISO
PB15 --> MOSI
*/