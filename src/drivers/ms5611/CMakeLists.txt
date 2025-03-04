add_library(ms5611 STATIC
  ms5611.cpp
  ${CMAKE_SOURCE_DIR}/lib/ms5611/src/driver_ms5611.c
)

target_include_directories(ms5611 PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_SOURCE_DIR}/config
  ${CMAKE_SOURCE_DIR}/lib/ms5611/src
)

target_link_libraries(ms5611
  pico_stdlib
  hardware_i2c
)