#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include <pico/stdlib.h>

#include "hardware_init.hpp"
#include "sensors.hpp"
#include "logger.hpp"

int main()
{
    stdio_init_all();

    init_hardware();

    // Wait for user to press Enter
    while (true) {
      printf("Press Enter to start...\n");
      int ch = getchar_timeout_us(0);
      if (ch == PICO_ERROR_TIMEOUT) {
        // No character received yet
        sleep_ms(100);
      } else if (ch == '\r' || ch == '\n') {
        // Enter key pressed
        break;
      }
    }
    printf("Starting tasks...\n");

    xTaskCreate(logger_task, "Logger Task", 2048, NULL, 1, NULL);
    // xTaskCreate(lsm6dsl_task, "LSM6DSL Task", 256, NULL, 1, NULL);
    vTaskStartScheduler();

    panic_unsupported();  // Should never reach here
}