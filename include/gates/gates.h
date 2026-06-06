#ifndef GATES_H
#define GATES_H

#include "bit.h"

bit_t nand_gate(bit_t i0, bit_t i1);

bit_t not_gate(bit_t i0);
bit_t and_gate(bit_t i0, bit_t i1);
bit_t or_gate(bit_t i0, bit_t i1);

bit_t xor_gate(bit_t i0, bit_t i1);

bit_t nor_gate(bit_t i0, bit_t i1);
bit_t xnor_gate(bit_t i0, bit_t i1);


/********** Multi-input gates **********/
// AND
bit_t and_gate3(bit_t i0, bit_t i1, bit_t i2);
bit_t and_gate4(bit_t i0, bit_t i1, bit_t i2, bit_t i3);

#endif // GATES_H