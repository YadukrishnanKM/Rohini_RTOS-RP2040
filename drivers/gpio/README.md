
# GPIO Library for RP2040

This is a **minimal GPIO library** for the RP2040 (Raspberry Pi Pico), written for the Rohini RTOS project.  
It provides **branchless bitmask-style** GPIO control with inline functions for fast digital I/O.  

---

## ✨ Features
- **Simple API**: `pinMode()`, `digitalWrite()`, `digitalRead()`  
- **Branchless implementation** using direct hardware registers  
- **Supports**:
  - Input  
  - Input with pull-up  
  - Input with pull-down  
  - Output  

---

## ⚡ API Reference

### Pin Modes
```c
#define INPUT           0x00  // Input, no pull
#define OUTPUT          0x01  // Output
#define INPUT_PULLUP    0x02  // Input with pull-up
#define INPUT_PULLDOWN  0x04  // Input with pull-down
````

### Functions

```c
void pinMode(uint gpio, int mode);
    // Configure pin as INPUT, OUTPUT, INPUT_PULLUP, or INPUT_PULLDOWN

void digitalWrite(uint gpio, bool value);
    // Set pin HIGH (true) or LOW (false)

bool digitalRead(uint gpio);
    // Read pin state (true = HIGH, false = LOW)
```

---

## 🖥️ Examples

### 1. Blink Onboard LED

```c
#include "gpio.h"
#include "pico/stdlib.h"

int main() {
    pinMode(25, OUTPUT);   // Onboard LED pin

    while (1) {
        digitalWrite(25, true);   // LED ON
        sleep_ms(500);
        digitalWrite(25, false);  // LED OFF
        sleep_ms(500);
    }
}
```

### 2. Button Input with Pull-Up

```c
#include "gpio.h"
#include "pico/stdlib.h"

int main() {
    pinMode(2, INPUT_PULLUP);  // Button on GPIO2
    pinMode(25, OUTPUT);       // LED on GPIO25

    while (1) {
        bool pressed = !digitalRead(2);  // Active LOW
        digitalWrite(25, pressed);
    }
}
```

---

## 📜 Notes

* The library bypasses Pico SDK’s `gpio_init()` and works **directly with RP2040 hardware registers** for speed.
* Pull-ups and pull-downs are configured in `pads_bank0`.
* This library is designed to be **inlined and branchless**, making it suitable for RTOS and high-performance tasks.

---

## 📜 License

Released under **GPL-3.0** as part of the [Rohini RTOS](https://github.com/YadukrishnanKM/Rohini_RTOS-RP2040).

```
