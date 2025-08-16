# Rohini RTOS C++ Kernel Wrapper

This library provides a **C++ object-oriented interface** over the RP2040 scheduler (implemented in C) to enable **preemptive multitasking** on the Raspberry Pi Pico.  
It wraps the `scheduler.h` API in a `Kernel` class and adds a base `Process` class for creating tasks in an idiomatic C++ style.  
It also supports **dual-core** operation using `pico/multicore.h`.

---

## 📜 Overview

The `Kernel` class handles:
- Initialization of hardware and the scheduler
- Creating initial processes
- Launching the scheduler loop on Core 1
- Forking, executing, waiting, and exiting processes

The `Process` class:
- Serves as a base for defining tasks with a `run()` method
- Bridges the C scheduler entry points with C++ methods
- Automatically calls `Kernel::exit()` after `run()` returns

---

## 📂 File Structure

```

kernel.h         // C++ wrapper (this file)
scheduler.h/c    // C scheduler backend
terminal\_core.h  // Optional terminal integration for debugging

```

---

## ⚙️ Architecture

The RP2040 scheduler runs in C but can be controlled from C++.  
Core 0 initializes and sets up processes.  
Core 1 runs the preemptive scheduling loop triggered by SysTick interrupts.

```

┌───────────────┐
│  Core 0       │
│ init()        │
│ create\_init()│
│ fork/exec/... │
└─────┬─────────┘
│
▼
┌───────────────┐
│  Core 1       │
│ launch\_core1 │
│ schedule()    │
│ (preemption)  │
└───────────────┘

````

---

## 📜 API Reference

### `Kernel` Static Methods
| Method | Description |
|--------|-------------|
| `init()` | Initializes clocks, USB stdio, and the C scheduler. Must be called first on Core 0. |
| `create_init(void (*entry)(void))` | Creates the first process for the scheduler. |
| `launch_core1()` | Starts the scheduler loop on Core 1. |
| `yield()` | Yields control to another ready process. |
| `fork()` | Forks the current process, returning PID or -1. |
| `exec(void (*entry)(void))` | Replaces the current process's code with a new entry point. |
| `exit(int code)` | Terminates the current process. |
| `wait(int pid)` | Waits for a child process to terminate and returns its exit code. |

---

### `Process` Base Class
| Method | Description |
|--------|-------------|
| `run()` | Override in derived class to define the task logic. |
| `spawn()` | Registers the process with the scheduler. Must be called after `Kernel::init()` and before `Kernel::launch_core1()`. |

---

## 🚀 Example — Parent/Child in C++

The following program demonstrates:
- Creating a parent process in C++
- Forking to create a child
- Running the child for 3 loops and exiting
- Parent waits for child’s exit code

```cpp
#include "pico/stdlib.h"
#include "kernel.h"

using namespace rohini;

class ParentProcess : public Process {
public:
    void run() override {
        printf("[Parent] Forking child...\n");
        int pid = Kernel::fork();

        if (pid == 0) {
            // Child process
            Kernel::exec(&child_entry);
        } else if (pid > 0) {
            // Parent process
            printf("[Parent] Waiting for child PID %d\n", pid);
            int code = Kernel::wait(pid);
            printf("[Parent] Child exited with code %d\n", code);

            while (true) {
                printf("[Parent] Still alive, doing work...\n");
                sleep_ms(1000);
            }
        } else {
            printf("[Parent] Fork failed!\n");
        }
    }

    static void child_entry() {
        for (int i = 1; i <= 3; i++) {
            printf("[Child] Loop %d\n", i);
            sleep_ms(500);
        }
        printf("[Child] Exiting now.\n");
        Kernel::exit(42);
    }
};

int main() {
    stdio_init_all();
    Kernel::init();

    ParentProcess parent;
    parent.spawn();

    Kernel::launch_core1();

    // Core 0 idle loop
    while (true) {
        Kernel::yield();
    }
}
````

---

### 🖥 Expected Output

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

## 🔧 Usage Notes

* `Kernel::init()` **must** be called before creating processes.
* Always call `spawn()` for `Process` subclasses **before** `Kernel::launch_core1()`.
* When `run()` returns, the process automatically calls `Kernel::exit(0)`.
* All processes share the same address space (no memory protection).

---

## 📜 License

GPL-3.0 License — see [LICENSE](../../LICENCE) for details.

---

## 🧠 Notes

This C++ wrapper is designed for **educational purposes** and small embedded multitasking systems.
It models Unix-style process management but omits complex features like MMU, signals, or file descriptors.

---
