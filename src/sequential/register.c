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
