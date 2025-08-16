# Rohini RTOS for RP2040 — v0.2.3

<p align="center">
  <img src="icon.png" alt="Logo" width="450"/>
</p>

Rohini RTOS is a lightweight, preemptive real-time operating system designed for the Raspberry Pi RP2040 microcontroller.  
It provides dual-core scheduling, process/task management, CMSIS compatibility, and a set of peripheral drivers.  


---

## 📂 Repository Structure

```

.
├── CMakeLists.txt          # RTOS build configuration
├── LICENCE                 # GPL-3.0 license
├── kernel/                 # Core kernel (C++ API)
├── scheduler/              # Preemptive scheduler (C API)
├── svc\_handler/            # Supervisor call handler (SVC, context switching)
├── drivers/                # Peripheral drivers
├── terminal/               # Minimal terminal interface
├── terminal\_core/          # Complete terminal-enabled RTOS build
├── ros\_cmsis\_compat/       # CMSIS compatibility layer
├── external/               # RTOS import scripts
└── icon.png                # Project logo

````

---

## 🚀 Features

- Preemptive multitasking on dual cores  
- SysTick-based task switching  
- `fork`, `exec`, `exit`, `wait`, `yield` process control  
- CMSIS compatibility shim  
- Modular drivers: GPIO, SPI, I²C, UART, Sleep, LCD (HD44780 over I²C)  
- Supervisor Call (SVC) context switching in assembly  
- Optional `terminal_core` variant with CLI  

---

## 🔧 Getting Started

### 1. Clone with SDKs

```bash
git clone https://github.com/YadukrishnanKM/Rohini_RTOS-RP2040.git
git clone https://github.com/raspberrypi/pico-sdk.git
git clone https://github.com/raspberrypi/pico-extras.git
````

Make sure `pico-sdk`, `pico-extras`, and `Rohini_RTOS-RP2040` are in the same parent directory.

---

### 2. Example `CMakeLists.txt`

Here’s a **simplified project CMake** that uses Rohini RTOS:

```cmake
cmake_minimum_required(VERSION 3.13)

# Paths (adjust if needed)
set(PICO_SDK_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../pico-sdk")
set(PICO_EXTRAS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../pico-extras")
set(ROHINI_RTOS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../Rohini_RTOS-RP2040")

# Import Pico SDK & Extras
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)
include(${PICO_EXTRAS_PATH}/external/pico_extras_import.cmake)

# Import Rohini RTOS
include(${ROHINI_RTOS_PATH}/external/rohini_rtos_import.cmake)

project(my_app C CXX ASM)
pico_sdk_init()

# App sources
add_executable(${PROJECT_NAME}
    src/main.cpp
)

# Link RTOS + SDK
target_link_libraries(${PROJECT_NAME} PUBLIC
    pico_stdlib
    kernel
    scheduler
    svc_handler
)

# Enable USB stdio
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

# Generate .uf2 firmware
pico_add_extra_outputs(${PROJECT_NAME})
```

This lets you include Rohini RTOS as part of **any RP2040 project**.

---

## 📖 Example Usage

### Minimal Kernel App

```cpp
#include "kernel/kernel.h"
using namespace rohini;

void task() {
    while (true) {
        printf("Hello from task!\n");
        Kernel::yield();
    }
}

int main() {
    Kernel::init();
    Kernel::create_init(task);
    Kernel::launch_core1();   // run scheduler on Core1
}
```

### Using a Driver (GPIO)

```c
#include "gpio.h"

int main() {
    // Configure onboard LED (GPIO 25) as output
    pinMode(25, OUTPUT);

    while (true) {
        digitalWrite(25, true);   // LED ON
        delay(500);
        digitalWrite(25, false);  // LED OFF
        delay(500);
    }
}
```

---

## 📜 License

This project is licensed under the **GNU GPL-3.0** License.
See [LICENCE](LICENCE) for details.

---

## 🙌 Contributing

Contributions are welcome!
Please open issues or submit PRs to improve drivers, kernel functionality, or add new features.

---
