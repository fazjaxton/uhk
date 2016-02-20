#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include <stdint.h>

#define VECTOR_COUNT                    48

typedef uint8_t vector_t;

typedef void (*isr_t)(void);


static inline void interrupt_global_enable(void)
{
    asm("CPSIE i":::);
}

static inline void interrupt_global_disable(void)
{
    asm("CPCIE i":::);
}

void interrupt_init(void);
void interrupt_vector_set_handler(vector_t vector, isr_t handler);
void interrupt_enable(vector_t vector, isr_t handler);
void interrupt_disable(vector_t vector);

#endif
