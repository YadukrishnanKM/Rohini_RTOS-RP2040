#pragma once
#include "pico/stdlib.h"

/// @brief Enum representing the possible states of a process
typedef enum {
    PROCESS_READY,       // Process is ready to run
    PROCESS_RUNNING,     // Currently running
    PROCESS_WAITING,     // Waiting for an event or another process
    PROCESS_TERMINATED   // Finished execution
} process_state_t;

/// @brief Structure representing a process in the system
typedef struct {
    uint32_t* sp;               // Stack pointer for context switching
    uint32_t pid;               // Unique process ID
    process_state_t state;      // Current state of the process
    uint8_t priority;           // Scheduling priority (higher is favored)
    void (*entry_point)(void);  // Function to execute when process runs
    uint32_t stack[256];        // Process stack (adjust size as needed)
    int parent_pid;             // PID of the parent process (if forked)
    int exit_code;              // Exit status set by exit()
} process_t;

/// @brief Initialize internal data structures for the scheduler
void init_scheduler(void);

/// @brief Clone current process to create a new one (similar to fork in Linux)
/// @return PID of the new process, or -1 on failure
int fork(void);

/// @brief Replace current process’s code with new function (like exec in Linux)
/// @param new_func Pointer to new function to execute
/// @return 0 on success, -1 on failure
int exec(void (*new_func)(void));

/// @brief Terminate current process and set its exit status
/// @param code Exit status (visible to parent via wait)
void exit(int code);

/// @brief Wait for a process to terminate by PID
/// @param pid PID of the child process to wait on
/// @return Exit code of terminated child
int wait(int pid);

/// @brief Choose the next process to run and switch context
void schedule(void);

/// @brief Manually create the first process to kickstart scheduler
/// @param func Function to assign as entry point of initial process
void create_init_process(void (*func)(void));

/// @brief Interrupt service routine for SysTick timer (used for preemptive scheduling)
void SysTick_Handler(void);

