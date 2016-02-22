#ifndef __TPM_H
#define __TPM_H

#include <stdint.h>

typedef uint8_t tpm_idx_t;
enum {
    TPM_0,
    TPM_1,

    TPM_COUNT
};

void tpm_init(tpm_idx_t idx, uint32_t hz, isr_t handler);
void tpm_enable(tpm_idx_t idx);
void tpm_disable(tpm_idx_t idx);

#endif
