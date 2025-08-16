# Terminal Library for RP2040

A **lightweight line-based terminal interface** for RP2040, part of the Rohini RTOS project.  
It provides a minimal shell over USB/UART, with **command + payload parsing** and **non-blocking updates**.

---

## ✨ Features
- Simple, single-header terminal interface
- Non-blocking input handling (uses `getchar_timeout_us(0)`)
- Echoes typed characters back to the terminal
- Splits input into:
  - **Command** (first word)
  - **Payload** (rest of the line)
- Provides functions to check for new commands and retrieve them

---

## ⚡ API Reference

### Data Structure
```c
typedef struct {
    char buffer[TERMINAL_MAX_LEN];   // Raw input buffer
    char command[TERMINAL_MAX_LEN];  // Parsed command
    char payload[TERMINAL_MAX_LEN];  // Parsed payload
    int index;                       // Current buffer index
    bool command_ready;              // Flag for new command
} Terminal;
````

### Functions

```c
void terminal_init(Terminal* t);
    // Initialize terminal state, print prompt

void terminal_update(Terminal* t);
    // Poll for input (non-blocking), parse command + payload when Enter pressed

bool terminal_has_command(Terminal* t);
    // Returns true if a complete command is ready

char* terminal_get_command(Terminal* t);
    // Get last command, clears command_ready flag

char* terminal_get_payload(Terminal* t);
    // Get last payload (string after command)
```

---

## 🖥️ Examples

### 1. Minimal Command Echo

```c
#include "terminal.h"
#include <stdio.h>

int main() {
    stdio_init_all();
    Terminal term;
    terminal_init(&term);

    while (1) {
        terminal_update(&term);

        if (terminal_has_command(&term)) {
            printf("You typed command: %s\n", terminal_get_command(&term));
            printf("With payload: %s\n", terminal_get_payload(&term));
        }
    }
}
```

---

### 2. Simple LED Control via Terminal

```c
#include "terminal.h"
#include "gpio.h"
#include "pico/stdlib"

int main() {
    stdio_init_all();
    Terminal term;
    terminal_init(&term);

    pinMode(25, OUTPUT);

    while (1) {
        terminal_update(&term);

        if (terminal_has_command(&term)) {
            char* cmd = terminal_get_command(&term);
            char* arg = terminal_get_payload(&term);

            if (strcmp(cmd, "on") == 0) {
                digitalWrite(25, true);
                printf("LED ON\n");
            } else if (strcmp(cmd, "off") == 0) {
                digitalWrite(25, false);
                printf("LED OFF\n");
            } else {
                printf("Unknown command: %s\n", cmd);
            }
        }
    }
}
```

---

## 📜 Notes

* Works with **USB CDC** (`stdio_usb`) or UART depending on Pico SDK configuration
* Input terminates on **Enter** (`\r` or `\n`)
* Parsing is **whitespace-separated** (first token = command, rest = payload)
* Echo prints typed characters to the terminal automatically

---

## 📜 License

Released under **GPL-3.0** as part of the [Rohini RTOS](https://github.com/YadukrishnanKM/Rohini_RTOS-RP2040).

