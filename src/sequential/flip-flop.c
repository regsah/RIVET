#include "flip-flop.h"

d_flip_flop_t d_flip_flop_init(bit_t q)
{
    return (d_flip_flop_t){
        .q = q,
        .q_bar = not_gate(q)
    };
}

d_flip_flop_t d_flip_flop_step(d_flip_flop_t previous, bit_t data)
{
    d_latch_t settling = d_latch_step(
        (d_latch_t){
            .q = previous.q,
            .q_bar = previous.q_bar
        },
        data,
        1
    );
    d_latch_t next = d_latch_step(settling, data, 1);

    return (d_flip_flop_t){
        .q = next.q,
        .q_bar = next.q_bar
    };
}
