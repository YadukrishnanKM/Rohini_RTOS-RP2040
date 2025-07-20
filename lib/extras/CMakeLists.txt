# Add your extras logic here similarly
add_library(extras STATIC extras.cpp)  # example source
target_include_directories(extras PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})