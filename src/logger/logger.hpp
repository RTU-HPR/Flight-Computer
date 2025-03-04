
#pragma once

#include <stdio.h>

#include "pico/stdlib.h"

#include "FreeRTOS.h"
#include "task.h"

#include "sd_card.hpp"

void logger_task(void *pvParameters);