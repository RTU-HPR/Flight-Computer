#pragma once

#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "board_config.h"
#include "lsm6dsl_reg.h"  // ST driver

#define LSM6DSL_I2C_ADDRESS  0x6B  // 0x6A or 0x6B

typedef struct {
    stmdev_ctx_t dev_ctx;
} LSM6DSL_Sensor;

void lsm6dsl_init(LSM6DSL_Sensor *sensor);
void lsm6dsl_read_acc(LSM6DSL_Sensor *sensor, int16_t *acc);
void lsm6dsl_read_gyro(LSM6DSL_Sensor *sensor, int16_t *gyro);
void lsm6dsl_read_temp(LSM6DSL_Sensor *sensor, float *temp);
void lsm6dsl_gyro_ready(LSM6DSL_Sensor *sensor, uint8_t *ready);
void lsm6dsl_acc_ready(LSM6DSL_Sensor *sensor, uint8_t *ready);
void lsm6dsl_temp_ready(LSM6DSL_Sensor *sensor, uint8_t *ready);
