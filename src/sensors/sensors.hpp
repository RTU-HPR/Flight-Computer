#pragma once

// I2C addresses
// ONBOARD
// - 0x6B - LSM6DSL
// - 0x76 - MS5611
//
// HEATED CONTAINER
// - 0x77 - BMP180
// - 0x4B - STS35
// - 0x1F - MCP9808 

#include <stdio.h>

#include "pico/stdlib.h"

#include "FreeRTOS.h"
#include "task.h"

#include "lsm6dsl.hpp"
#include "ms5611.hpp"

void lsm6dsl_task(void *pvParameters);
void ms5611_task(void *pvParameters);