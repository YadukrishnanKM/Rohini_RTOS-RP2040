file(GLOB SVC_SOURCES "*.c" "*.s")

add_library(svc_handler STATIC ${SVC_SOURCES})

target_include_directories(svc_handler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Optional: Cortex-M0+ flags
# target_compile_options(svc_handler PRIVATE
#     -mcpu=cortex-m0plus
#     -mthumb
# )