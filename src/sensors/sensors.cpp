#include "sensors.hpp"

void lsm6dsl_task(void *pvParameters)
{
  LSM6DSL_Sensor sensor;
  lsm6dsl_init(&sensor);

  struct LSM6DSL_Data
  {
    uint8_t acc_ready; 
    uint8_t gyro_ready;
    uint8_t temp_ready;
    int16_t raw_acc[3];
    int16_t raw_gyro[3];
    float acc[3];
    float gyro[3];
    float temp;
  } data;

  while (true)
  {
    bool updated = false;
    lsm6dsl_gyro_ready(&sensor, &data.gyro_ready);
    lsm6dsl_acc_ready(&sensor, &data.acc_ready);
    lsm6dsl_temp_ready(&sensor, &data.temp_ready);

    if (data.acc_ready)
    {
      lsm6dsl_read_acc(&sensor, data.raw_acc); // mg
      for (int i = 0; i < 3; i++)
      {
        data.acc[i] = data.raw_acc[i] * 9.81 / 1000.0f; // m/s^2
      }
      data.acc_ready = false;
      updated = true;
    }

    if (data.gyro_ready)
    {
      lsm6dsl_read_gyro(&sensor, data.raw_gyro); // mdps
      for (int i = 0; i < 3; i++)
      {
        data.gyro[i] = data.raw_gyro[i] * 0.0174532925 / 1000.0f; // rad/s
      }
      data.gyro_ready = false;
      updated = true;
    }

    if (data.temp_ready)
    {
      lsm6dsl_read_temp(&sensor, &data.temp); // Celsius
      data.temp_ready = false;
      updated = true;
    }
    
    // Print only if data is updated
    if (updated)
    {
      printf("Time: %.2f\n", (float)to_ms_since_boot(get_absolute_time()) / 1000.0f);
      printf("Acc: %.2f, %.2f, %.2f\n", data.acc[0], data.acc[1], data.acc[2]);
      printf("Gyro: %.2f, %.2f, %.2f\n", data.gyro[0], data.gyro[1], data.gyro[2]);
      printf("Temp: %.2f\n\n", data.temp);
    }

    vTaskDelay(1);
  }
}

void ms5611_task(void *pvParameters)
{
  printf("MS5611 Task Started\n");
  MS5611_Sensor sensor;
  printf("MS5611 Sensor Created\n");
  
  if (!ms5611_init(&sensor))
  {
    printf("MS5611 Sensor Initialization Failed\n");
    vTaskDelete(NULL);
  }

  printf("MS5611 Sensor Initialized\n");
  while (true)
  {
    float temp, pressure;
    if (ms5611_read_temp_pressure(&sensor, &temp, &pressure))
    {
    }
    printf("Time: %.2f\n", (float)to_ms_since_boot(get_absolute_time()) / 1000.0f);
    printf("Temp: %.2f\n", temp);
    printf("Pressure: %.2f\n\n", pressure);
    
    vTaskDelay(100);
  }
}