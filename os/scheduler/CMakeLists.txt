file(GLOB SCHEDULER_SOURCES "*.c")
add_library(scheduler STATIC ${SCHEDULER_SOURCES})
target_include_directories(scheduler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(scheduler PUBLIC pico_stdlib)