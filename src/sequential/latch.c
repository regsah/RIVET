#include "latch.h"

sr_latch_t sr_latch_init(bit_t q)
{
    return (sr_latch_t){
        .q = q,
        .q_bar = not_gate(q)
    };
}

sr_latch_t sr_latch_step(sr_latch_t previous, bit_t set, bit_t reset)
{
    return (sr_latch_t){
        .q = nor_gate(reset, previous.q_bar),
        .q_bar = nor_gate(set, previous.q)
    };
}

sr_latch_t d_latch_step(sr_latch_t previous, bit_t data, bit_t enable)
{
    return sr_latch_step(
        previous, 
        and_gate(data, enable), 
        and_gate(not_gate(data), enable)
    );
}
