#pragma once

#include <stdio.h>

#include "pico/stdlib.h"

#include "FreeRTOS.h"
#include "task.h"

#include "lsm6dsl.hpp"

void lsm6dsl_task(void *pvParameters);