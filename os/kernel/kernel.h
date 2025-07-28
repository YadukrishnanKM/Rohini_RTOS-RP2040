#pragma once
/** 
 * @file kernel.h
 * @brief C++ wrapper around the RP2040 scheduler for preemptive multitasking.
 * 
 * Provides Kernel and Process abstractions, plus core1 launch support.
 */

#include "pico/stdlib.h"
#include "pico/multicore.h"

extern "C" {
    #include "scheduler.h"
}

extern "C" {
    #include "terminal_core.h"
}

namespace rohini {

/**
 * @brief The Kernel class initializes hardware and drives the scheduler.
 */
class Kernel {
public:
    /**
     * @brief Initialize clocks, USB STDIO, and the C scheduler.
     * 
     * Must be called on Core 0 before launching Core 1 or creating tasks.
     */
    static void init() {
        stdio_init_all();
        init_scheduler();

    }

    /**
     * @brief Create the initial process that the scheduler will run.
     * 
     * Equivalent to `create_init_process()` in C.
     * @param entry  Function pointer to the task entry.
     */
    static void create_init(void (*entry)(void)) {
        create_init_process(entry);
    }

    /**
     * @brief Launch the preemptive scheduler on Core 1.
     * 
     * Core 1 will run its own loop; scheduling is driven by SysTick interrupts.
     */
    static void launch_core1() {
        multicore_launch_core1([]() {
            // Core 1 idles; SysTick_Handler will call schedule()
            while (true) tight_loop_contents();
        });
    }

    /**
     * @brief Yield execution to the next ready process.
     * 
     * Wraps the C `schedule()` function.
     */
    static void yield() {
        schedule();
    }

    /**
     * @brief Fork the current process.
     * 
     * Wraps the C `fork()` and returns the child's PID or -1 on error.
     */
    static int fork() {
        return ::fork();
    }

    /**
     * @brief Replace the current process's code with a new entry.
     * 
     * Wraps the C `exec()` and returns 0 on success or -1 on failure.
     * @param entry  New function pointer to execute.
     */
    static int exec(void (*entry)(void)) {
        return ::exec(entry);
    }

    /**
     * @brief Terminate the current process with an exit code.
     * 
     * Wraps the C `exit()`.
     * @param code  Exit status.
     */
    static void exit(int code) {
        ::exit(code);
    }

    /**
     * @brief Wait for a child process to terminate.
     * 
     * Wraps the C `wait()` and returns the child's exit code or -1 on error.
     * @param pid  PID of the child to wait on.
     */
    static int wait(int pid) {
        return ::wait(pid);
    }

};

/**
 * @brief Base class for C++ processes/tasks.
 * 
 * Derive from Process and implement `run()`. Use `spawn()` to register.
 */
class Process {
public:
    virtual ~Process() = default;

    /**
     * @brief Entry point for the C++ task.
     * 
     * Scheduler will invoke this method each time the process is dispatched.
     */
    virtual void run() = 0;

    /**
     * @brief Register this Process with the scheduler.
     * 
     * Internally creates a C‐style init process that calls the `entry_wrapper()`.
     * Should be called after Kernel::init() but before Kernel::launch_core1().
     */
    void spawn() {
        // Store pointer for the static wrapper
        instance_ = this;
        Kernel::create_init(&Process::entry_wrapper);
    }

private:
    static Process* instance_;

    /**
     * @brief Static wrapper to transition from C to C++.
     * 
     * Invokes `instance_->run()` and exits automatically on return.
     */
    static void entry_wrapper() {
        instance_->run();
        Kernel::exit(0);
    }
};

} // namespace rp2040_os