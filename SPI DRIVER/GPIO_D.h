// Register Definitions
#define RCC_APB_ENABLE    
#define GPIO_PORT_A       
#define GPIO_PORT_B        
#define GPIO_PORT_C      

// Input Types
#define INPUT_ANALOG       0
#define INPUT_FLOATING     1
#define INPUT_PULL         2

// Pin Definitions
#define PIN_A              1
#define PIN_B              2
#define PIN_C              3

// Pin Modes
#define PIN_INPUT          0
#define PIN_OUTPUT_10      1
#define PIN_OUTPUT_2       2
#define PIN_OUTPUT_50      3

// Output Types
#define OUTPUT_PUSH_PULL   0
#define OUTPUT_OPEN_DRAIN  1
#define OUTPUT_ALTFN_PP    2
#define OUTPUT_ALTFN_OD    3

// Pin States
#define PIN_HIGH           1
#define PIN_LOW            0

// Function Prototypes
void configurePin(unsigned short port, unsigned short pin, unsigned short direction, unsigned short options);
void initializeGPIO(unsigned short port, unsigned short pin, unsigned short mode, unsigned short type);
int readPin(unsigned short port, unsigned short pin);
void writePin(unsigned short port, unsigned short pin, unsigned short state);
void togglePin(unsigned short port, unsigned short pin);
void blinkLED(unsigned short state);
void initializeLED(void);
void setDigitalInput(unsigned short port, unsigned short pin);
void setDigitalOutput(unsigned short port, unsigned short pin);