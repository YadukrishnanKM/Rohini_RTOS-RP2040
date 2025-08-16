#include "terminal_core.h"
#include "terminal.h"
#include "pico/multicore.h"
#include <string.h>
#include <stdio.h>

terminal_core_state_t terminal_state = {
    .last_command = {0},
    .last_payload = {0},
    .command_ready = false
};

static void terminal_core_loop() {
    Terminal term;
    terminal_init(&term);

    while (true) {
        terminal_update(&term);

        if (terminal_has_command(&term)) {
            // Read and store command + payload
            const char* cmd = terminal_get_command(&term);
            const char* payload = terminal_get_payload(&term);

            strncpy(terminal_state.last_command, cmd, TERMINAL_CMD_MAX_LEN - 1);
            terminal_state.last_command[TERMINAL_CMD_MAX_LEN - 1] = '\0';

            strncpy(terminal_state.last_payload, payload, TERMINAL_PAYLOAD_MAX_LEN - 1);
            terminal_state.last_payload[TERMINAL_PAYLOAD_MAX_LEN - 1] = '\0';

            terminal_state.command_ready = true;

            // Optional: Echo command confirmation
            terminal_write(&term, "Command received\r\n");
        }
    }
}

void terminal_core_launch(void) {
    multicore_launch_core1(terminal_core_loop);
}

/*

example

#include "terminal_core.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>

int main() {
    stdio_init_all();
    terminal_core_launch();  // Run terminal on Core 1

    while (true) {
        if (terminal_state.command_ready) {
            printf("Command: %s\n", terminal_state.last_command);
            printf("Payload: %s\n", terminal_state.last_payload);

            // Example: react to a specific command
            if (strcmp(terminal_state.last_command, "blink") == 0) {
                // Do something like toggling an LED
                printf("Blinking LED...\n");
            }

            terminal_state.command_ready = false; // Reset after handling
        }

        sleep_ms(100);  // Core 0 polling loop
    }

    return 0;
}


*/