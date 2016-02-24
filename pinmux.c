#include <assert.h>
#include <pinmux.h>
#include <stdint.h>

#define PORT_PCR_MUX                    8

struct pinmux_regs_t {
    volatile uint32_t control[32];
};

static struct pinmux_regs_t *pinmux_regs[PORT_COUNT] = 
    { (void *)0x40049000, (void *)0x4004A000 };

static inline port_t port_from_gpio(gpio_t gpio)
{
    return gpio >> 5;
}

static inline port_t pin_from_gpio(gpio_t gpio)
{
    return gpio & 0x1f;
}

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
