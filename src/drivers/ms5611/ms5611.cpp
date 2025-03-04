#include "ms5611.hpp"

// Platform write function
uint8_t platform_write(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
  uint8_t buffer[len + 1];
  buffer[0] = reg; // Register address
  memcpy(&buffer[1], buf, len);
  return i2c_write_blocking(I2C_PORT, addr, buffer, len + 1, false) < 0 ? -1 : 0;
}

// Platform read function
uint8_t platform_read(uint8_t addr, uint8_t reg, uint8_t *bufp, uint16_t len)
{
  i2c_write_blocking(I2C_PORT, addr, &reg, 1, true); // Write register address
  return i2c_read_blocking(I2C_PORT, addr, bufp, len, false) < 0 ? -1 : 0;
}

uint8_t platform_i2c_init()
{
  return 0;
}

// Wrapper for printf that returns void
void printf_wrapper(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
}

bool ms5611_init(MS5611_Sensor *sensor)
{
  printf("Initializing MS5611 sensor...\n");
  sensor->dev_handle.iic_init = platform_i2c_init;
  sensor->dev_handle.iic_read = platform_read;
  sensor->dev_handle.iic_write = platform_write;
  sensor->dev_handle.debug_print = printf_wrapper;
  sensor->dev_handle.delay_ms = sleep_ms;

  uint8_t res;

  printf("Setting interface...\n");
  res = ms5611_set_interface(&sensor->dev_handle, MS5611_INTERFACE_IIC);
  if (res != 0)
  {
    printf("set interface failed.\n");
    return false;
  }

  printf("Setting address pin...\n");
  res = ms5611_set_addr_pin(&sensor->dev_handle, MS5611_ADDRESS_CSB_1);
  if (res != 0)
  {
    printf("set addr pin failed.\n");
    return false;
  }

  printf("Initializing sensor...\n");
  res = ms5611_init(&sensor->dev_handle);
  if (res != 0)
  { 
    printf("init failed.\n");
    return false;
  }

  printf("Setting temperature osr...\n");
  res = ms5611_set_temperature_osr(&sensor->dev_handle, MS5611_OSR_256);
  if (res != 0)
  {
    printf("set temperature osr failed.\n");
    return false;
  }

  printf("Setting pressure osr...\n");
  res = ms5611_set_pressure_osr(&sensor->dev_handle, MS5611_OSR_256);
  if (res != 0)
  {
    printf("set pressure osr failed.\n");
    return false;
  }

  return true;
}

bool ms5611_read_temp_pressure(MS5611_Sensor *sensor, float *temp, float *pressure)
{
  uint8_t res;
  uint32_t temperature_raw;
  uint32_t pressure_raw;

  res = ms5611_read_temperature_pressure(&sensor->dev_handle, &temperature_raw, temp, &pressure_raw, pressure);
  if (res != 0)
  {
    return false;
  }

  return true;
}