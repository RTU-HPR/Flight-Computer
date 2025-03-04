#include "board_config.h"
#include "hw_config.h"

/* Configuration of RP2040 hardware SPI object */
static spi_t spi = {
    .hw_inst = SPI_PORT,  // RP2040 SPI component
    .sck_gpio = SPI_SCK_PIN,    // GPIO number (not Pico pin number)
    .mosi_gpio = SPI_MOSI_PIN,
    .miso_gpio = SPI_MISO_PIN,
    .baud_rate = SPI_SPEED,  // Actual frequency: 10416666.
};

/* SPI Interface */
static sd_spi_if_t spi_if = {
    .spi = &spi,  // Pointer to the SPI driving this card
    .ss_gpio = SPI_CS_PIN3  // The SPI slave select GPIO for this SD card
};

/* Configuration of the SD Card socket object */
static sd_card_t sd_card = {
    // "device_name" is arbitrary:
    .device_name = "sd0",
    // "mount_point" must be a directory off the file system's root directory and must be an absolute path:
    .mount_point = "/sd0",
    .type = SD_IF_SPI,
    .spi_if_p = &spi_if  // Pointer to the SPI interface driving this card
};

/* ********************************************************************** */

size_t sd_get_num() { return 1; }

sd_card_t *sd_get_by_num(size_t num) {
    if (0 == num) {
        return &sd_card;
    } else {
        return NULL;
    }
}