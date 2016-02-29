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

#ifndef __TPM_H
#define __TPM_H

#include <stdint.h>
#include <interrupts.h>

typedef uint8_t tpm_idx_t;
enum {
    TPM_0,
    TPM_1,

    TPM_COUNT
};

void tpm_init(tpm_idx_t idx, uint32_t hz, isr_t handler);
void tpm_enable(tpm_idx_t idx);
void tpm_disable(tpm_idx_t idx);

#endif
