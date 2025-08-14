#pragma once

#include "pico/stdlib.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes UART with given baud rate.
 * @param baud Baud rate (e.g., 115200).
 */
static inline void Serial_begin(uint baud);

/**
 * @brief Writes a byte to UART0.
 * @param byte Byte to send.
 */
static inline void Serial_write(uint8_t byte);

/**
 * @brief Reads a byte from UART0.
 * @return Received byte (undefined if no data).
 */
static inline uint8_t Serial_read(void);

/**
 * @brief Returns non-zero if data is available.
 */
static inline uint Serial_available(void);

#ifdef __cplusplus
}
#endif
