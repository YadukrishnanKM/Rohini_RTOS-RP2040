file(GLOB SVC_SOURCES "*.c" "*.s")

add_library(svc_handler STATIC ${SVC_SOURCES})

target_include_directories(svc_handler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(svc_handler PUBLIC cmsis_core hardware_sleep pico_stdlib ros_cmsis_compat)
