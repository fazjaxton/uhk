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

#ifndef __CLOCK_H
#define __CLOCK_H

#include <stdint.h>

#define CPU_HZ                          8000000

#define CLK_GATE_BIT(reg, bit)          (((reg) << 5) | (bit))

enum {
    CLK_GATE_REG_4,
    CLK_GATE_REG_5,
    CLK_GATE_REG_6,
};

typedef uint8_t clk_gate_t;
enum {
    CLK_GATE_I2C0                       = CLK_GATE_BIT(CLK_GATE_REG_4, 6),
    CLK_GATE_CMP0                       = CLK_GATE_BIT(CLK_GATE_REG_4, 19),
    CLK_GATE_VREF                       = CLK_GATE_BIT(CLK_GATE_REG_4, 20),
    CLK_GATE_SPI0                       = CLK_GATE_BIT(CLK_GATE_REG_4, 22),
    CLK_GATE_LPTMR                      = CLK_GATE_BIT(CLK_GATE_REG_5, 0),
    CLK_GATE_PORT_A                     = CLK_GATE_BIT(CLK_GATE_REG_5, 9),
    CLK_GATE_PORT_B                     = CLK_GATE_BIT(CLK_GATE_REG_5, 10),
    CLK_GATE_LPUART0                    = CLK_GATE_BIT(CLK_GATE_REG_5, 20),
    CLK_GATE_FTF                        = CLK_GATE_BIT(CLK_GATE_REG_6, 0),
    CLK_GATE_TPM0                       = CLK_GATE_BIT(CLK_GATE_REG_6, 24),
    CLK_GATE_TPM1                       = CLK_GATE_BIT(CLK_GATE_REG_6, 25),
    CLK_GATE_ADC0                       = CLK_GATE_BIT(CLK_GATE_REG_6, 27),
    CLK_GATE_RTC                        = CLK_GATE_BIT(CLK_GATE_REG_6, 29),

    CLK_GATE_MAX
};

void clock_gate_enable(clk_gate_t gate);
void clock_gate_disable(clk_gate_t gate);

#endif
