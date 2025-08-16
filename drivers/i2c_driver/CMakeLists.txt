file(GLOB SOURCES "*.c")

add_library(i2c_driver STATIC ${SOURCES})
target_include_directories(i2c_driver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(i2c_driver PUBLIC hardware_i2c gpio
                                                )