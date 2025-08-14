#include "i2c_driver.h"



static inline __attribute__((always_inline)) void Wire_begin(uint freq, uint sda, uint scl) {
    i2c_init(i2c0, freq);

    gpio_init(sda);
    gpio_init(scl);

    gpio_set_function(sda, GPIO_FUNC_I2C);
    gpio_set_function(scl, GPIO_FUNC_I2C);

    gpio_pull_up(sda);
    gpio_pull_up(scl);
}

static inline __attribute__((always_inline)) void Wire_write(uint8_t addr, const uint8_t *data, size_t len) {
    i2c_write_blocking(i2c0, addr, data, len, false);
}

static inline __attribute__((always_inline)) void Wire_read(uint8_t addr, uint8_t *buffer, size_t len) {
    i2c_read_blocking(i2c0, addr, buffer, len, false);
}