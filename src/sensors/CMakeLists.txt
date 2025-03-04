add_library(sensors STATIC
    sensors.cpp
)

target_include_directories(sensors PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_SOURCE_DIR}/config
) 

target_link_libraries(sensors
    pico_stdlib
    FreeRTOS-Kernel-Heap4
    lsm6dsl
)