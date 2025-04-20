
#pragma once

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include "pico/stdlib.h"
#include "pico/time.h"  
#include "hardware/i2c.h"

#define GPS_INFO(...) printf(__VA_ARGS__)
#define GPS_WARN(...) printf(__VA_ARGS__)
#define GPS_ERR(...)  printf(__VA_ARGS__)

#define M_DEG_TO_RAD (M_PI / 180.0)
#define M_RAD_TO_DEG (180.0 / M_PI)
#define M_DEG_TO_RAD_F 0.0174532925f
#define M_RAD_TO_DEG_F 57.2957795f

#define M_PI_2_F 0.63661977f

static inline void gps_usleep(unsigned long usecs)
{
    sleep_us(usecs);
}

typedef uint64_t gps_abstime;
static inline gps_abstime gps_absolute_time()
{
    return get_absolute_time();
}

struct satellite_info_s
{
  uint64_t timestamp;
  static constexpr uint8_t SAT_INFO_MAX_SATELLITES = 20;

  uint8_t count;
  uint8_t svid[20];
  uint8_t used[20];
  uint8_t elevation[20];
  uint8_t azimuth[20];
  uint8_t snr[20];
  uint8_t prn[20];
};

struct sensor_gnss_relative_s
{
  uint64_t timestamp;
  uint64_t timestamp_sample;

  uint32_t device_id;

  uint64_t time_utc_usec;

  uint16_t reference_station_id;

  float position[3];
  float position_accuracy[3];

  float heading;
  float heading_accuracy;

  float position_length;
  float accuracy_length;

  bool gnss_fix_ok;
  bool differential_solution;
  bool relative_position_valid;
  bool carrier_solution_floating;
  bool carrier_solution_fixed;
  bool moving_base_mode;
  bool reference_position_miss;
  bool reference_observations_miss;
  bool heading_valid;
  bool relative_position_normalized;
};

struct sensor_gps_s
{
  uint64_t timestamp;
  uint64_t timestamp_sample;

  uint32_t device_id;

  double latitude_deg;
  double longitude_deg;
  double altitude_msl_m;
  double altitude_ellipsoid_m;

  float s_variance_m_s;
  float c_variance_rad;

  static constexpr uint8_t FIX_TYPE_NONE = 1;
  static constexpr uint8_t FIX_TYPE_2D = 2;
  static constexpr uint8_t FIX_TYPE_3D = 3;
  static constexpr uint8_t FIX_TYPE_RTCM_CODE_DIFFERENTIAL = 4;
  static constexpr uint8_t FIX_TYPE_RTK_FLOAT = 5;
  static constexpr uint8_t FIX_TYPE_RTK_FIXED = 6;
  static constexpr uint8_t FIX_TYPE_EXTRAPOLATED = 8;
  uint8_t fix_type;

  float eph;
  float epv;

  float hdop;
  float vdop;

  int32_t noise_per_ms;
  uint16_t automatic_gain_control;

  static constexpr uint8_t JAMMING_STATE_UNKNOWN = 0;
  static constexpr uint8_t JAMMING_STATE_OK = 1;
  static constexpr uint8_t JAMMING_STATE_WARNING = 2;
  static constexpr uint8_t JAMMING_STATE_CRITICAL = 3;
  uint8_t jamming_state;
  int32_t jamming_indicator;

  static constexpr uint8_t SPOOFING_STATE_UNKNOWN = 0;
  static constexpr uint8_t SPOOFING_STATE_NONE = 1;
  static constexpr uint8_t SPOOFING_STATE_INDICATED = 2;
  static constexpr uint8_t SPOOFING_STATE_MULTIPLE = 3;
  uint8_t spoofing_state;

  float vel_m_s;
  float vel_n_m_s;
  float vel_e_m_s;
  float vel_d_m_s;
  float cog_rad;
  bool vel_ned_valid;

  int32_t timestamp_time_relative;
  uint64_t time_utc_usec;

  uint8_t satellites_used;

  float heading;
  float heading_offset;
  float heading_accuracy;

  float rtcm_injection_rate;
  uint8_t selected_rtcm_instance;

  bool rtcm_crc_failed;

  static constexpr uint8_t RTCM_MSG_USED_UNKNOWN = 0;
  static constexpr uint8_t RTCM_MSG_USED_NOT_USED = 1;
  static constexpr uint8_t RTCM_MSG_USED_USED = 2;
  uint8_t rtcm_msg_used;
};