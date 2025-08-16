#include "serial_uart.h"

static inline __attribute__((always_inline)) void Serial_begin(uint baud) {
    uart_init(uart0, baud);
    gpio_set_function(0, GPIO_FUNC_UART);  // TX
    gpio_set_function(1, GPIO_FUNC_UART);  // RX
}

static inline __attribute__((always_inline)) void Serial_write(uint8_t byte) {
    uart_putc_raw(uart0, byte);
}

static inline __attribute__((always_inline)) uint8_t Serial_read(void) {
    return uart_getc(uart0);  // Unsafe if no data; use Serial_available first
}

static inline __attribute__((always_inline)) uint Serial_available(void) {
    return uart_is_readable(uart0);  // Returns 0 or 1
}