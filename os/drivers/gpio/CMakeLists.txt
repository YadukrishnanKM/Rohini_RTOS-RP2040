file(GLOB SOURCES "*.c")

add_library(gpio STATIC ${SOURCES})
target_include_directories(gpio PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(gpio PUBLIC   hardware_regs
                                    pico_stdlib
                                    harware_structs
                                                )