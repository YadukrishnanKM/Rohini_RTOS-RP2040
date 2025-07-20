add_subdirectory(drivers)

add_library(lib INTERFACE)
target_link_libraries(lib INTERFACE drivers)