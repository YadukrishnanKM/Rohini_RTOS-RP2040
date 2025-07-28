add_subdirectory(terminal)
add_subdirectory(terminal_core)
add_subdirectory(scheduler)
add_subdirectory(kernel)
add_subdirectory(svc_handler)
add_subdirectory(boot_loader)

add_library(os INTERFACE)
target_include_directories(os INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/terminal
    ${CMAKE_CURRENT_SOURCE_DIR}/terminal_core
    ${CMAKE_CURRENT_SOURCE_DIR}/scheduler
    ${CMAKE_CURRENT_SOURCE_DIR}/kernel
    ${CMAKE_CURRENT_SOURCE_DIR}/svc_handler
    ${CMAKE_CURRENT_SOURCE_DIR}/boot_loader
)

# Optionally, you can combine the actual object files from submodules into another target if needed