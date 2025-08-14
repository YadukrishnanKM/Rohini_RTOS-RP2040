/**
 * @file terminal.h
 * @brief Simple terminal interface for RP2040 using the Pico SDK.
 *
 * Provides a minimal line-based shell over USB STDIO. It reads characters,
 * echoes them, splits the first token as the command, and treats the rest
 * as payload data.
 */

#pragma once

#include "pico/stdlib.h"  // Pico SDK stdio and basic definitions

/// Maximum number of characters (including terminating '\0') the input buffer can hold.
#define TERMINAL_MAX_LEN 256

/**
 * @struct Terminal
 * @brief Holds the state and buffers for the terminal interface.
 *
 * buffer         – raw character buffer until newline
 * index          – current write position in buffer  
 * command_ready  – true when a full line (command + payload) is parsed 
 * command[64]    – NUL-terminated first token (the command keyword)  
 * payload[192]   – NUL-terminated remainder of the line  
 */
typedef struct {
    char buffer[TERMINAL_MAX_LEN];
    int  index;
    bool command_ready;
    char command[64];
    char payload[192];
} Terminal;

/**
 * @brief Initialize terminal state and print the prompt.
 *
 * Resets indexes and flags, clears buffers, and outputs the first "-> " prompt.
 *
 * @param t Pointer to the Terminal instance to initialize.
 */
static void terminal_init(Terminal* t) __attribute__((no_inline));

/**
 * @brief Read and process incoming characters from USB STDIO.
 *
 * - Reads all available characters (non-blocking).  
 * - Echoes each character back to the host.  
 * - On '\r' or '\n':
 *   - Terminates buffer with NUL.  
 *   - Splits buffer into command (first word) and payload (rest).  
 *   - Sets command_ready flag.  
 *   - Prints parsed command, payload, and reprints "-> " prompt.  
 *   - Resets index to 0 for next line.  
 *
 * @param t Pointer to the Terminal instance to update.
 */
static void terminal_update(Terminal* t) __attribute__((no_inline));

/**
 * @brief Query whether a complete command has been received.
 *
 * After a line break is processed, this returns true until get_command() is called.
 *
 * @param t Pointer to the Terminal instance.
 * @return true if a command+payload pair is ready to be handled.
 * @return false otherwise.
 */
static bool terminal_has_command(Terminal* t) __attribute__((no_inline));

/**
 * @brief Retrieve the parsed command token.
 *
 * Clears the command_ready flag so subsequent calls to has_command() return false.
 *
 * @param t Pointer to the Terminal instance.
 * @return Pointer to a NUL-terminated string containing the command.
 */
static char* terminal_get_command(Terminal* t) __attribute__((no_inline));

/**
 * @brief Retrieve the payload string (everything after the command token).
 *
 * Payload remains intact until the next update() and does not affect the ready flag.
 *
 * @param t Pointer to the Terminal instance.
 * @return Pointer to a NUL-terminated string containing the payload.
 */
static char* terminal_get_payload(Terminal* t);