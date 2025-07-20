#include <stdio.h>
#include "pico/stdlib.h"
#include "kernel.h"

int main() {
    setup_default_uart();
    printf("Hello, world!\n");
    return 0;
    
}
