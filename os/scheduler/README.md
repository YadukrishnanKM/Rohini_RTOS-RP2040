# RP2040 Simple Process Scheduler

A lightweight cooperative/preemptive process scheduler for the Raspberry Pi Pico (RP2040) built with the Pico SDK.  
This scheduler provides **basic process management** similar to Unix-like `fork()`, `exec()`, and `wait()` semantics, making it easier to create multitasking systems on bare-metal RP2040 applications.

---

## 📜 Overview

This library provides:

- **Process abstraction** with states (`READY`, `RUNNING`, `WAITING`, `TERMINATED`)
- **Static process control block (PCB)** structure for each process
- **Basic process creation** (`create_init_process`, `fork`)
- **Program replacement** (`exec`)
- **Blocking wait** for child termination (`wait`)
- **Graceful process exit** (`exit`)
- **Priority-based scheduling**
- **SysTick-driven preemption**

---

## 🛠 Features

- **Lightweight**: Minimal memory footprint, works without dynamic allocation.
- **Portable**: Uses Pico SDK’s standard headers (`pico/stdlib.h`).
- **Educational**: Models familiar Linux-like APIs for embedded systems.
- **Stack isolation**: Each process has its own dedicated stack space.

---

## 📂 File Structure

```

scheduler.h   // Header file (process definitions & APIs)
scheduler.c   // Implementation file
README.md     // Documentation (this file)

````

---

## 📦 Data Structures

### `process_state_t`
Enum for process states:

| State               | Meaning                                    |
|---------------------|--------------------------------------------|
| `PROCESS_READY`     | Ready to be scheduled                      |
| `PROCESS_RUNNING`   | Currently executing                        |
| `PROCESS_WAITING`   | Waiting for an event or other process       |
| `PROCESS_TERMINATED`| Finished execution                         |

---

### `process_t`
The Process Control Block (PCB) structure:

| Field          | Type          | Description |
|----------------|--------------|-------------|
| `sp`           | `uint32_t*`  | Stack pointer (for context switching) |
| `pid`          | `uint32_t`   | Unique process ID |
| `state`        | `process_state_t` | Current execution state |
| `priority`     | `uint8_t`    | Scheduling priority (higher = favored) |
| `entry_point`  | `void (*)(void)` | Function executed when scheduled |
| `stack[256]`   | `uint32_t[]` | Process stack (size adjustable) |
| `parent_pid`   | `int`        | PID of parent process |
| `exit_code`    | `int`        | Status returned by `exit()` |

---

## 📜 API Reference

### `void init_scheduler(void)`
Initializes internal scheduler data structures.  
Call **before** creating any process.

### `int fork(void)`
Creates a new process by cloning the current one.

- **Returns**:
  - PID of child (to parent process)
  - `0` to the child process
  - `-1` on failure

### `int exec(void (*new_func)(void))`
Replaces the currently running process code with a new function.

- **Parameters**:
  - `new_func`: Pointer to the function to execute.
- **Returns**:
  - `0` on success
  - `-1` on failure

### `void exit(int code)`
Terminates the current process.

- **Parameters**:
  - `code`: Exit status code visible to parent via `wait()`.

### `int wait(int pid)`
Waits for the specified process to terminate.

- **Parameters**:
  - `pid`: PID of child process.
- **Returns**:
  - Exit code of the terminated process.

### `void schedule(void)`
Selects the next ready process and switches context.  
Normally called from `SysTick_Handler()` for preemption.

### `void create_init_process(void (*func)(void))`
Manually creates the very first process to start the scheduler.

- **Parameters**:
  - `func`: Entry function for initial process.

### `void SysTick_Handler(void)`
SysTick ISR that performs preemptive scheduling.

---

## 🚀 Example: Parent and Child Process

The example below creates a parent process that forks a child.  
The child runs for **3 loops** and exits with a custom exit code, while the parent waits and reports the result.

```c
#include "pico/stdlib.h"
#include "scheduler.h"  // Your scheduler header

int child_pid = -1; // For clarity

// Child process: loops 3 times then exits
void child_task(void) {
    for (int i = 1; i <= 3; i++) {
        printf("[Child] Loop %d\n", i);
        sleep_ms(500);
    }
    printf("[Child] Exiting now.\n");
    exit(42); // Exit code 42
}

// Parent process: forks a child, waits for it, then keeps running
void parent_task(void) {
    printf("[Parent] Forking child...\n");
    child_pid = fork();

    if (child_pid == 0) {
        // Child
        exec(child_task);
    } else if (child_pid > 0) {
        // Parent
        printf("[Parent] Waiting for child PID %d\n", child_pid);
        int code = wait(child_pid);
        printf("[Parent] Child exited with code %d\n", code);

        while (1) {
            printf("[Parent] Still alive, doing work...\n");
            sleep_ms(1000);
        }
    } else {
        printf("[Parent] Fork failed!\n");
    }
}

int main() {
    stdio_init_all();

    init_scheduler();
    create_init_process(parent_task);

    while (1) {
        schedule();
    }
}
````

---

### 🖥 Example Output

```
[Parent] Forking child...
[Parent] Waiting for child PID 1
[Child] Loop 1
[Child] Loop 2
[Child] Loop 3
[Child] Exiting now.
[Parent] Child exited with code 42
[Parent] Still alive, doing work...
[Parent] Still alive, doing work...
...
```

---

## ⚙️ Configuration

* **Stack size**: Change `uint32_t stack[256]` in `process_t` to adjust per-process stack.
* **Priorities**: Higher `priority` values get scheduled first.

---

## 📜 License

GPL-3.0 License — see [LICENSE](../../LICENCE) for details.

---

## 🧠 Notes

* This is a **pre-release** educational scheduler.
* Not intended for production real-time critical tasks.
* No MMU or memory protection — all processes share the same address space.