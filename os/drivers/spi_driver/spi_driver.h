#pragma once

#include "hardware/spi.h"
#include "gpio.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Initializes SPI0 with custom pins.
 * @param baud Baud rate in Hz.
 * @param sck GPIO pin for SCK.
 * @param mosi GPIO pin for MOSI.
 * @param miso GPIO pin for MISO.
 */
static inline void SPI_begin(uint baud, uint sck, uint mosi, uint miso);

/**
 * @brief Transfers a byte over SPI and returns the received byte.
 * @param data Byte to send.
 * @return Byte received.
 */
static inline uint8_t SPI_transfer(uint8_t data);

/**
 * @brief Transfer multiple bytes over SPI.
 *
 * Sends and receives `len` bytes using blocking transfer.
 *
 * @param tx Pointer to transmit buffer.
 * @param rx Pointer to receive buffer.
 * @param len Number of bytes to transfer.
 */
static inline void SPI_transferBytes(const uint8_t *tx, uint8_t *rx, size_t len);

/**
 * @brief Begin an SPI transaction with custom format.
 *
 * Configures SPI mode and reinitializes SPI0.
 *
 * @param baud Baud rate in Hz.
 * @param cpol Clock polarity (0 or 1).
 * @param cpha Clock phase (0 or 1).
 */
static inline void SPI_beginTransaction(uint baud, uint cpol, uint cpha);

/**
 * @brief End an SPI transaction.
 *
 * Currently a no-op, included for API symmetry.
 */
static inline void SPI_endTransaction(void);

/**
 * @brief Transfer multiple bytes using DMA (blocking).
 *
 * Placeholder for future non-blocking DMA support.
 *
 * @param tx Pointer to transmit buffer.
 * @param rx Pointer to receive buffer.
 * @param len Number of bytes to transfer.
 */
static inline void SPI_transferDMA(const uint8_t *tx, uint8_t *rx, size_t len);


#ifdef __cplusplus
}
#endif