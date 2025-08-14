#pragma once

#include "hardware/i2c.h"
#include "gpio.h"  // Reuse our optimized GPIO setup

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Initializes I2C0 with custom SDA/SCL pins.
 * @param freq Frequency in Hz.
 * @param sda GPIO pin for SDA.
 * @param scl GPIO pin for SCL.
 */
static inline void Wire_begin(uint freq, uint sda, uint scl);

/**
 * @brief Writes data to a device over I2C.
 */
static inline void Wire_write(uint8_t addr, const uint8_t *data, size_t len);

/**
 * @brief Reads data from a device over I2C.
 */
static inline void Wire_read(uint8_t addr, uint8_t *buffer, size_t len);

#ifdef __cplusplus
}
#endif

