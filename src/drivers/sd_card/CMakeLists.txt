add_library(sd_card STATIC
  sd_card.cpp
  hw_config.c
)

add_subdirectory(${CMAKE_SOURCE_DIR}/lib/FreeRTOS-FAT-CLI-for-RPi-Pico/src/FreeRTOS+FAT+CLI build)

target_include_directories(sd_card PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_SOURCE_DIR}/config
  ${CMAKE_SOURCE_DIR}/lib/no-OS-FatFS-SD-SDIO-SPI-RPi-Pico/include
  ${CMAKE_SOURCE_DIR}/lib/no-OS-FatFS-SD-SDIO-SPI-RPi-Pico/src/ff15/source
)

target_link_libraries(sd_card
  pico_stdlib
  pico_time
  FreeRTOS+FAT+CLI
)