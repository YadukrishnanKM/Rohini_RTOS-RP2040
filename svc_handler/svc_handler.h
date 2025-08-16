#pragma once

#include "pico/stdlib.h"
#include "pico/sleep.h"
#include "ros_cmsis_compat.h"


#ifdef __cplusplus
extern "C" {
#endif


//-----------------------------------------------------------------------------
// 1. SVC Numbers
//-----------------------------------------------------------------------------
typedef enum {
    RESET,
    MASTER_CAUTION,
    GO_TO_DORMANT,
    TERMINAL_WRITE,
    TERMINAL_READ,
} svc_id_t;

//-----------------------------------------------------------------------------
// 2. Low-level SVC invocations
//-----------------------------------------------------------------------------
static inline __attribute__((always_inline)) uint32_t svc_comp_time(uint8_t id) 
{
    register uint32_t r0 __asm__("r0");
    __asm__ volatile (
        "svc %[imm]\n"
        : "=r"(r0)
        : [imm] "I"(id)
        : "memory"
    );
    return r0;
}

static inline __attribute__((always_inline)) uint32_t svc_runtime(uint8_t id) {
    register uint32_t r0 asm("r0") = id;
    __asm volatile ("svc 0" : "+r"(r0) : : "memory");
    return r0;
}


static inline __attribute__((always_inline)) uint32_t svc_arg(uint8_t id, uint32_t a0)
{
    register uint32_t r0 __asm__("r0") = a0;
    __asm__ volatile (
        "svc %[imm]\n"
        : "+r"(r0)
        : [imm] "I"(id)
        : "memory"
    );
    return r0;
}

//-----------------------------------------------------------------------------
// 3. Friendly wrappers
//-----------------------------------------------------------------------------
static inline void svc_call_reset(void) { (void)svc_comp_time(RESET); }
static inline void svc_call_master_caution(void) { (void)svc_comp_time(MASTER_CAUTION); }
static inline void svc_call_go_to_dormant_gpio_irq(void) { (void)svc_comp_time(GO_TO_DORMANT); }

// If your SVC handlers take/return values, use svc1, svc2, etc.
// e.g., static inline uint32_t svc_get_value(uint32_t key) {
//           return svc1(MY_SVC_GET, key);
//       }

//-----------------------------------------------------------------------------
// 4. Handler prototypes (to be implemented by user or overridden)
//-----------------------------------------------------------------------------
static void software_reset(void) __attribute__((used));
static void master_caution(void) __attribute__((used));
static void go_to_dormant_gpio_irq(uint8_t gpio_pin) __attribute__((used));

#ifdef __cplusplus
}
#endif
