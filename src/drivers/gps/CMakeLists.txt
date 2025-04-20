add_library(gps STATIC
  gps.cpp
  # ${CMAKE_SOURCE_DIR}/lib/PX4-GPSDrivers/src/gps_helper.cpp
)

target_include_directories(bmp180 PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_SOURCE_DIR}/config
  ${CMAKE_SOURCE_DIR}/lib/PX4-GPSDrivers/src
)

target_link_libraries(gps
  pico_stdlib
  hardware_i2c
)