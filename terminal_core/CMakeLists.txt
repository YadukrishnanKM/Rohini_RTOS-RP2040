file(GLOB TERMINAL_CORE_SOURCES "*.c")

add_library(terminal_core STATIC ${TERMINAL_SOURCES})
target_include_directories(terminal_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


target_link_libraries(terminal_core PUBLIC pico_stdlib terminal)