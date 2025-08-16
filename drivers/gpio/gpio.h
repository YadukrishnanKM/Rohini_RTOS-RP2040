#pragma once
#include "hardware/regs/io_bank0.h"
#include "hardware/structs/io_bank0.h"
#include "hardware/structs/pads_bank0.h"
#include "hardware/structs/sio.h"

#ifdef __cplusplus
extern "C" {
#endif

// ─────────────────────────────────────────────────────────────
// GPIO mode flags (bitmask-style)
#define INPUT           0x00  // Input, no pull
#define OUTPUT          0x01  // Output
#define INPUT_PULLUP    0x02  // Input with pull-up
#define INPUT_PULLDOWN  0x04  // Input with pull-down

// ─────────────────────────────────────────────────────────────
// Branchless mode helpers
#define _IS_OUTPUT(mode)      ((mode) & OUTPUT)
#define _IS_PULLUP(mode)      (((mode) & INPUT_PULLUP) >> 1)
#define _IS_PULLDOWN(mode)    (((mode) & INPUT_PULLDOWN) >> 2)

// ─────────────────────────────────────────────────────────────

/**
 * @brief Sets the mode of a GPIO pin (no branching).
 * @param gpio GPIO pin number.
 * @param mode INPUT, OUTPUT, or INPUT_PULLUP.
 */
static inline __attribute__((always_inline)) void pinMode(uint gpio, int mode);

/**
 * @brief Writes a digital value to a GPIO pin.
 * @param gpio GPIO pin number.
 * @param value true for HIGH, false for LOW.
 */
static inline __attribute__((always_inline)) void digitalWrite(uint gpio, bool value);

/**
 * @brief Reads the digital value from a GPIO pin.
 * @param gpio GPIO pin number.
 * @return true if HIGH, false if LOW.
 */
static inline __attribute__((always_inline)) bool digitalRead(uint gpio);

#ifdef __cplusplus
}
#endif
