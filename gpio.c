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
#include <gpio.h>
#include <pinmux.h>
#include <stdbool.h>
#include <stdint.h>

struct gpio_regs_t {
    volatile uint32_t output;
    volatile uint32_t set;
    volatile uint32_t clear;
    volatile uint32_t toggle;
    volatile uint32_t input;
    volatile uint32_t direction;
};

static struct gpio_regs_t * const gpio_regs[PORT_COUNT] =
    { (void *)0x400ff000, (void *)0x400ff040 };

void gpio_configure(gpio_t gpio, gpio_dir_t dir)
{
    struct gpio_regs_t *regs;
    uint32_t bit;

    assert(gpio < PIN_MAX);

    pinmux_set_function(gpio, PIN_FUNC_GPIO);

    regs = gpio_regs[port_from_gpio(gpio)];
    bit = 1 << pin_from_gpio(gpio);

    if (dir == GPIO_DIR_INPUT)
        regs->direction &= ~bit;
    else
        regs->direction |= bit;
}

void gpio_set(gpio_t gpio)
{
    struct gpio_regs_t *regs;
    uint32_t bit;

    assert(gpio < PIN_MAX);

    regs = gpio_regs[port_from_gpio(gpio)];
    bit = 1 << pin_from_gpio(gpio);

    regs->set |= bit;
}

void gpio_clear(gpio_t gpio)
{
    struct gpio_regs_t *regs;
    uint32_t bit;

    assert(gpio < PIN_MAX);

    regs = gpio_regs[port_from_gpio(gpio)];
    bit = 1 << pin_from_gpio(gpio);

    regs->clear |= bit;
}

void gpio_toggle(gpio_t gpio)
{
    struct gpio_regs_t *regs;
    uint32_t bit;

    assert(gpio < PIN_MAX);

    regs = gpio_regs[port_from_gpio(gpio)];
    bit = 1 << pin_from_gpio(gpio);

    regs->toggle |= bit;
}

bool gpio_read(gpio_t gpio)
{
    struct gpio_regs_t *regs;
    uint32_t bit;

    assert(gpio < PIN_MAX);

    regs = gpio_regs[port_from_gpio(gpio)];
    bit = 1 << pin_from_gpio(gpio);

    return !!(regs->input & bit);
}

void gpio_write_port(port_t port, uint32_t mask, uint32_t value)
{
    struct gpio_regs_t *regs;
    uint32_t data;

    assert(port < PORT_COUNT);

    regs = gpio_regs[port];

    data = regs->output;
    data &= ~mask;
    data |= (value & mask);
    regs->output = data;
}

uint32_t gpio_read_port(port_t port)
{
    assert(port < PORT_COUNT);

    return gpio_regs[port]->input;
}
