add_library(sleep STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sleep.h)

target_sources(sleep INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/sleep.h)

target_include_directories(sleep INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Link required RP2040 hardware libraries
target_link_libraries(sleep PUBLIC  hardware_structs
                                    hardware_platform_defs
                                    pico_stdlib
                    )