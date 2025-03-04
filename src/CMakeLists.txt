# Define the executable
add_executable(${PROJECT_NAME} main.cpp)

# Include paths to source files
target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_SOURCE_DIR}/config
)

# Add subdirectories under src
add_subdirectory(utils)
add_subdirectory(drivers)
add_subdirectory(sensors)
add_subdirectory(logger)

# Link the executable to the libraries
target_link_libraries(${PROJECT_NAME}
    pico_stdlib 
    FreeRTOS-Kernel-Heap4 
    hardware_init
    sensors
    logger
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    USE_PRINTF
)

set_property(TARGET ${PROJECT_NAME} APPEND_STRING PROPERTY LINK_FLAGS
    "-Wl,--print-memory-usage"
)

# Enable/disable output over UART/USB
pico_enable_stdio_uart(FlightComputer 0)
pico_enable_stdio_usb(FlightComputer 1)

pico_set_program_name(${PROJECT_NAME} "${PROJECT_NAME}")
pico_set_program_version(${PROJECT_NAME} "0.1")

pico_add_extra_outputs(FlightComputer)