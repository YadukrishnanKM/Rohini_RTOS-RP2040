#include "spi_driver.h" // Replace with your MCU-specific CMSIS header
#include "hardware/resets.h"


static inline __attribute__((always_inline)) void SPI_begin(uint32_t baud, uint sck, uint mosi, uint miso) {
    // Unreset SPI0
    resets_hw->reset &= ~RESETS_RESET_SPI0_BITS;
    while (!(resets_hw->reset_done & RESETS_RESET_DONE_SPI0_BITS)) {}

    // GPIO function select (no branching)
    io_bank0_hw->io[sck].ctrl  = IO_BANK0_GPIO0_CTRL_FUNCSEL_VALUE_SPI0_SCLK;
    io_bank0_hw->io[mosi].ctrl = IO_BANK0_GPIO0_CTRL_FUNCSEL_VALUE_SPI0_TX;
    io_bank0_hw->io[miso].ctrl = IO_BANK0_GPIO0_CTRL_FUNCSEL_VALUE_SPI0_RX;

    // Enable output for SCK and MOSI
    sio_hw->gpio_oe_set = (1u << sck) | (1u << mosi);

    // SPI format: 8-bit, CPOL=0, CPHA=0, FRF=0 (SPI), DSS=7 (8-bit)
    spi0_hw->cr0 = (7 << SPI_SSPCR0_DSS_LSB);
    spi0_hw->cpsr = 2;  // Prescaler (must be even)
    spi0_hw->cr1 = SPI_SSPCR1_SSE_BITS;
}

static inline __attribute__((always_inline)) uint8_t SPI_transfer(uint8_t data) {
    while (!(spi0_hw->sr & SPI_SSPSR_TNF_BITS)) {}
    spi0_hw->dr = data;
    while (!(spi0_hw->sr & SPI_SSPSR_RNE_BITS)) {}
    return spi0_hw->dr;
}

static inline __attribute__((always_inline)) void SPI_transferBytes(const uint8_t *tx, uint8_t *rx, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        rx[i] = SPI_transfer(tx[i]);
    }
}

static inline __attribute__((always_inline)) void SPI_beginTransaction(uint32_t baud, uint cpol, uint cpha) {
    spi0_hw->cr1 = 0; // Disable SPI
    spi0_hw->cr0 = (7 << SPI_SSPCR0_DSS_LSB) |
                   ((cpol & 1) << SPI_SSPCR0_SPO_LSB) |
                   ((cpha & 1) << SPI_SSPCR0_SPH_LSB);
    spi0_hw->cpsr = 2;
    spi0_hw->cr1 = SPI_SSPCR1_SSE_BITS;
}

static inline __attribute__((always_inline)) void SPI_endTransaction(void) {
    // No-op
}

static inline __attribute__((always_inline)) void SPI_transferDMA(const uint8_t *tx, uint8_t *rx, size_t len) {
    // Blocking fallback
    SPI_transferBytes(tx, rx, len);
}