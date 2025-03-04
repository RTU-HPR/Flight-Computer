#pragma once

#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "board_config.h"
#include "driver_ms5611.h"


typedef struct {
    ms5611_handle_t dev_handle;
} MS5611_Sensor;

bool ms5611_init(MS5611_Sensor *sensor);
bool ms5611_read_temp_pressure(MS5611_Sensor *sensor, float *temp, float *pressure);