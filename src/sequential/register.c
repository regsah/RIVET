#include "register.h"

#include "combinational.h"

register1_t register1_init(bit_t q)
{
    return (register1_t){
        .q = q,
        .q_bar = not_gate(q)
    };
}

register1_t register1_step(register1_t previous, bit_t data, bit_t load)
{
    d_flip_flop_t next = d_flip_flop_step(
        (d_flip_flop_t){
            .q = previous.q,
            .q_bar = previous.q_bar
        },
        mux2_1(previous.q, data, load)
    );

    return (register1_t){
        .q = next.q,
        .q_bar = next.q_bar
    };
}


register32_t register32_init(word_t q)
{
    register32_t result;
    for (int bit = 0; bit < 32; bit++) {
        result.bits[bit] = register1_init(q.bits[bit]);
    }
    return result;
}

register32_t register32_step(register32_t previous, word_t data, bit_t load)
{
    register32_t result;
    for (int bit = 0; bit < 32; bit++) {
        result.bits[bit] = register1_step(previous.bits[bit], data.bits[bit], load);
    }
    return result;
}