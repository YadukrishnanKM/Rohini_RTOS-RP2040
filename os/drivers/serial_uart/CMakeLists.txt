file(GLOB SOURCES "*.c")

add_library(serial_uart STATIC ${SOURCES})
target_include_directories(serial_uart PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(serial_uart PUBLIC pico_stdlib
                                                )