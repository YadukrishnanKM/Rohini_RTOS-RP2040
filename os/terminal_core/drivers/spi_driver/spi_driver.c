#include "hardware/spi.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"

static inline void SPI_begin(uint32_t baud, uint sck, uint mosi, uint miso) {
    // --- Step 1: Configure GPIO functions ---
    gpio_set_function(sck,  GPIO_FUNC_SPI);
    gpio_set_function(mosi, GPIO_FUNC_SPI);
    gpio_set_function(miso, GPIO_FUNC_SPI);

    // --- Step 2: Initialize SPI0 ---
    spi_init(spi0, baud);

    // --- Step 3: Set default format (8 bits, CPOL=0, CPHA=0, MSB first) ---
    spi_set_format(spi0,
                   8,      // bits per transfer
                   SPI_CPOL_0,
                   SPI_CPHA_0,
                   SPI_MSB_FIRST);
}

static inline uint8_t SPI_transfer(uint8_t data) {
    uint8_t rx;
    spi_write_read_blocking(spi0, &data, &rx, 1);
    return rx;
}

static inline void SPI_transferBytes(const uint8_t *tx, uint8_t *rx, size_t len) {
    spi_write_read_blocking(spi0, tx, rx, len);
}

static inline void SPI_beginTransaction(uint32_t baud, uint cpol, uint cpha) {
    spi_set_baudrate(spi0, baud);
    spi_set_format(spi0,
                   8,
                   cpol ? SPI_CPOL_1 : SPI_CPOL_0,
                   cpha ? SPI_CPHA_1 : SPI_CPHA_0,
                   SPI_MSB_FIRST);
}

static inline void SPI_endTransaction(void) {
    // No-op: SDK handles state internally
}

static inline void SPI_transferDMA(const uint8_t *tx, uint8_t *rx, size_t len) {
    // Blocking fallback
    spi_write_read_blocking(spi0, tx, rx, len);
}