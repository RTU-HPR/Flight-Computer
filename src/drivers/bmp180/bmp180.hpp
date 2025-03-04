#pragma once

#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "board_config.h"
#include "driver_bmp180.h"

namespace bmp180
{
  typedef struct {
      bmp180_handle_t dev_handle;
  } BMP180_Sensor;
  
  bool bmp180_init(BMP180_Sensor *sensor);
  bool bmp180_read_temp_pressure(BMP180_Sensor *sensor, float *temp, uint32_t *pressure);
}
