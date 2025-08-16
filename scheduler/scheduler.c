#include "scheduler.h"

#define MAX_PROCESSES 8

process_t process_table[MAX_PROCESSES];
int current_pid = -1;
int next_pid = 0;

void init_scheduler() {
    memset(process_table, 0, sizeof(process_table));
    current_pid = -1;
    next_pid = 0;
}

void create_init_process(void (*func)(void)) {
    process_t* proc = &process_table[next_pid];
    proc->pid = next_pid;
    proc->entry_point = func;
    proc->priority = 1;
    proc->state = PROCESS_READY;
    proc->sp = &proc->stack[255]; // Simplified stack setup
    next_pid++;
}

int fork() {
    if (current_pid == -1 || next_pid >= MAX_PROCESSES)
        return -1;

    process_t* parent = &process_table[current_pid];
    process_t* child = &process_table[next_pid];

    memcpy(child->stack, parent->stack, sizeof(parent->stack));

    child->pid = next_pid;
    child->priority = parent->priority;
    child->state = PROCESS_READY;
    child->sp = child->stack + 256 - ((uint32_t)(parent->stack + 256) - (uint32_t)(parent->sp)) / sizeof(uint32_t);
    child->entry_point = parent->entry_point;
    child->parent_pid = parent->pid;

    return next_pid++;
}

int exec(void (*new_func)(void)) {
    if (current_pid == -1) return -1;

    process_t* proc = &process_table[current_pid];
    proc->entry_point = new_func;
    memset(proc->stack, 0, sizeof(proc->stack));
    proc->sp = &proc->stack[255]; // Reset SP
    return 0;
}

void exit(int code) {
    if (current_pid == -1) return;
    process_table[current_pid].state = PROCESS_TERMINATED;
    process_table[current_pid].exit_code = code;
    schedule();
}

int wait(int pid) {
    for (;;) {
        if (process_table[pid].state == PROCESS_TERMINATED)
            return process_table[pid].exit_code;
    }
}

void schedule() {
    int next = -1;
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (process_table[i].state == PROCESS_READY) {
            next = i;
            break;
        }
    }

    if (next != -1) {
        current_pid = next;
        process_table[next].state = PROCESS_RUNNING;
        process_table[next].entry_point();
    }
}

void SysTick_Handler() {
    schedule();
}