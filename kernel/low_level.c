#include "types.h"
#include "memory_map.h"
uint8_t get_cpu_id(){
    uint8_t cpu_id;
    __asm__ volatile (
        "mrs %0, mpidr_el1"
    : "=r" (cpu_id)
    );
    return cpu_id;
}

void spin(){
    asm volatile("nop");
}


void enable_interrupts(){
    __asm__ volatile(
        "msr DAIFClr, 0xf"
    );
}
void disable_interrupts(){
    __asm__ volatile(
        "msr DAIFset, 0xf"
    );
}


//void disable_interrupts(){}

/*
void enable_timer_interrupt(){
    uint8_t cpu_id = get_cpu_id();
    volatile uint32_t *cpu_control_reg_addr;
    switch (cpu_id)
    {
    case 0:
        cpu_control_reg_addr = CORE0_TIMER_IRQ_CTRL;
        break;
     case 1:
        cpu_control_reg_addr = CORE1_TIMER_IRQ_CTRL;
        break;
     case 2:
        cpu_control_reg_addr = CORE2_TIMER_IRQ_CTRL;
        break;
     case 3:
        cpu_control_reg_addr = CORE3_TIMER_IRQ_CTRL;
        break;
    default:
    }

    __asm__ volatile(
        "mov x0, 1\n"
        "msr cntp_ctl_el0, x0\n" // enable
        "mrs x0, cntfrq_el0\n"
        "msr cntp_tval_el0, x0\n" // set expired time
        : // no output operads
        : 
        : "x0" 
    );
   *cpu_control_reg_addr = 2;  
}
*/
//void disable_timer();