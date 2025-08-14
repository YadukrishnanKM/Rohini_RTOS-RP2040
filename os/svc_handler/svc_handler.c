#include "svc_handler.h"

//-----------------------------------------------------------------------------
// Weak default implementations.
// Linker will pick user-provided symbols if they exist.
//-----------------------------------------------------------------------------

static void software_reset(void)
{
    NVIC_SystemReset();

}


static void master_caution(void) //yet to complete
{
    // Default stub:  overridein your application, now modified with __attribute__((used));
}


static void go_to_dormant_gpio_irq(uint8_t gpio_pin)
{
    sleep_run_from_xosc();
    sleep_goto_dormant_until_pin(gpio_pin, true, true);

}