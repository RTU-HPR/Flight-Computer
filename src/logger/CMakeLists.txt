add_library(logger STATIC
    logger.cpp
)

target_include_directories(logger PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_SOURCE_DIR}/config
) 

target_link_libraries(logger
    pico_stdlib
    FreeRTOS-Kernel-Heap4
    sd_card
)