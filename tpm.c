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
#include <clock.h>
#include <interrupts.h>
#include <limits.h>
#include <stdint.h>
#include <tpm.h>

#define TPM_SC_TOF                      7
#define TPM_SC_TOIE                     6
#define TPM_SC_CPWMS                    5
#define TPM_SC_CMOD                     3
#define TPM_SC_PS                       0

#define TPM_SC_CMOD_DISABLED            0
#define TPM_SC_CMOD_TPM_CLK             1
#define TPM_SC_CMOD_EXT_CLK             2

struct tpm_regs_t {
    volatile uint32_t status_ctrl;
    volatile uint32_t counter;
    volatile uint32_t modulo;
};

static struct tpm_regs_t * const tpm_regs[TPM_COUNT] =
    { (void *)0x40038000, (void *)0x40039000};
static const vector_t tpm_vectors[TPM_COUNT] =
    { VECTOR_TPM0, VECTOR_TPM1 };
static const clk_gate_t clk_gates[TPM_COUNT] =
    { CLK_GATE_TPM0, CLK_GATE_TPM1 };

void tpm_init(tpm_idx_t idx, uint32_t hz, isr_t handler)
{
    uint8_t psc;
    uint32_t mod;
    uint32_t scr;

    assert(idx < TPM_COUNT);

    clock_gate_enable(clk_gates[idx]);

    mod = CPU_HZ / hz;

    /* Increase prescalar until mod fits into the mod field */
    for (psc = 0; psc < 7; psc++) {
        if (mod <= USHRT_MAX)
            break;
        mod >>= 1;
    }

    scr = psc;

    if (handler) {
        scr |= (1 << TPM_SC_TOF) | (1 << TPM_SC_TOIE);
        interrupt_enable(tpm_vectors[idx], handler);
    }

    tpm_regs[idx]->modulo = mod;
    tpm_regs[idx]->counter = 0;
    tpm_regs[idx]->status_ctrl = scr;
}

void tpm_enable(tpm_idx_t idx)
{
    assert(idx < TPM_COUNT);
    tpm_regs[idx]->status_ctrl |= (1 << TPM_SC_CMOD);
}

void tpm_disable(tpm_idx_t idx)
{
    assert(idx < TPM_COUNT);
    tpm_regs[idx]->status_ctrl &= ~(0x3 << TPM_SC_CMOD);
}

void tpm_isr_first(tpm_idx_t idx)
{
    assert(idx < TPM_COUNT);
    /* Clear interrupt */
    tpm_regs[idx]->status_ctrl |= (1 << TPM_SC_TOF);
}
