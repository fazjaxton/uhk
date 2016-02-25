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
