add_library(adc STATIC
    adc.h
    adc.c
)

target_include_directories(adc PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_SOURCE_DIR}/config
) 

target_link_libraries(adc
    pico_stdlib
    hardware_adc
)