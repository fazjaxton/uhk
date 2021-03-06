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

#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include <stdint.h>

typedef uint8_t vector_t;
enum {
    VECTOR_NMI                          = 3,
    VECTOR_HARD_FAULT                   = 4,
    VECTOR_SVCALL                       = 11,
    VECTOR_PENDABLE_SRV_REQ             = 14,
    VECTOR_SYSTICK                      = 15,
    VECTOR_FTFA                         = 21,
    VECTOR_PMC                          = 22,
    VECTOR_LLWU                         = 23,
    VECTOR_I2C0                         = 24,
    VECTOR_SPI0                         = 26,
    VECTOR_LPUART0                      = 28,
    VECTOR_ADC0                         = 31,
    VECTOR_CMP0                         = 32,
    VECTOR_TPM0                         = 33,
    VECTOR_TPM1                         = 34,
    VECTOR_RTC_ALARM                    = 36,
    VECTOR_RTC_SECONDS                  = 37,
    VECTOR_LPTMR0                       = 44,
    VECTOR_PORT_A                       = 46,
    VECTOR_PORT_B                       = 47,
    VECTOR_COUNT
};

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
