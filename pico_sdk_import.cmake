# This is a copy-style import file for your OS project, similar to pico-extras
# It should be include()ed prior to project()

# Allow environment overrides
if (DEFINED ENV{PICO_SDK_PATH} AND (NOT PICO_SDK_PATH))
    set(PICO_SDK_PATH $ENV{PICO_SDK_PATH})
    message("Using PICO_SDK_PATH from environment ('${PICO_SDK_PATH}')")
endif ()

if (DEFINED ENV{OS_FETCH_FROM_GIT} AND (NOT OS_FETCH_FROM_GIT))
    set(OS_FETCH_FROM_GIT $ENV{OS_FETCH_FROM_GIT})
    message("Using OS_FETCH_FROM_GIT from environment ('${OS_FETCH_FROM_GIT}')")
endif ()

if (DEFINED ENV{OS_FETCH_FROM_GIT_PATH} AND (NOT OS_FETCH_FROM_GIT_PATH))
    set(OS_FETCH_FROM_GIT_PATH $ENV{OS_FETCH_FROM_GIT_PATH})
    message("Using OS_FETCH_FROM_GIT_PATH from environment ('${OS_FETCH_FROM_GIT_PATH}')")
endif ()

# Cache variables
set(PICO_SDK_PATH "${PICO_SDK_PATH}" CACHE PATH "Path to the Raspberry Pi Pico SDK")
set(OS_FETCH_FROM_GIT "${OS_FETCH_FROM_GIT}" CACHE BOOL "Set to ON to fetch OS from git if not otherwise locatable")
set(OS_FETCH_FROM_GIT_PATH "${OS_FETCH_FROM_GIT_PATH}" CACHE FILEPATH "Location to download OS")

# Fetch Pico SDK if needed
if (NOT PICO_SDK_PATH)
    if (OS_FETCH_FROM_GIT)
        include(FetchContent)
        set(FETCHCONTENT_BASE_DIR_SAVE ${FETCHCONTENT_BASE_DIR})
        if (OS_FETCH_FROM_GIT_PATH)
            get_filename_component(FETCHCONTENT_BASE_DIR "${OS_FETCH_FROM_GIT_PATH}" REALPATH BASE_DIR "${CMAKE_SOURCE_DIR}")
        endif ()

        FetchContent_Declare(
            pico_sdk
            GIT_REPOSITORY https://github.com/raspberrypi/pico-sdk
            GIT_TAG master
            GIT_SUBMODULES_RECURSE FALSE
        )

        if (NOT pico_sdk)
            message("Downloading Raspberry Pi Pico SDK")
            FetchContent_Populate(pico_sdk)
            set(PICO_SDK_PATH ${pico_sdk_SOURCE_DIR})
        endif ()

        set(FETCHCONTENT_BASE_DIR ${FETCHCONTENT_BASE_DIR_SAVE})
    else ()
        message(FATAL_ERROR
            "PICO_SDK_PATH not specified. Set it manually or enable OS_FETCH_FROM_GIT to fetch from Git."
        )
    endif ()
endif ()

# Validate SDK path
get_filename_component(PICO_SDK_PATH "${PICO_SDK_PATH}" REALPATH BASE_DIR "${CMAKE_BINARY_DIR}")
if (NOT EXISTS ${PICO_SDK_PATH})
    message(FATAL_ERROR "Directory '${PICO_SDK_PATH}' not found")
endif ()

set(PICO_SDK_INIT_CMAKE_FILE ${PICO_SDK_PATH}/pico_sdk_init.cmake)
if (NOT EXISTS ${PICO_SDK_INIT_CMAKE_FILE})
    message(FATAL_ERROR "Directory '${PICO_SDK_PATH}' does not appear to contain the Raspberry Pi Pico SDK")
endif ()

set(PICO_SDK_PATH ${PICO_SDK_PATH} CACHE PATH "Path to the Raspberry Pi Pico SDK" FORCE)

# Import Pico SDK
include(${PICO_SDK_INIT_CMAKE_FILE})

# Define OS root
set(OS_ROOT ${CMAKE_CURRENT_LIST_DIR})

# Add OS subsystems
add_subdirectory(${OS_ROOT}/drivers/gpio)
add_subdirectory(${OS_ROOT}/drivers/i2c_driver)
add_subdirectory(${OS_ROOT}/drivers/spi_driver)
add_subdirectory(${OS_ROOT}/drivers/serial_uart)
add_subdirectory(${OS_ROOT}/drivers/sleep)
add_subdirectory(${OS_ROOT}/kernel)
add_subdirectory(${OS_ROOT}/scheduler)
add_subdirectory(${OS_ROOT}/svc_handler)
add_subdirectory(${OS_ROOT}/terminal_core)
add_subdirectory(${OS_ROOT}/terminal)
add_subdirectory(${OS_ROOT}/include)