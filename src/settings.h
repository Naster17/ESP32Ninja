/*BUILD MODE*/
#define DEBUG
#define ENABLE_IR

#ifdef ENABLE_IR
#define IR_RECEIVER_PIN 22
#define IR_TRANSMITTER_PIN 21
#define IR_CAPTURE_BUFFER_SIZE 1024
#endif

/* PINS */
#define BUTTON_UP_PIN 32
#define BUTTON_DOWN_PIN 26
#define BUTTON_LEFT_PIN 33  
#define BUTTON_RIGHT_PIN 27 
#define BUTTON_OK_PIN 25    
#define BUTTON_FREE_PIN 36

#define TFT_CS 17  // Пин для CS (Chip Select)
#define TFT_RST 2  // Пин для RESET
#define TFT_DC 4   // Пин для A0 (Data/Command)
#define TFT_SDA 23 // Пин для SDA
#define TFT_SCL 18 // Пин для SCK
#define TFT_LED 15 // Пример пина на ESP32 для управления подсветкой дисплея

#define SD_CS_PIN 5

/* PRESS CODES */
#define UP_PRESS 1
#define DOWN_PRESS 2
#define LEFT_PRESS 3
#define RIGHT_PRESS 4
#define OK_PRESS 5
#define FREE_PRESS 6
#define EMPTY_PRESS 0

#define UP_LONG_PRESS 11
#define DOWN_LONG_PRESS 22
#define LEFT_LONG_PRESS 33
#define RIGHT_LONG_PRESS 44
#define OK_LONG_PRESS 55
#define FREE_LONG_PRESS 66

/*INIT ERRORS*/
#define INIT_ERROR_BUTTONS 1
#define INIT_ERROR_SCREEN 1