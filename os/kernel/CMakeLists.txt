file(GLOB KERNEL_SOURCES "*.cpp")
add_library(kernel STATIC ${KERNEL_SOURCES})
target_include_directories(terminal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})