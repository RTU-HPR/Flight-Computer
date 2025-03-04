#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include <pico/stdlib.h>

#include "hardware_init.hpp"
#include "sensors.hpp"
// #include "logger.hpp"

// I2C reserves some addresses for special purposes. We exclude these from the scan.
// These are any addresses of the form 000 0xxx or 111 1xxx
bool reserved_addr(uint8_t addr) {
  return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

int main()
{
  stdio_init_all();

  init_hardware();

  // Wait for user to press Enter
  while (true)
  {
    printf("Press Enter to start...\n");
    int ch = getchar_timeout_us(0);
    if (ch == PICO_ERROR_TIMEOUT)
    {
      // No character received yet
      sleep_ms(100);
    }
    else if (ch == '\r' || ch == '\n')
    {
      // Enter key pressed
      break;
    }
  }
  printf("Starting tasks...\n");

  // UNCOMMENT THIS SECTION TO SCAN I2C BUS
  // printf("\nI2C Bus Scan\n");
  // printf("   0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");

  // for (int addr = 0; addr < (1 << 7); ++addr)
  // {
  //   if (addr % 16 == 0)
  //   {
  //     printf("%02x ", addr);
  //   }

  //   // Perform a 1-byte dummy read from the probe address. If a slave
  //   // acknowledges this address, the function returns the number of bytes
  //   // transferred. If the address byte is ignored, the function returns
  //   // -1.

  //   // Skip over any reserved addresses.
  //   int ret;
  //   uint8_t rxdata;
  //   if (reserved_addr(addr))
  //     ret = PICO_ERROR_GENERIC;
  //   else
  //     ret = i2c_read_blocking(i2c_default, addr, &rxdata, 1, false);

  //   printf(ret < 0 ? "." : "@");
  //   printf(addr % 16 == 15 ? "\n" : "  ");
  // }
  // printf("Done.\n");

  // while (true)
  //   ;

  // xTaskCreate(logger_task, "Logger Task", 2048, NULL, 1, NULL);
  // xTaskCreate(lsm6dsl_task, "LSM6DSL Task", 256, NULL, 1, NULL);
  xTaskCreate(ms5611_task, "MS5611 Task", 2048, NULL, 1, NULL);
  
  vTaskStartScheduler();

  panic_unsupported();  // Should never reach here
}




  