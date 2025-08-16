#ifndef ROS_CMSIS_COMPAT_H
#define ROS_CMSIS_COMPAT_H

// Use Pico SDK's IRQ enum
#include "hardware/regs/intctrl.h"  // defines UART0_IRQ, etc.
typedef enum irq_num_rp2040 IRQn_Type;

// Define NVIC priority bits for RP2040
#define __NVIC_PRIO_BITS 2

// Now include CMSIS core
#include "core_cm0plus.h"

#endif // ROS_CMSIS_COMPAT_H