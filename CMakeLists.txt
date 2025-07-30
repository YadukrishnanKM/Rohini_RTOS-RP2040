cmake_minimum_required(VERSION 3.13)


# initialize the SDK based on PICO_SDK_PATH
set(PICO_SDK_PATH "${CMAKE_CURRENT_SOURCE_DIR}/pico-sdk")
set(PICO_EXTRAS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/pico-extras")
set(PICOTOOL_FETCH_FROM_GIT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/picotool")

#--------------------------------------------------------------------------------------------------------
# Check if PICO_SDK_PATH is set and exists
if (NOT EXISTS ${PICO_SDK_PATH})
    message(FATAL_ERROR "PICO_SDK_PATH does not exist: ${PICO_SDK_PATH}")
endif()

# Check if PICO_SDK_PATH is defined and is a directory
if (NOT DEFINED PICO_SDK_PATH)
    message(FATAL_ERROR "PICO_SDK_PATH is not defined. Please set it to the path of your Pico SDK.")
endif()

# Check if PICO_SDK_PATH is a directory
if (NOT IS_DIRECTORY ${PICO_SDK_PATH})
    message(FATAL_ERROR "PICO_SDK_PATH is not a directory: ${PICO_SDK_PATH}")
endif()

# Print the PICO_SDK_PATH for debugging purposes
message("\n\n\n PICO_SDK_PATH: ${PICO_SDK_PATH} \n\n")
#--------------------------------------------------------------------------------------------------------

# Include the Pico SDK import file
include("${PICO_SDK_PATH}/external/pico_sdk_import.cmake")

# Include the Pico Extras import file
include("${PICO_EXTRAS_PATH}/external/pico_extras_import.cmake")


project("ros" LANGUAGES C CXX ASM)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
#--------------------------------------------------------------------------------------------------------

# Add the executable target
add_executable(${PROJECT_NAME}
    src/main.cpp
)

# Add the source files for the project
include_directories(${PROJECT_NAME}
    ${PICO_SDK_PATH}/src/rp2_common/cmsis/include
)

# Link the os libraries to the executable
add_subdirectory(os)

add_subdirectory(lib)

target_link_libraries(${PROJECT_NAME} PUBLIC pico_stdlib hardware_i2c lib terminal_core scheduler kernel svc_handler)
#--------------------------------------------------------------------------------------------------------

# Enable USB output, UART, etc. if needed
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)


# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(${PROJECT_NAME})