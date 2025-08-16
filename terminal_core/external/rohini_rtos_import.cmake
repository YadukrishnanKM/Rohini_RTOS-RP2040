# rohini_rtos_import.cmake
# Import the ROS OS interface target for external projects

# Guard against multiple inclusion
if(TARGET ros)
    return()
endif()

# Set path to the OS root (assumes this file is in os/external/)
set(ROHINI_RTOS_ROOT "${CMAKE_CURRENT_LIST_DIR}/..")

# Add the OS source tree
add_subdirectory(${ROHINI_RTOS_ROOT} ${CMAKE_BINARY_DIR}/ros_build)

# Link the interface target
# External projects can now use: target_link_libraries(<target> ros)