#define I2C_PORT i2c0
#define SPI_PORT spi0

#define I2C_SPEED 400000 // 400 kHz
#define SPI_SPEED 10000000 // 1 MHz

#define I2C_SDA_PIN 0
#define I2C_SCL_PIN 1

#define SPI_SCK_PIN  2
#define SPI_MOSI_PIN 3
#define SPI_MISO_PIN 4
#define SPI_CS_PIN   15
#define SPI_CS_PIN2  5
#define SPI_CS_PIN3  14

#define PWR_EN_PIN  28
#define BUZZER_PIN  16
#define SWITCH_PIN  10
#define LED_PIN     17
#define GPS_RST_PIN 6
#define HEATER_PIN  22
#define V_SENSE_PIN 26 // ADC0
#define THERM_PIN   27 // ADC1

#define RECOV1_PIN 21
#define RECOV2_PIN 20
#define PYRO1_SENSE_PIN 19
#define PYRO2_SENSE_PIN 18

// 2.4 GHz LoRa
#define LORA_RST_PIN   13
#define LORA_DIO1_PIN  12
#define LORA_BUSY_PIN  11

// 433 MHz LoRa
#define LORA2_RST_PIN  7
#define LORA2_DIO1_PIN 9
#define LORA2_BUSY_PIN 8