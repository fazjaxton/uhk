#include <config.h>
#include <gpio.h>
#include <matrix.h>
#include <pinmux.h>
#include <stdint.h>
#include <tpm.h>

/* Update these with correct ports once HW design is finalized */
#define COL_PORT                PORT_A
#define ROW_PORT                PORT_A

#define COL_COUNT               7
#define ROW_COUNT               5

/* Frequency of the ISR that reads a single column */
#define COL_HZ                  ((1000000 * COL_COUNT * \
                                    MATRIX_DEBOUNCE_SAMPLES) \
                                    / MATRIX_DEBOUNCE_TIME_US)

/* A bitmask of the debounced state of each key in each column */
static uint8_t rows_state[COL_COUNT];
/* A bitmask of the most recently sampled state of each key in each column */
static uint8_t rows_last[COL_COUNT];
/* The number of samples */
static uint8_t db_count[COL_COUNT][ROW_COUNT];
/* A mask of the gpios used for driving the column lines */
static uint32_t col_mask;

/* Update these with correct pins once HW design finalized */
static const uint8_t row_pins[ROW_COUNT] = {
    0, 1, 2, 3, 4
};
static const uint8_t col_pins[COL_COUNT] = {
    0, 1, 2, 3, 4, 5, 6
};

/* Read gpio port bits and decode into a bitfield of row statuses */
static uint8_t read_rows(void)
{
    uint32_t bits;
    uint8_t i;
    uint8_t res;

    res = 0;

    bits = gpio_read_port(ROW_PORT);
    for (i = 0; i < ROW_COUNT; i++) {
        if (bits & (1 << row_pins[i])) {
            res |= 1 << i;
        }
    }

    return res;
}

/* Drive the correct gpio signals to read the given column */
static void drive_column(uint8_t col)
{
    gpio_write_port(COL_PORT, col_mask, 1 << col_pins[col]);
}

/* Report a change in key state */
static void update_key_state(uint8_t col, uint8_t row, bool state)
{
    /* Report key state here */
}

/* Read the row lines and update switch state for a given active column */
static void matrix_read(uint8_t col)
{
    uint8_t changed;
    uint8_t diff;
    uint8_t debouncing;
    uint8_t bit;
    uint8_t rows;
    uint8_t *db;
    uint8_t i;
    
    rows = read_rows();

    /* Whether the reading has changed from the last time */
    changed = rows ^ rows_last[col];
    /* Whether the reading is different from the current debounced state */
    diff = rows ^ rows_state[col];

    /* Debouncing for this switch continues if it is a change from the current
     * state and has not changed since the last sample */
    debouncing = diff & ~(changed);

    /* Update debouncing state for each row in this column */
    for (i = 0; i < ROW_COUNT; i++) {
        bit = 1 << i;
        db = &db_count[col][i];

        if (debouncing & bit) {
            *db += 1;
            if (*db >= MATRIX_DEBOUNCE_SAMPLES) {
                /* Switch has been debounced; change state */
                rows_state[col] ^= bit;
                update_key_state(col, i, !!(rows_state[col] & bit));
                *db = 0;
            }
        } else {
            *db = 0;
        }
    }

    rows_last[col] = rows;
}

static void matrix_isr(void)
{
    static uint8_t col_idx;

    /* Handle any ISR cleanup in the driver */
    tpm_isr_first(MATRIX_TPM_IDX);

    /* Sample the row lines for this column */
    matrix_read(col_idx);

    /* Drive the column lines for the next sample */
    col_idx++;
    if (col_idx >= COL_COUNT)
        col_idx = 0;
    drive_column(col_idx);
}

void matrix_init(void)
{
    uint8_t i;

    /* Configure pins as gpios */
    for (i = 0; i < COL_COUNT; i++) {
        gpio_configure(GPIO_PIN(COL_PORT, col_pins[i]), GPIO_DIR_OUTPUT);
        col_mask |= (1 << col_pins[i]);
    }
    for (i = 0; i < ROW_COUNT; i++) {
        gpio_configure(GPIO_PIN(ROW_PORT, row_pins[i]), GPIO_DIR_INPUT);
    }

    /* Drive lines for first read */
    drive_column(0);

    /* Enable periodic interrupt to read key matrix */
    tpm_init(MATRIX_TPM_IDX, COL_HZ, matrix_isr);
    tpm_enable(MATRIX_TPM_IDX);
}
