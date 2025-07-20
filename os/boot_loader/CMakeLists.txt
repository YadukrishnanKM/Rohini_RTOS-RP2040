file(GLOB BOOT_SOURCES "*.c")
add_library(boot_loader STATIC ${BOOT_SOURCES})

target_include_directories(boot_loader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(boot_loader PRIVATE  pico_stdlib)