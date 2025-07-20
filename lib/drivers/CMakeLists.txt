add_subdirectory(Liquid_Crystal_RP)

# Optionally, group all drivers into one target
add_library(drivers INTERFACE)

target_link_libraries(drivers INTERFACE Liquid_Crystal_RP)

target_include_directories(drivers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/Liquid_Crystal_RP)