# Terminal Core Library for RP2040

A **dual-core terminal interface** for RP2040, designed for use with the Rohini RTOS project.  
This library runs the **terminal loop on Core 1** so Core 0 can handle real-time tasks while still accepting commands via USB/UART.

---

## ✨ Features
- Runs terminal input loop on **Core 1**
- Provides a **shared global state** (`terminal_state`)
- Non-blocking command + payload parsing
- Core 0 can **poll or react** to new commands without blocking its main loop
- Lightweight, no dynamic allocation

---

## ⚡ API Reference

### Data Structure
```c
typedef struct {
    char last_command[TERMINAL_CMD_MAX_LEN];   // Command string
    char last_payload[TERMINAL_PAYLOAD_MAX_LEN]; // Payload after command
    volatile bool command_ready;               // Flag when command available
} terminal_core_state_t;
````

* **Command** = first token typed (e.g., `"led_on"`)
* **Payload** = rest of line after command (e.g., `"25 1"`)
* **command\_ready** = set true by Core 1, cleared by Core 0 after handling

### Globals

```c
extern terminal_core_state_t terminal_state;
```

### Functions

```c
void terminal_core_launch(void);
    // Starts terminal loop on Core 1
    // Updates `terminal_state` when commands are entered
```

---

## 🖥️ Examples

### 1. Launch Terminal on Core 1

```c
#include "terminal_core.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include <stdio.h>
#include <string.h>

int main() {
    stdio_init_all();

    // Start terminal loop on Core 1
    multicore_launch_core1(terminal_core_launch);

    while (1) {
        if (terminal_state.command_ready) {
            printf("Command: %s\n", terminal_state.last_command);
            printf("Payload: %s\n", terminal_state.last_payload);

            // Clear flag after handling
            terminal_state.command_ready = false;
        }
    }
}
```

---

### 2. Simple LED Control via Terminal (Dual Core)

```c
#include "terminal_core.h"
#include "gpio.h"
#include "pico/multicore.h"
#include <stdio.h>
#include <string.h>

int main() {
    stdio_init_all();
    pinMode(25, OUTPUT);

    // Launch terminal loop on Core 1
    multicore_launch_core1(terminal_core_launch);

    while (1) {
        if (terminal_state.command_ready) {
            if (strcmp(terminal_state.last_command, "on") == 0) {
                digitalWrite(25, true);
                printf("LED ON\n");
            } else if (strcmp(terminal_state.last_command, "off") == 0) {
                digitalWrite(25, false);
                printf("LED OFF\n");
            } else {
                printf("Unknown command: %s\n", terminal_state.last_command);
            }

            // Clear flag for next input
            terminal_state.command_ready = false;
        }
    }
}
```

---

## 📜 Notes

* Designed for **Core 1 input handling** while Core 0 handles main tasks
* Input terminates on **Enter** (`\r` or `\n`)
* Command parsing is **whitespace-based** (first word = command, rest = payload)
* Works with both **USB CDC (`stdio_usb`)** and UART (depending on Pico SDK setup)

---

## 📜 License

Released under **GPL-3.0** as part of the [Rohini RTOS](https://github.com/YadukrishnanKM/Rohini_RTOS-RP2040).

