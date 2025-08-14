#pragma once

#include "pico/stdlib.h"

#define INPUT         0
#define OUTPUT        1
#define INPUT_PULLUP  2

#ifdef __cplusplus
extern "C" {
#endif

// Mode constants as bit flags
#define _IS_OUTPUT(mode)     ((mode) & 0x01)
#define _IS_PULLUP(mode)     (((mode) >> 1) & 0x01)

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
