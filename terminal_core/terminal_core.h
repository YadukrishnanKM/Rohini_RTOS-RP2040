#pragma once

#include "pico/stdlib.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Maximum command and payload sizes
#define TERMINAL_CMD_MAX_LEN     64
#define TERMINAL_PAYLOAD_MAX_LEN 192

/**
 * @struct terminal_core_state_t
 * @brief Shared state between Core 0 and Core 1 terminal loop.
 */
typedef struct {
    /// Command received from user input (e.g., "start", "led_on", etc.)
    char last_command[TERMINAL_CMD_MAX_LEN];

    /// Payload after the command (e.g., "arg1 arg2")
    char last_payload[TERMINAL_PAYLOAD_MAX_LEN];

    /// True when a new command is ready for processing (set by Core 1, cleared by Core 0)
    volatile bool command_ready;

    // Add more flags or fields as needed (e.g., for signaling results or tasks)
} terminal_core_state_t;

/// Global shared terminal state
extern terminal_core_state_t terminal_state;

/**
 * @brief Launch the terminal loop on Core 1.
 *
 * Initializes terminal and starts a loop that listens for user input.
 * Populates `terminal_state` with commands typed from the terminal.
 */
void terminal_core_launch(void);

#ifdef __cplusplus
}
#endif
