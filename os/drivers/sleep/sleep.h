#pragma once

#include "hardware/structs/systick.h"
#include "hardware/structs/timer.h"
#include "hardware/structs/clocks.h"

#ifdef __cplusplus
extern "C" {
#endif

// ─────────────────────────────────────────────────────────────
// Default system clock frequency (in Hz)
// Override this macro before including if using a custom clock
#ifndef RP2040_SYSCLK_HZ
#define RP2040_SYSCLK_HZ 125000000u  // Default 125 MHz
#endif

// ─────────────────────────────────────────────────────────────
// Sleep for a specified number of microseconds
// Uses RP2040 hardware timer (timerawl), no branches
static inline void sleep_us(uint32_t us) {
    uint64_t start = timer_hw->timerawl;
    uint64_t target = start + us;
    while (timer_hw->timerawl < target) __asm volatile("nop");
}

// Sleep for a specified number of milliseconds
// Internally calls sleep_us()
static inline void sleep_ms(uint32_t ms) {
    sleep_us(ms * 1000u);
}

// Arduino-style delay in milliseconds
// Alias for sleep_ms()
static inline void delay(uint32_t ms) {
    sleep_ms(ms);
}

// Arduino-style delay in microseconds
// Alias for sleep_us()
static inline void delayMicroseconds(uint32_t us) {
    sleep_us(us);
}

// Sleep for a number of CPU cycles
// Converts cycles to microseconds using RP2040_SYSCLK_HZ
static inline void sleep_cycles(uint32_t cycles) {
    uint32_t us = cycles / (RP2040_SYSCLK_HZ / 1000000u);
    sleep_us(us);
}

// Sleep for a number of SysTick ticks
// Converts ticks to microseconds using RP2040_SYSCLK_HZ
static inline void sleep_ticks(uint32_t ticks) {
    uint32_t tick_us = 1000000u / RP2040_SYSCLK_HZ;
    sleep_us(ticks * tick_us);
}

// Get time since boot in microseconds
// Reads directly from timerawl
static inline uint64_t micros(void) {
    return timer_hw->timerawl;
}

// Get time since boot in milliseconds
// Derived from timerawl
static inline uint32_t millis(void) {
    return (uint32_t)(timer_hw->timerawl / 1000u);
}

#ifdef __cplusplus
}
#endif