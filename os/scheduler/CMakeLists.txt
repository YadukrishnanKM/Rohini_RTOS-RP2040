file(GLOB SCHEDULER_SOURCES "*.c")
add_library(scheduler STATIC ${SCHEDULER_SOURCES})
target_include_directories(terminal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})