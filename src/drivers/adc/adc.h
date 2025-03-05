#ifndef ADC_H
#define ADC_H

#include "hardware/adc.h"
#include "pico/stdlib.h"
#include "board_config.h"
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

// Function declarations
float read_onboard_temperature(void);
float read_battery_voltage(void);
float thermistor_read_temperature(void);

#ifdef __cplusplus
}
#endif

#endif // ADC_H