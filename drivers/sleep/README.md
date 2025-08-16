# Timing Library for RP2040 (Branchless Delays)

This is a **minimal timing library** for the RP2040 (Raspberry Pi Pico), written for the Rohini RTOS project.  
It provides **branchless delay and timing functions** using direct access to RP2040 hardware timers (`timerawl`).  

---

## ✨ Features
- **Accurate microsecond & millisecond delays** using `timer_hw->timerawl`  
- **Arduino-style API**: `delay()`, `delayMicroseconds()`, `millis()`, `micros()`  
- **Cycle and tick based delays** (`sleep_cycles`, `sleep_ticks`)  
- **Branchless implementation** (uses inline busy-waiting loops only)  
- **Custom system clock frequency** support via `RP2040_SYSCLK_HZ`  

---

## ⚡ API Reference

### Configuration
```c
#define RP2040_SYSCLK_HZ 125000000u
// Default 125 MHz system clock
// Define this macro before including to use a custom clock frequency
````

### Functions

```c
void sleep_us(uint32_t us);
    // Sleep for given microseconds

void sleep_ms(uint32_t ms);
    // Sleep for given milliseconds

void delay(uint32_t ms);
    // Alias for sleep_ms() (Arduino style)

void delayMicroseconds(uint32_t us);
    // Alias for sleep_us() (Arduino style)

void sleep_cycles(uint32_t cycles);
    // Sleep for a number of CPU cycles

void sleep_ticks(uint32_t ticks);
    // Sleep for a number of SysTick ticks

uint64_t micros(void);
    // Time since boot in microseconds

uint32_t millis(void);
    // Time since boot in milliseconds
```

---

## 🖥️ Examples

### 1. Simple LED Blink (millis delay)

```c
#include "time.h"
#include "gpio.h"

int main() {
    pinMode(25, OUTPUT);

    while (1) {
        digitalWrite(25, true);   // LED ON
        delay(500);               // 500 ms
        digitalWrite(25, false);  // LED OFF
        delay(500);
    }
}
```

### 2. Microsecond Precision Delay

```c
#include "time.h"
#include "gpio.h"

int main() {
    pinMode(25, OUTPUT);

    while (1) {
        digitalWrite(25, true);
        delayMicroseconds(100);  // 100 µs pulse
        digitalWrite(25, false);
        delayMicroseconds(100);
    }
}
```

### 3. Timing Measurement

```c
#include "time.h"
#include "pico/stdlib.h"

int main() {
    uint64_t start = micros();
    delay(1000);   // 1 second
    uint64_t end = micros();

    printf("Elapsed time: %llu µs\n", end - start);
}
```

---

## 📜 Notes

* All functions use **busy-waiting** (blocking) — suitable for simple tasks and bare-metal loops.
* For **non-blocking multitasking**, use with Rohini RTOS scheduler instead.
* Timing resolution is based on `timer_hw->timerawl` which runs at the system clock frequency.

---

## 📜 License

Released under **GPL-3.0** as part of the [Rohini RTOS](https://github.com/YadukrishnanKM/Rohini_RTOS-RP2040).

