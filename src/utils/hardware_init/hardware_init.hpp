#pragma once

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

#include "board_config.h"

void init_i2c();
void init_spi();
void init_gpio();
void init_adc();

void init_hardware();