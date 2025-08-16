.syntax unified
.thumb

.global SVC_Handler
.global trigger_svc

.global software_reset
.global master_caution
.global go_to_dormant_gpio_irq

.type SVC_Handler, %function
.type trigger_svc, %function

@ C-callable wrapper — pass argument in R3 -> R12 (optional)
trigger_svc:
    svc #0                 @ Replace immediate with desired value in test
    bx lr

@ Function prototypes (implemented in C or assembly elsewhere)
.extern software_reset
.extern master_caution
.extern go_to_dormant_gpio_irq

SVC_Handler:
    @ Determine which stack (MSP or PSP)
    movs r1, #4            @ Bitmask for checking bit 2
    mov r2, lr             @ Copy LR into low register
    tst r2, r1             @ Test bit 2 of LR
    beq use_msp            @ If zero, use MSP
    mrs r0, psp            @ Else, use PSP
    b continue_handler

use_msp:
    mrs r0, msp            @ Use MSP

continue_handler:
    @ R0 now points to the stack frame
    ldr r1, [r0, #24]      @ Get stacked PC into R1

    @ SVC instruction is at PC - 2 (Thumb mode)
    subs r1, r1, #2
    ldrb r2, [r1]          @ Load the immediate value (SVC number)

    @ Dispatch based on R2
    cmp r2, #0
    beq call_software_reset
    cmp r2, #1
    beq call_master_caution
    cmp r2, #2
    beq call_go_to_dormant_gpio_irq

    bx lr                  @ Default return

call_software_reset:
    bl software_reset
    bx lr

call_master_caution:
    bl master_caution
    bx lr

call_go_to_dormant_gpio_irq:
    bl go_to_dormant_gpio_irq
    bx lr