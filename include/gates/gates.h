#ifndef GATES_H
#define GATES_H

#include "bit.h"

bit_t nand_gate(bit_t a, bit_t b);

bit_t not_gate(bit_t a);
bit_t and_gate(bit_t a, bit_t b);
bit_t or_gate(bit_t a, bit_t b);

bit_t xor_gate(bit_t a, bit_t b);

bit_t nor_gate(bit_t a, bit_t b);
bit_t xnor_gate(bit_t a, bit_t b);

#endif // GATES_H