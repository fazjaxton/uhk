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
