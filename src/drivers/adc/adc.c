#include "adc.h"

float read_onboard_temperature() {
  adc_select_input(4);
  uint16_t raw = adc_read();
  float voltage = (raw / 4095.0f) * 3.3f;
  float tempC = 27.0f - (voltage - 0.706f) / 0.001721f;
  return tempC;
}

float read_battery_voltage() {
  adc_select_input(V_SENSE_PIN-26);
  uint16_t raw = adc_read();
  float voltage = (raw / 4095.0f) * 3.3f;
  float battery_voltage = voltage * ((V_SENSE_R1 + V_SENSE_R2) / V_SENSE_R1);
  return battery_voltage;
}

float thermistor_read_temperature() {
  adc_select_input(THERM_PIN-26);
  uint16_t raw = adc_read();
  float voltage = (raw / 4095.0f) * 3.3f;
  float resistance = THERMISTOR_SERIES_RESISTOR * ((3.3f / voltage) - 1.0f);
  
  // Convert resistance to temperature using the Steinhart-Hart equation
  float temperature = 1.0f / ((1.0f / THERMISTOR_BETA) + (log(resistance / THERMISTOR_NOMINAL) / THERMISTOR_BETA));
  return temperature - 273.15f;  // Convert Kelvin to Celsius
}