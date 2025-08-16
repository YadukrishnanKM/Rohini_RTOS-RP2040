cmake_minimum_required(VERSION 3.13)
project(ros C CXX ASM)

# Set C and C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Enable interface targets for modular SDK-style reuse
set(ROS_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(ROS_DRIVERS ${ROS_ROOT}/drivers)
set(ROS_KERNEL ${ROS_ROOT}/kernel)
set(ROS_SCHEDULER ${ROS_ROOT}/scheduler)
set(ROS_SVC_HANDLER ${ROS_ROOT}/svc_handler)
set(ROS_TERMINAL ${ROS_ROOT}/terminal)
set(ROS_TERMINAL_CORE ${ROS_ROOT}/terminal_core)
set(ROS_CMSIS_COMPAT ${ROS_ROOT}/ros_cmsis_compat)

# Add subdirectories
add_subdirectory(kernel)
add_subdirectory(scheduler)
add_subdirectory(svc_handler)
add_subdirectory(terminal)
add_subdirectory(terminal_core)
add_subdirectory(drivers)
add_subdirectory(ros_cmsis_compat)

# Create an interface target for the whole OS
add_library(ros INTERFACE)

# Link all subsystems to the interface target
target_link_libraries(ros INTERFACE
    kernel
    scheduler
    svc_handler
    terminal
    terminal_core
    gpio
    i2c_driver
    serial_uart
    sleep
    spi_driver

)

# Include directories for consumers
target_include_directories(ros INTERFACE
    ${ROS_KERNEL}
    ${ROS_SCHEDULER}
    ${ROS_SVC_HANDLER}
    ${ROS_TERMINAL}
    ${ROS_TERMINAL_CORE}
    ${ROS_DRIVERS}/gpio
    ${ROS_DRIVERS}/i2c_driver
    ${ROS_DRIVERS}/serial_uart
    ${ROS_DRIVERS}/sleep
    ${ROS_DRIVERS}/spi_driver
    ${ROS_CMSIS_COMPAT}
)

# Optional: Add Liquid_Crystal_RP as an external dependency