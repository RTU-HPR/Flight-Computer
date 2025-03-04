add_library(lsm6dsl STATIC
  lsm6dsl.cpp
  ${CMAKE_SOURCE_DIR}/lib/lsm6dsl-pid/lsm6dsl_reg.c
)

target_include_directories(lsm6dsl PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_SOURCE_DIR}/config
  ${CMAKE_SOURCE_DIR}/lib/lsm6dsl-pid
)

target_link_libraries(lsm6dsl
  pico_stdlib
  hardware_i2c
)