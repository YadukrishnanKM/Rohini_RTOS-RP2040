.syntax unified
.thumb
.global SVC_Handler
.global trigger_svc

.global software_reset
.global master_caution
.global go_to_dormant_gpio_irq

.type SVC_Handler, %function
.type trigger_svc, %function

// C-callable wrapper — pass argument in R3 -> R12 (optional)
trigger_svc:
    SVC #0        // Replace immediate with desired value in test
    BX LR

// Function prototypes (implemented in C or assembly elsewhere)
.extern software_reset
.extern master_caution
.extern go_to_dormant_gpio_irq

SVC_Handler:
    // Determine which stack (MSP or PSP)
    TST LR, #4
    MRS R0, PSP
    BEQ use_msp
    MRS R0, MSP
use_msp:
    // R0 now points to the stack frame
    LDR R1, [R0, #24]      // Get stacked PC into R1

    // SVC instruction is at PC - 2 (Thumb mode)
    SUB R1, R1, #2
    LDRB R2, [R1]          // Load the immediate value (SVC number)

    // Dispatch based on R2
    CMP R2, #0
    BEQ call_software_reset
    CMP R2, #1
    BEQ call_master_caution
    CMP R2, #2
    BEQ call_go_to_dormant_gpio_irq

    BX LR                  // Default return

call_software_reset:
    BL software_reset
    BX LR

call_software_reset:
    BL master_caution
    BX LR

call_software_reset:
    BL go_to_dormant_gpio_irq
    BX LR