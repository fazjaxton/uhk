#ifndef __CONFIG_H
#define __CONFIG_H

/* Time allowed to completely debounce one key */
#define MATRIX_DEBOUNCE_TIME_US         1000

/* How many samples a switch must remain in the same state to be debounced.  A
 * value of 2 means that after observing a switch state change, the switch must
 * remain in the same state for two more samples to be reported as changed. */
#define MATRIX_DEBOUNCE_SAMPLES         2

/* Which TPM module to use for sampling the key matrix */
#define MATRIX_TPM_IDX                  TPM_0

#endif
