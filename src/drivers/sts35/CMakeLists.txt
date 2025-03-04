add_library(sts35 STATIC
  sts35.cpp
  sensirion_i2c_hal.c
  sensirion_i2c_hal.h
  ${CMAKE_SOURCE_DIR}/lib/embedded-i2c-sts4x/sts4x_i2c.c
  ${CMAKE_SOURCE_DIR}/lib/embedded-i2c-sts4x/sensirion_i2c.c
  ${CMAKE_SOURCE_DIR}/lib/embedded-i2c-sts4x/sensirion_common.c
)

target_include_directories(sts35 PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_SOURCE_DIR}/config
  ${CMAKE_SOURCE_DIR}/lib/embedded-i2c-sts4x
)

target_link_libraries(sts35
  pico_stdlib
  hardware_i2c
)