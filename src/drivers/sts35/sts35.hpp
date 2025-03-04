#pragma once

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "board_config.h"
#include "sensirion_common.h"
#include "sensirion_i2c_hal.h"
#include "sts4x_i2c.h"

namespace sts35
{
    void sts35_init();
    void sts35_read_temp(float *temp);
}
