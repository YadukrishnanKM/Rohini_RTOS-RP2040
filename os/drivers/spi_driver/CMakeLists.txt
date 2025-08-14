file(GLOB SOURCES "*.c")

add_library(spi_driver STATIC ${SOURCES})
target_include_directories(spi_driver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(spi_driver PUBLIC hardware_spi gpio
                                                )