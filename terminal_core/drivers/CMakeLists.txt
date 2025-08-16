add_subdirectory(gpio)
add_subdirectory(serial_uart)
add_subdirectory(i2c_driver)
add_subdirectory(spi_driver)
add_subdirectory(sleep)

# Optionally, group all drivers into one target
add_library(drivers INTERFACE)

target_link_libraries(drivers INTERFACE gpio)
target_link_libraries(drivers INTERFACE serial_uart)
target_link_libraries(drivers INTERFACE i2c_driver)
target_link_libraries(drivers INTERFACE spi_driver)
target_link_libraries(drivers INTERFACE sleep)

target_include_directories(drivers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/gpio)
target_include_directories(drivers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/serial_uart)
target_include_directories(drivers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/i2c_driver)
target_include_directories(drivers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/spi_driver)
target_include_directories(drivers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/sleep)