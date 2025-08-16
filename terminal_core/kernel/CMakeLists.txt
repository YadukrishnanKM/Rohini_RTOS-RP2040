file(GLOB KERNEL_SOURCES "*.cpp")
add_library(kernel STATIC ${KERNEL_SOURCES})

target_include_directories(kernel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(kernel  PUBLIC    pico_stdlib_headers
                                        terminal_core
                                        scheduler
                                        hardware_irq
                                        )
