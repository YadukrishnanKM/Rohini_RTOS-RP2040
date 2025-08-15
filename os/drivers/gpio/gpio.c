#include "gpio.h"


// Configure GPIO pin mode (CMSIS-only, branchless)
static inline __attribute__((always_inline)) void pinMode(uint gpio, int mode) {
    if (gpio >= NUM_BANK0_GPIOS) return;  // Optional safety check

    // Set GPIO function to SIO (FUNCSEL = 5)
    io_bank0_hw->io[gpio].ctrl =
        (io_bank0_hw->io[gpio].ctrl & ~IO_BANK0_GPIO0_CTRL_FUNCSEL_BITS) |
        (5 << IO_BANK0_GPIO0_CTRL_FUNCSEL_LSB);

    // Set direction: output or input
    sio_hw->gpio_oe_set = -(uint32_t)_IS_OUTPUT(mode) & (1u << gpio);
    sio_hw->gpio_oe_clr = -(uint32_t)(1 - _IS_OUTPUT(mode)) & (1u << gpio);

    // Modify pad register directly
    uint32_t pad = pads_bank0_hw->io[gpio];

    // Clear pull-up and pull-down bits
    pad &= ~((1u << 2) | (1u << 3));

    // Set pull-up/pull-down if needed
    pad |= ((uint32_t)_IS_PULLUP(mode) << 2);
    pad |= ((uint32_t)_IS_PULLDOWN(mode) << 3);

    // Enable input if not output
    pad |= ((uint32_t)(1 - _IS_OUTPUT(mode)) << 7);  // Bit 7 = IE

    pads_bank0_hw->io[gpio] = pad;
}

// ─────────────────────────────────────────────────────────────
// Write digital value to GPIO (CMSIS-only, branchless)
static inline __attribute__((always_inline)) void digitalWrite(uint gpio, bool value) {
    sio_hw->gpio_set = -(uint32_t)value & (1u << gpio);
    sio_hw->gpio_clr = -(uint32_t)(!value) & (1u << gpio);
}

// ─────────────────────────────────────────────────────────────
// Read digital value from GPIO (CMSIS-only)
static inline __attribute__((always_inline)) bool digitalRead(uint gpio) {
    return !!(sio_hw->gpio_in & (1u << gpio));
}
