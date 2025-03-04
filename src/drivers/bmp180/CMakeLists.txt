add_library(bmp180 STATIC
bmp180.cpp
  ${CMAKE_SOURCE_DIR}/lib/bmp180/src/driver_bmp180.c
)

target_include_directories(bmp180 PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_SOURCE_DIR}/config
  ${CMAKE_SOURCE_DIR}/lib/bmp180/src
)

target_link_libraries(bmp180
  pico_stdlib
  hardware_i2c
)