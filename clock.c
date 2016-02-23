#include <assert.h>
#include <clock.h>
#include <stdint.h>

struct sim_regs_t {
    volatile uint32_t options1;
    volatile uint32_t _1[1024];
    volatile uint32_t options2;
    volatile uint32_t _2;
    volatile uint32_t options4;
    volatile uint32_t options5;
    volatile uint32_t _3;
    volatile uint32_t options7;
    volatile uint32_t _4[2];
    volatile uint32_t system_id;
    volatile uint32_t _5[3];
    volatile uint32_t clk_gate[3];
    volatile uint32_t _6;
    volatile uint32_t sys_clk_div;
    volatile uint32_t _7;
    volatile uint32_t flash_cfg_1;
    volatile uint32_t flash_cfg_2;
};

static struct sim_regs_t * const sim_regs = (void *)0x40047000;

void clock_gate_enable(clk_gate_t gate)
{
    uint8_t reg;
    uint8_t bit;

    assert(gate < CLK_GATE_MAX);

    reg = gate >> 5;
    bit = gate & 0x1f;

    sim_regs->clk_gate[reg] |= (1 << bit);
}

void clock_gate_disable(clk_gate_t gate)
{
    uint8_t reg;
    uint8_t bit;

    assert(gate < CLK_GATE_MAX);

    reg = gate >> 5;
    bit = gate & 0x1f;

    sim_regs->clk_gate[reg] &= ~(1 << bit);
}
