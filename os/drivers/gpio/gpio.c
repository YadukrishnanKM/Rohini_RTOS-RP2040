#include "gpio.h"


static inline void pinMode(uint gpio, int mode) {
    gpio_init(gpio);
    gpio_set_dir(gpio, _IS_OUTPUT(mode));       // 0 = IN, 1 = OUT
    gpio_pull_up(gpio * _IS_PULLUP(mode));      // Pull-up only if mode == INPUT_PULLUP
}

static inline void digitalWrite(uint gpio, bool value) {
    gpio_put(gpio, value);
}

static inline bool digitalRead(uint gpio) {
    return gpio_get(gpio);
}