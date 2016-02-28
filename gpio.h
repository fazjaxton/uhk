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

#ifndef __GPIO_H
#define __GPIO_H

#include <pinmux.h>
#include <stdbool.h>
#include <stdint.h>

typedef uint8_t gpio_dir_t;
enum {
    GPIO_DIR_INPUT,
    GPIO_DIR_OUTPUT,
};

void gpio_configure(gpio_t gpio, gpio_dir_t dir);
void gpio_set(gpio_t gpio);
void gpio_clear(gpio_t gpio);
void gpio_toggle(gpio_t gpio);
bool gpio_read(gpio_t gpio);
void gpio_write_port(port_t port, uint32_t mask, uint32_t value);
uint32_t gpio_read_port(port_t port);

#endif
