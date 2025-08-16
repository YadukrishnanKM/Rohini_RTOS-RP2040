# os/init.cmake

# Define a marker interface to indicate OS is included
add_library(os_included INTERFACE)
target_compile_definitions(os_included INTERFACE -DOS_INCLUDED=1)

# Optional: attach platform-specific settings
pico_add_platform_library(os_included)

# Add subsystems (already added in pico_sdk_import.cmake, so this is optional redundancy)
# You can skip this if import already handles it, or keep it for top-level builds
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/drivers/gpio ${CMAKE_BINARY_DIR}/os/drivers/gpio)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/drivers/i2c_driver ${CMAKE_BINARY_DIR}/os/drivers/i2c_driver)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/drivers/spi_driver ${CMAKE_BINARY_DIR}/os/drivers/spi_driver)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/drivers/serial_uart ${CMAKE_BINARY_DIR}/os/drivers/serial_uart)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/drivers/sleep ${CMAKE_BINARY_DIR}/os/drivers/sleep)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/kernel ${CMAKE_BINARY_DIR}/os/kernel)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/scheduler ${CMAKE_BINARY_DIR}/os/scheduler)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/svc_handler ${CMAKE_BINARY_DIR}/os/svc_handler)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/terminal_core ${CMAKE_BINARY_DIR}/os/terminal_core)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/terminal ${CMAKE_BINARY_DIR}/os/terminal)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_BINARY_DIR}/os/include)

# Optional: tests or examples
if (OS_TESTS_ENABLED OR OS_TOP_LEVEL_PROJECT)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/test ${CMAKE_BINARY_DIR}/os/test)
endif ()