/**
 * Copyright 2016  Kevin Smith <thirdwiggin@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <assert.h>
#include <interrupts.h>

#define VTOR                            *((volatile uint32_t *)0xe000ed08)
#define NVIC_ISER                       *((volatile uint32_t *)0xe000e100)
#define NVIC_ICER                       *((volatile uint32_t *)0xe000e180)
#define NVIC_ICPR                       *((volatile uint32_t *)0xe000e280)
#define NVIC_IPRN                       *((volatile uint32_t *)0xe000e400)

#define IRQ_OFFSET                      16

typedef uint8_t irq_t;

static isr_t vector_table[VECTOR_COUNT]
                    __attribute__((aligned(32 * sizeof(isr_t))));

extern unsigned long __stack[];
void _cstartup(void);

static inline irq_t irq_from_vector(vector_t vector)
{
    assert(vector < VECTOR_COUNT);
    return vector - IRQ_OFFSET;
}

void interrupt_init(void)
{
    uint8_t i;

    vector_table[0] = (isr_t)__stack;
    vector_table[1] = (isr_t)_cstartup;

    for (i = 2; i < VECTOR_COUNT; i++)
        vector_table[i] = _cstartup;

    VTOR = (uint32_t)vector_table;
}

void interrupt_vector_set_handler(vector_t vector, isr_t handler)
{
    assert(vector < VECTOR_COUNT);

    vector_table[vector] = handler;
}

void interrupt_enable(vector_t vector, isr_t handler)
{
    irq_t irq;

    assert(vector < VECTOR_COUNT);
    assert(vector >= IRQ_OFFSET);

    irq = irq_from_vector(vector);

    interrupt_vector_set_handler(vector, handler);
    NVIC_ISER = (1 << irq);
}

void interrupt_disable(vector_t vector)
{
    NVIC_ICER = (1 << irq_from_vector(vector));
}
