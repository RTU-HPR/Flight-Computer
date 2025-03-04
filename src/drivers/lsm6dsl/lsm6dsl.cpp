#include "lsm6dsl.hpp"
#include <stdio.h>
#include <string.h>

// Platform write function
int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len) {
    uint8_t buffer[len + 1];
    buffer[0] = reg;  // Register address
    memcpy(&buffer[1], bufp, len);
    
    return i2c_write_blocking(I2C_PORT, LSM6DSL_I2C_ADDRESS, buffer, len + 1, false) < 0 ? -1 : 0;
}

// Platform read function
int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len) {
    i2c_write_blocking(I2C_PORT, LSM6DSL_I2C_ADDRESS, &reg, 1, true);  // Write register address
    return i2c_read_blocking(I2C_PORT, LSM6DSL_I2C_ADDRESS, bufp, len, false) < 0 ? -1 : 0;
}

// Initialize the LSM6DSL sensor
void lsm6dsl_init(LSM6DSL_Sensor *sensor) {
    // Initialize the device context
    sensor->dev_ctx.write_reg = platform_write;
    sensor->dev_ctx.read_reg = platform_read;
    
    // Reset device
    uint8_t rst;
    lsm6dsl_reset_set(&sensor->dev_ctx, PROPERTY_ENABLE);
    do {
        lsm6dsl_reset_get(&sensor->dev_ctx, &rst);
    } while (rst);

    // Set accelerometer output data rate and scale
    lsm6dsl_xl_data_rate_set(&sensor->dev_ctx, LSM6DSL_XL_ODR_833Hz);
    lsm6dsl_xl_full_scale_set(&sensor->dev_ctx, LSM6DSL_2g);

    // Set gyroscope output data rate and scale
    lsm6dsl_gy_data_rate_set(&sensor->dev_ctx, LSM6DSL_GY_ODR_833Hz);
    lsm6dsl_gy_full_scale_set(&sensor->dev_ctx, LSM6DSL_2000dps);
}

// Read acceleration values
void lsm6dsl_read_acc(LSM6DSL_Sensor *sensor, int16_t *acc)
{
    int16_t raw_data[3];
    lsm6dsl_acceleration_raw_get(&sensor->dev_ctx, raw_data);
    acc[0] = lsm6dsl_from_fs2g_to_mg(raw_data[0]);
    acc[1] = lsm6dsl_from_fs2g_to_mg(raw_data[1]);
    acc[2] = lsm6dsl_from_fs2g_to_mg(raw_data[2]);
}

// Read gyroscope values
void lsm6dsl_read_gyro(LSM6DSL_Sensor *sensor, int16_t *gyro)
{
    int16_t raw_data[3];
    lsm6dsl_angular_rate_raw_get(&sensor->dev_ctx, raw_data);
    gyro[0] = lsm6dsl_from_fs2000dps_to_mdps(raw_data[0]);
    gyro[1] = lsm6dsl_from_fs2000dps_to_mdps(raw_data[1]);
    gyro[2] = lsm6dsl_from_fs2000dps_to_mdps(raw_data[2]);
}

// Read temperature value
void lsm6dsl_read_temp(LSM6DSL_Sensor *sensor, float *temp) {
    int16_t raw_data;
    lsm6dsl_temperature_raw_get(&sensor->dev_ctx, &raw_data);
    *temp = lsm6dsl_from_lsb_to_celsius(raw_data);
}

void lsm6dsl_gyro_ready(LSM6DSL_Sensor *sensor, uint8_t *ready) {
    lsm6dsl_gy_flag_data_ready_get(&sensor->dev_ctx, ready);
}

void lsm6dsl_acc_ready(LSM6DSL_Sensor *sensor, uint8_t *ready) {
    lsm6dsl_xl_flag_data_ready_get(&sensor->dev_ctx, ready);
}

void lsm6dsl_temp_ready(LSM6DSL_Sensor *sensor, uint8_t *ready) {
    lsm6dsl_temp_flag_data_ready_get(&sensor->dev_ctx, ready);
}