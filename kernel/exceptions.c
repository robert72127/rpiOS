#include "types.h"
#include "memory_map.h"
#include "definitions.h"
#include "low_level.h"

void exception_handler(unsigned long state,unsigned long type, unsigned long esr, unsigned long elr, unsigned long spsr, unsigned long far)
{
    // print out state
    switch(state) {
        case 0: uart_puts("EL1T"); break;
        case 1: uart_puts("EL1H"); break;
        case 2: uart_puts("EL0_64"); break;
        case 3: uart_puts("EL0_32"); break;
    }
    uart_puts(":\t");
    // print out interruption type
    switch(type) {
        case 0: uart_puts("Synchronous"); break;
        case 1: uart_puts("IRQ"); break;
        case 2: uart_puts("FIQ"); break;
        case 3: uart_puts("SError"); break;
    }
    uart_puts(":\n");
    // decode exception type (some, not all. See ARM DDI0487B_b chapter D10.2.28)
    switch(esr>>26) {
        case 0b000000: uart_puts("Unknown"); break;
        case 0b000001: uart_puts("Trapped WFI/WFE"); break;
        case 0b001110: uart_puts("Illegal execution"); break;
        case 0b010101: uart_puts("System call"); break;
        case 0b100000: uart_puts("Instruction abort, lower EL"); break;
        case 0b100001: uart_puts("Instruction abort, same EL"); break;
        case 0b100010: uart_puts("Instruction alignment fault"); break;
        case 0b100100: uart_puts("Data abort, lower EL"); break;
        case 0b100101: uart_puts("Data abort, same EL"); break;
        case 0b100110: uart_puts("Stack alignment fault"); break;
        case 0b101100: uart_puts("Floating point"); break;
        default: uart_puts("Unknown"); break;
    }
    uart_puts("\n");
    // decode data abort cause
    if(esr>>26==0b100100 || esr>>26==0b100101) {
        uart_puts(", ");
        switch((esr>>2)&0x3) {
            case 0: uart_puts("Address size fault"); break;
            case 1: uart_puts("Translation fault"); break;
            case 2: uart_puts("Access flag fault"); break;
            case 3: uart_puts("Permission fault"); break;
        }
        switch(esr&0x3) {
            case 0: uart_puts(" at level 0"); break;
            case 1: uart_puts(" at level 1"); break;
            case 2: uart_puts(" at level 2"); break;
            case 3: uart_puts(" at level 3"); break;
        }
    }
    uart_puts("\n");
    // dump registers
    /*
    uart_puts(":\n  ESR_EL1 ");
    uart_hex(esr>>32);
    uart_hex(esr);
    uart_puts(" ELR_EL1 ");
    uart_hex(elr>>32);
    uart_hex(elr);
    uart_puts("\n SPSR_EL1 ");
    uart_hex(spsr>>32);
    uart_hex(spsr);
    uart_puts(" FAR_EL1 ");
    uart_hex(far>>32);
    uart_hex(far);
    uart_puts("\n");
    */
    // no return from exception for now
}


void handle_irq(){
 //uint32_t irq_req = *IRQ_PENDING_1;

 //switch (irq_req)
    //uart
 //   case (SYSTEm)
    /*
    while(uart_irq_pending){
        char chr =  uart_getc();
        while (chr != -1 && chr != 0)
            uart_send(chr);
    }
    */
    
    uint32_t iir = *AUX_MU_IIR;
    char c;
    // check if pending interrupts is for mini uart
    // check if it's read
    if(*AUX_IRQ && 0x1) {
        if( iir & 0b100){
          c = uart_getc();
          while( c != 255 ){
            uart_send(c);
            c = uart_getc();
          }
        }
    
        // reset interrupt pending
    }
    *AUX_MU_IIR &= 0b001;
}
