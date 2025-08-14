#include "spi_driver.h"


static inline __attribute__((always_inline)) void SPI_begin(uint baud, uint sck, uint mosi, uint miso) {
    spi_init(spi0, baud);

    gpio_init(sck);
    gpio_init(mosi);
    gpio_init(miso);

    gpio_set_function(sck, GPIO_FUNC_SPI);
    gpio_set_function(mosi, GPIO_FUNC_SPI);
    gpio_set_function(miso, GPIO_FUNC_SPI);
}

static inline __attribute__((always_inline)) uint8_t SPI_transfer(uint8_t data) {
    uint8_t recv;
    spi_write_read_blocking(spi0, &data, &recv, 1);
    return recv;
}

static inline __attribute__((always_inline)) void SPI_transferBytes(const uint8_t *tx, uint8_t *rx, size_t len) {
    spi_write_read_blocking(spi0, tx, rx, len);
}

static inline __attribute__((always_inline)) void SPI_beginTransaction(uint baud, uint cpol, uint cpha) {
    spi_deinit(spi0);
    spi_set_format(spi0, 8, (spi_cpol_t)cpol, (spi_cpha_t)cpha, SPI_MSB_FIRST);
    spi_init(spi0, baud);
}

static inline __attribute__((always_inline)) void SPI_endTransaction(void) {
    // No-op for symmetry
}

static inline __attribute__((always_inline)) void SPI_transferDMA(const uint8_t *tx, uint8_t *rx, size_t len) {
    // Minimal DMA example (blocking)
    spi_write_read_blocking(spi0, tx, rx, len);
    // For true DMA, you'd use spi_write_read_blocking_async() with IRQs
}
