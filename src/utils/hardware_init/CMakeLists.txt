add_library(hardware_init STATIC
    hardware_init.cpp
)

target_include_directories(hardware_init PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_SOURCE_DIR}/config
) 

target_link_libraries(hardware_init
    pico_stdlib
    hardware_i2c
    hardware_spi
    hardware_adc
    hardware_pwm
)