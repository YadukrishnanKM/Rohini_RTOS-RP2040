
add_library(ros_cmsis_compat INTERFACE)

target_include_directories(ros_cmsis_compat INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ros_cmsis_compat  INTERFACE hardware_regs cmsis_core)
