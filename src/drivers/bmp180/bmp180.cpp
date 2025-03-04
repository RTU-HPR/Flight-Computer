#include "bmp180.hpp"

namespace bmp180
{
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

  uint8_t platform_i2c_deinit()
  {
    return 0;
  }

  void printf_wrapper(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
}

  bool bmp180_init(BMP180_Sensor *sensor)
  {
    printf("Initializing BMP180 sensor...\n");
    sensor->dev_handle.iic_init = platform_i2c_init;
    sensor->dev_handle.iic_deinit = platform_i2c_deinit;
    sensor->dev_handle.iic_read = platform_read;
    sensor->dev_handle.iic_write = platform_write;
    sensor->dev_handle.debug_print = printf_wrapper;
    sensor->dev_handle.delay_ms = sleep_ms;

    uint8_t res;

    res = bmp180_init(&sensor->dev_handle);
    if (res != 0)
    {
      printf("BMP180 sensor initialization failed.\n");
      return false;
    }

    res = bmp180_set_mode(&sensor->dev_handle, BMP180_MODE_ULTRA_HIGH);
    if (res != 0)
    {
      printf("BMP180 sensor set mode failed.\n");
      return false;
    }

    printf("BMP180 sensor initialized.\n");
    
    return true;
  }

  bool bmp180_read_temp_pressure(BMP180_Sensor *sensor, float *temp, uint32_t *pressure)
  {
    uint16_t temp_raw;
    uint32_t pressure_raw;

    if (bmp180_read_temperature(&sensor->dev_handle, &temp_raw, temp) != 0)
    {
      printf("BMP180 sensor read temperature failed.\n");
      return false;
    }

    if (bmp180_read_pressure(&sensor->dev_handle, &pressure_raw, pressure) != 0)
    {
      printf("BMP180 sensor read pressure failed.\n");
      return false;
    }

    return true;
  }
}