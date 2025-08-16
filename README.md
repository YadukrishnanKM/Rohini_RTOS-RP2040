# Rohini RTOS – (Preview beta) Version 0.1.8

## Overview

<p align="center">
  <img src="icon.png" alt="Logo" width="450"/>
</p>

The **Rohini RTOS Kernel** is the core execution engine of the Rohini Real-Time Operating System for the Raspberry Pi RP2040 microcontroller.  
It provides a **preemptive, multitasking environment** with process management, dual-core scheduling, and an optional object-oriented task model for C++ developers.

This kernel is designed to be:
- **Lightweight** – minimal footprint suitable for microcontrollers
- **Deterministic** – preemptive scheduling with predictable context switching
- **Dual-core aware** – runs tasks on both RP2040 cores
- **C and C++ friendly** – low-level C API + high-level C++ wrappers

---

## Features

### Process & Task Management
- Create, run, fork, and terminate processes
- Replace process execution image (`exec`)
- Wait for child process termination (`wait`)
- Cooperative yielding (`yield`)

### Scheduler
- Preemptive multitasking driven by `SysTick` interrupts
- Configurable to run on **Core 1** while **Core 0** handles I/O or setup

### C++ Integration
- `Kernel` class for hardware init and scheduler control
- `Process` base class for object-oriented task creation

---

## Architecture

```text
+------------------------------+
| Core 0                       |
| - Kernel::init()             |
| - Process registration       |
| - Launch Core 1 scheduler    |
+------------------------------+
                │
                ▼
+------------------------------+
| Core 1                       |
| - SysTick-driven scheduler   |
| - Runs ready processes       |
+------------------------------+
````

---

## Directory Structure

```
kernel.h         # C++ wrapper API for the kernel
scheduler.h      # Low-level C scheduler API
terminal_core.h  # Terminal/command handling core
os/              # OS core components (kernel, scheduler, services)
lib/             # Supporting libraries (drivers, utils)
src/main.cpp     # Example user application
CMakeLists.txt   # Project build configuration
```

---

## Building Rohini RTOS Kernel

This project uses **CMake** and the **Raspberry Pi Pico SDK**.

### 1. Clone Dependencies

```bash
git clone https://github.com/raspberrypi/pico-sdk.git
git clone https://github.com/raspberrypi/pico-extras.git
git clone https://github.com/raspberrypi/picotool.git
```

Ensure they are in the same directory as your project.

### 2. Example CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.13)

# SDK and extras paths
set(PICO_SDK_PATH "${CMAKE_CURRENT_SOURCE_DIR}/pico-sdk")
set(PICO_EXTRAS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/pico-extras")
set(PICOTOOL_FETCH_FROM_GIT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/picotool")

# Path validation
if (NOT EXISTS ${PICO_SDK_PATH})
    message(FATAL_ERROR "PICO_SDK_PATH does not exist: ${PICO_SDK_PATH}")
endif()
if (NOT DEFINED PICO_SDK_PATH)
    message(FATAL_ERROR "PICO_SDK_PATH is not defined.")
endif()
if (NOT IS_DIRECTORY ${PICO_SDK_PATH})
    message(FATAL_ERROR "PICO_SDK_PATH is not a directory: ${PICO_SDK_PATH}")
endif()
message("\n\n PICO_SDK_PATH: ${PICO_SDK_PATH} \n\n")

# Import Pico SDK & extras
include("${PICO_SDK_PATH}/external/pico_sdk_import.cmake")
include("${PICO_EXTRAS_PATH}/external/pico_extras_import.cmake")

project("ros" LANGUAGES C CXX ASM)

# Initialize SDK
pico_sdk_init()

# Main application
add_executable(${PROJECT_NAME}
    src/main.cpp
)

include_directories(${PROJECT_NAME}
    ${PICO_SDK_PATH}/src/rp2_common/cmsis/include
)

# Add OS and library directories
add_subdirectory(os)
add_subdirectory(lib)

target_link_libraries(${PROJECT_NAME} PUBLIC pico_stdlib kernel svc_handler)

# USB/UART output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

# Output files
pico_add_extra_outputs(${PROJECT_NAME})
```

### 3. Build Commands

```bash
mkdir build
cd build
cmake ..
make
```

The `.uf2` firmware file will be created in `build/` — drag it onto the RP2040’s USB storage to flash.

---

## Getting Started

### Minimal Example (C API)

```cpp
#include "kernel.h"
using namespace rohini;

void my_task() {
    while (true) {
        printf("Hello from task!\n");
        Kernel::yield();
    }
}

int main() {
    Kernel::init();
    Kernel::create_init(my_task);
    Kernel::launch_core1();
}
```

### Minimal Example (C++ Process API)

```cpp
#include "kernel.h"
using namespace rohini;

class MyProcess : public Process {
public:
    void run() override {
        while (true) {
            printf("Hello from MyProcess!\n");
            Kernel::yield();
        }
    }
};

int main() {
    Kernel::init();
    MyProcess proc;
    proc.spawn();
    Kernel::launch_core1();
}
```

---

## API Reference

### `class Kernel`

| Method                                         | Description                                   |
| ---------------------------------------------- | --------------------------------------------- |
| `static void init()`                           | Initialize clocks, USB serial, and scheduler. |
| `static void create_init(void (*entry)(void))` | Create the first process.                     |
| `static void launch_core1()`                   | Start scheduler on Core 1.                    |
| `static void yield()`                          | Yield CPU to another ready process.           |
| `static int fork()`                            | Fork current process (returns child PID).     |
| `static int exec(void (*entry)(void))`         | Replace current process code.                 |
| `static void exit(int code)`                   | Terminate process with code.                  |
| `static int wait(int pid)`                     | Wait for a child process to exit.             |

### `class Process`

Base class for object-oriented tasks.

| Method               | Description                          |
| -------------------- | ------------------------------------ |
| `virtual void run()` | Override to implement process logic. |
| `void spawn()`       | Register process with the scheduler. |

---

## Multicore Model

* **Core 0**: System initialization, process creation
* **Core 1**: Preemptive scheduler, task execution

---

## License

MIT License – see `LICENSE` file.

```

---
