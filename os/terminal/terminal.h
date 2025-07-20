#pragma once

#include "pico/stdlib.h"

// Initializes USB serial interface
void terminal_init(void);

// Reads a character from USB serial (blocking)
char terminal_read_char(void);

// Writes a character to USB serial
void terminal_write_char(char c);

// Writes a string to USB serial
void terminal_write_string(const char *str);

// Reads a line (blocking until newline)
void terminal_read_line(char *buffer, uint32_t max_len);
