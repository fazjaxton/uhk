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
#include <pinmux.h>
#include <stdint.h>

#define PORT_PCR_MUX                    8

struct pinmux_regs_t {
    volatile uint32_t control[32];
};

static struct pinmux_regs_t *pinmux_regs[PORT_COUNT] = 
    { (void *)0x40049000, (void *)0x4004A000 };

void pinmux_set_function(gpio_t gpio, pin_func_t func)
{
    struct pinmux_regs_t *regs;
    uint32_t val;
    uint8_t pin;

    assert(gpio < PIN_MAX);
    assert(func < 6);

    pin = pin_from_gpio(gpio);
    regs = pinmux_regs[port_from_gpio(gpio)];
    val = regs->control[pin];
    val &= (0x7 << PORT_PCR_MUX);
    val |= (func << PORT_PCR_MUX);
    regs->control[pin] = val;
}
