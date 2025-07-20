#include "terminal.h"

void terminal_init(void) {
    stdio_init_all();  // Initializes stdio USB (or UART if configured)
    sleep_ms(2000);    // Allow time for USB connection to stabilize
}

char terminal_read_char(void) {
    while (!stdio_usb_connected()) {
        tight_loop_contents();  // Wait until USB is ready
    }

    int c = getchar();
    return (c == PICO_ERROR_TIMEOUT) ? '\0' : (char)c;
}

void terminal_write_char(char c) {
    putchar(c);
}

void terminal_write_string(const char *str) {
    while (*str) {
        terminal_write_char(*str++);
    }
}

void terminal_read_line(char *buffer, uint32_t max_len) {
    uint32_t i = 0;
    while (i < max_len - 1) {
        char c = terminal_read_char();
        if (c == '\n' || c == '\r') break;
        buffer[i++] = c;
    }
    buffer[i] = '\0';
}