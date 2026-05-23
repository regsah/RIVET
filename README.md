# groundup-cpu

`groundup-cpu` is a bottom up computer systems project where the aim is to create a small machine from the first principles.


## Goals
- Build logical components in C.
- Implement a small and readable model.
- Extend the model into a simple RV32I RISC-V implementation.
- Keep the codebase understandable enough to support future expansion / writing projects


## Stages
1. Gates and bit-level operations
2. Combinational components
3. Sequential components and state
4. Tiny machine core
5. RISC-V decode and execution
6. Assembly programs


## Scope
The initial target is:
- RV32I
- user mode only
- Clarity over completeness

Out of scope for the first version:
- privileged mode
- interrupts
- devices
- booting an operating system
- pipelining or microarchitectural optimizations


## License
TBD
