#include "terminal.h"
#include <stdio.h>
#include <string.h>

void terminal_init(Terminal* t) {
    t->index = 0;
    t->command_ready = false;
    t->buffer[0] = '\0';
    t->command[0] = '\0';
    t->payload[0] = '\0';
    printf("-> ");
}

void terminal_update(Terminal* t) {
    int c;
    while ((c = getchar_timeout_us(0)) != PICO_ERROR_TIMEOUT) {
        if (c == '\r' || c == '\n') {
            if (t->index > 0) {
                t->buffer[t->index] = '\0';

                // Parse command and payload
                char* space = strchr(t->buffer, ' ');
                if (space) {
                    int cmd_len = space - t->buffer;
                    strncpy(t->command, t->buffer, cmd_len);
                    t->command[cmd_len] = '\0';
                    strncpy(t->payload, space + 1, sizeof(t->payload) - 1);
                } else {
                    strncpy(t->command, t->buffer, sizeof(t->command) - 1);
                    t->payload[0] = '\0';
                }

                t->command_ready = true;
                printf("\nCommand: %s\n", t->command);
                printf("Payload: %s\n", t->payload);
                printf("-> ");
                t->index = 0;
            }
        } else {
            if (t->index < TERMINAL_MAX_LEN - 1) {
                t->buffer[t->index++] = (char)c;
                putchar(c); // Echo
            }
        }
    }
}

bool terminal_has_command(Terminal* t) {
    return t->command_ready;
}

char* terminal_get_command(Terminal* t) {
    t->command_ready = false;
    return t->command;
}

char* terminal_get_payload(Terminal* t) {
    return t->payload;
}