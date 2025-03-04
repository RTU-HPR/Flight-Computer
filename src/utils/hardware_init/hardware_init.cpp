#include "hardware_init.hpp"

void init_i2c()
{
  i2c_init(I2C_PORT, I2C_SPEED);
  gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
  gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
  gpio_pull_up(I2C_SDA_PIN);
  gpio_pull_up(I2C_SCL_PIN);
}

void init_spi()
{
  spi_init(SPI_PORT, SPI_SPEED);
  gpio_set_function(SPI_SCK_PIN, GPIO_FUNC_SPI);
  gpio_set_function(SPI_MOSI_PIN, GPIO_FUNC_SPI);
  gpio_set_function(SPI_MISO_PIN, GPIO_FUNC_SPI);
  gpio_set_function(SPI_CS_PIN, GPIO_FUNC_SPI);
  gpio_set_function(SPI_CS_PIN2, GPIO_FUNC_SPI);
  gpio_set_function(SPI_CS_PIN3, GPIO_FUNC_SPI);
}

void init_gpio()
{
  gpio_init(PWR_EN_PIN);
  gpio_init(BUZZER_PIN);
  gpio_init(SWITCH_PIN);
  gpio_init(LED_PIN);
  gpio_init(GPS_RST_PIN);
  gpio_init(HEATER_PIN);
  gpio_init(RECOV1_PIN);
  gpio_init(RECOV2_PIN);
  gpio_init(PYRO1_SENSE_PIN);
  gpio_init(PYRO2_SENSE_PIN);
  gpio_init(LORA_RST_PIN);
  gpio_init(LORA_DIO1_PIN);
  gpio_init(LORA_BUSY_PIN);
  gpio_init(LORA2_RST_PIN);
  gpio_init(LORA2_DIO1_PIN);
  gpio_init(LORA2_BUSY_PIN);

  gpio_set_dir(PWR_EN_PIN, GPIO_OUT);
  gpio_set_dir(BUZZER_PIN, GPIO_OUT);
  gpio_set_dir(SWITCH_PIN, GPIO_IN);
  gpio_set_dir(LED_PIN, GPIO_OUT);
  gpio_set_dir(GPS_RST_PIN, GPIO_OUT);
  gpio_set_dir(HEATER_PIN, GPIO_OUT);
  gpio_set_dir(RECOV1_PIN, GPIO_OUT);
  gpio_set_dir(RECOV2_PIN, GPIO_OUT);
  gpio_set_dir(PYRO1_SENSE_PIN, GPIO_IN);
  gpio_set_dir(PYRO2_SENSE_PIN, GPIO_IN);
  gpio_set_dir(LORA_RST_PIN, GPIO_OUT);
  gpio_set_dir(LORA_DIO1_PIN, GPIO_IN);
  gpio_set_dir(LORA_BUSY_PIN, GPIO_IN);
  gpio_set_dir(LORA2_RST_PIN, GPIO_OUT);
  gpio_set_dir(LORA2_DIO1_PIN, GPIO_IN);
  gpio_set_dir(LORA2_BUSY_PIN, GPIO_IN);
}

void init_adc()
{
  adc_init();
  adc_gpio_init(V_SENSE_PIN);
  adc_gpio_init(THERM_PIN);
}

void enable_power()
{
  gpio_put(PWR_EN_PIN, 1);
}

void disable_power()
{
  gpio_put(PWR_EN_PIN, 0);
}

void init_hardware()
{
  init_gpio();
  enable_power();
  // disable_power();
  init_i2c();
  init_spi();
  init_adc();
}