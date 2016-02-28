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

#ifndef __PINMUX_H
#define __PINMUX_H

#include <stdint.h>

#define GPIO_PIN(port,pin)              (((port) << 5) | (pin))
#define PIN_MAX                         GPIO_PIN(PORT_B, 13)

typedef uint8_t port_t;
enum {
    PORT_A,
    PORT_B,

    PORT_COUNT
};

typedef uint8_t gpio_t;

typedef uint8_t pin_func_t;
enum {
    PIN_FUNC_ANALOG = 0,
    PIN_FUNC_GPIO = 1,
};

static inline port_t port_from_gpio(gpio_t gpio)
{
    return gpio >> 5;
}

static inline port_t pin_from_gpio(gpio_t gpio)
{
    return gpio & 0x1f;
}

void pinmux_set_function(gpio_t gpio, pin_func_t func);

#endif
