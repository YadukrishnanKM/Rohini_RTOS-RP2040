file(GLOB TERMINAL_SOURCES "*.c")
add_library(terminal STATIC ${TERMINAL_SOURCES})
target_include_directories(terminal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(terminal PUBLIC pico_stdlib)