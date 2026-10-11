# RV32I implementation checklist

RIVET targets RV32I, the 32-bit base integer instruction set. This document
tracks its 40 base instructions and the circuits needed to execute them.
It is a build plan and a quick reference; the specification remains authoritative.

References:

- [RV32I, version 2.1, in the 20260120 ratified ISA manual](https://docs.riscv.org/reference/isa/v20260120/unpriv/rv32.html)
- [Official instruction formats and encoding listings](https://docs.riscv.org/reference/isa/v20260120/unpriv/rv-32-64g.html)
- Official machine-readable encodings: [rv_i](https://github.com/riscv/riscv-opcodes/blob/master/extensions/rv_i) and [rv32_i](https://github.com/riscv/riscv-opcodes/blob/master/extensions/rv32_i)

## Project approach

Registers use the existing flip-flop and latch primitives. Combinational
computation and control selection should compose NAND-derived components.
Fixed loops, containers, constants, and bit-to-bit connections describe repeated
wiring. Native C arithmetic, comparisons, shifts, or instruction dispatch should
not replace the circuits being modeled. The formulas below describe behavior,
not the C implementation to use.

State is explicit: a step receives the previous state and returns the next one.
The simulator retains that result between steps. A register step represents a
clock event; the current model does not simulate a clock waveform.

RAM will be an array-backed abstraction. Its storage does not need a gate-level
implementation. Address generation and CPU-side data selection still belong to
the simulated datapath. Tests may use ordinary C operations as independent
reference calculations.

## Current status

| Component | Status | Existing code or next work |
| --- | --- | --- |
| NAND-derived gates and selection | Implemented, unit tested | `src/gates/`, muxes, demuxes, decoders |
| 32-bit addition | Implemented, unit tested | `adder32` in `src/combinational/adder.c` |
| 32-bit equality and zero detection | Implemented, unit tested | `eq32`, `is_zero32` |
| Registers and register file | Implemented, unit tested | `src/sequential/register.c`, `register-file.c` |
| Shared add/subtract circuit | Implemented, unit tested | `add_sub32` in `src/combinational/adder.c` |
| Word bitwise operations | Implemented, unit tested | `bitwise_and32`, `bitwise_or32`, `bitwise_xor32` in `src/bitwise/` |
| Variable shifts | Implemented, unit tested | `bitwise_sll32`, `bitwise_srl32`, `bitwise_sra32` in `src/bitwise/shifts.c` |
| Signed/unsigned less-than | Implemented, unit tested | `lt32_signed`, `lt32_unsigned` in `src/combinational/comparators.c` |
| ALU result selection | Implemented, unit tested | `alu32` in `src/combinational/alu.c` |
| Instruction field wiring | Next milestone | Opcode, register-address, and function-field connections |
| Immediate generation | Next milestone | I/S/B/U/J reconstruction and shift-amount wiring |
| Instruction decode and control | Pending | Recognize supported encodings, validate fields, generate control signals |
| Operand and writeback selection | Pending | Connect register, immediate, PC, ALU, and later memory paths |
| Program counter and next-PC selection | Pending | Register, adders, muxes, alignment checks |
| RAM and load/store interface | Pending | Array storage, access widths, extension, faults |
| CPU execution and environment events | Pending | State composition and execution boundary |

The project has a tested computation/storage foundation, but no complete
instruction execution path. Do not measure completion by counting component
rows: instruction decoding, state integration, memory, faults, and program
tests account for substantial work beyond the ALU. All 40 instruction rows
remain pending until their instruction-level milestones are met.

## Next milestone: fields and immediates

Build a combinational component that receives an instruction word and exposes
its opcode, register-address fields, function fields, immediate candidates,
and shift amount as bits/bit containers. Field extraction is fixed wiring;
immediate construction uses fixed connections, constants, and sign replication.
Keep the existing least-significant-bit-first convention.

This component supplies field values and candidate operands. Recognizing an
instruction, deciding which fields are meaningful, checking its encoding, and
selecting the appropriate immediate belong to the subsequent decoder/control
milestone. An exposed `rs2` bit slice, for example, is not a register source
for every instruction format.

Acceptance checks:

- Walk individual instruction bits and verify each field's width and ordering.
- Check I/S/B/U/J candidates against independently encoded examples and boundary
  values, including zero, negative immediates, and the most positive offsets.
- Verify sign replication, U-immediate low zeros, and B/J offset low zeros.
- Verify branch/jump bit rearrangement without applying a second scaling shift.
- Expose the five shift-amount bits independently of operation selection.
- Keep tests at the field/immediate level; full instruction execution is a
  later integration test.

The [formats and immediates](#formats-and-immediates) table below defines the
connections. After this checkpoint, add recognition/control circuits and tests
for supported and neighboring unsupported encodings. Only then connect the
register file, ALU, PC, and writeback into instruction execution.

## Existing component interfaces

`and_gate32` reduces 32 inputs to one bit. A word-wide bitwise AND instead
uses 32 two-input AND gates, producing 32 output bits. The word operations
have their own header, `include/bitwise/bitwise.h`, and use the `bitwise_`
prefix to distinguish them from multi-input gates. Each takes two words and
returns one word, applying the corresponding existing gate to each bit pair.

The shifters in the same header take one word and five control bits, with
`s0` selecting a shift of 1 and `s4` selecting 16. Five mux stages combine
those fixed distances into any shift from 0 through 31. `bitwise_sll32` and
`bitwise_srl32` fill with zero; `bitwise_sra32` fills with the original input's
bit 31. The implementation shifts data through fixed connections and muxes,
without native C shift operators on the input word.

`add_sub32(A, B, subtract)` uses XOR gates to conditionally invert B and
passes `subtract` as the carry-in to `adder32`. Control 0 computes A+B;
control 1 computes A-B. The low 32 result bits are returned in `.sum` for
both operations. `.carry` is the raw adder carry-out: in subtraction mode,
1 means no unsigned borrow and 0 means a borrow occurred. It is not a signed
overflow flag or architectural CPU state.

`lt32_unsigned(A, B)` subtracts B from A and inverts the carry-out to detect
an unsigned borrow. `lt32_signed(A, B)` uses XOR to detect differing sign bits:
a mux selects A's sign when they differ, or the difference's sign when they
match. This avoids interpreting an overflowed difference as the signed ordering.
Both return a single bit. Instruction-level set-less-than results will place
that bit in bit 0 of an otherwise zero word.

The ALU interface is declared in `include/combinational/alu.h`:
`alu32(A, B, op0, op1, op2, op3)` returns a single word without changing state.
The control word below is written most-significant bit first, `op3 op2 op1 op0`.

| Control | Operation | Result |
| --- | --- | --- |
| 0000 | ADD | A+B, low 32 bits |
| 0001 | SLL | A shifted left by B[4:0], zero fill |
| 0010 | SLT | Signed A<B, represented as the word 0 or 1 |
| 0011 | SLTU | Unsigned A<B, represented as the word 0 or 1 |
| 0100 | XOR | Bitwise A XOR B |
| 0101 | SRL | A shifted right by B[4:0], zero fill |
| 0110 | OR | Bitwise A OR B |
| 0111 | AND | Bitwise A AND B |
| 1000 | SUB | A-B, low 32 bits |
| 1101 | SRA | A shifted right by B[4:0], sign fill |

All other control words return zero. This is an internal ALU convention,
not illegal-instruction handling. The ALU uses the existing circuits and
selects each output bit through two 8-input muxes followed by a 2-input mux.
Only bit 0 of each comparison result is connected to the comparator output;
the remaining bits are tied low. The adder's carry-out is not exposed as an
architectural flag.

These control codes are our implementation choice, not complete instruction
encodings. The future decoder must validate the opcode and required function
fields before generating them. In particular, instruction bit 30 must not be
wired indiscriminately to `op3`: a negative ADDI immediate can set that bit
without requesting subtraction. Loads, stores, and AUIPC can use ADD after
operand selection; LUI can use a separate writeback path. Branch conditions
can use the existing equality and less-than circuits outside the result mux.

An existing circuit does not mean an instruction is implemented. Every
instruction below is currently **Pending**: there is no instruction decoder or
CPU execution path yet. The test column lists tests to add, not existing tests.
Change a row to **Decoded**, **Executed**, then **Tested** as those milestones
are completed. Component tests alone do not qualify a row as Tested.

## Notation and shared rules

- `A = x[rs1]`, `B = x[rs2]`, and `D = x[rd]`. Sources come from the previous
  state, including when `rd` equals a source register.
- `pc` is the address of the current instruction. Ordinary successful execution
  advances to `pc + 4`; control transfers override it. Faults/events need a
  separate outcome and must not be treated as ordinary successful execution.
- Results and address arithmetic keep their low 32 bits. Arithmetic overflow
  does not itself raise an exception or create an architectural carry flag.
- `s(v)` interprets a word as signed two's complement; `u(v)` as unsigned.
  `bool32(condition)` is the word 1 or 0, not an all-ones mask.
- `sextN(v)` sign-extends an N-bit value to 32 bits; `zextN(v)` zero-extends it.
  `loN(v)` selects the low N bits. `SHL`/`SHR` insert zeros; `SAR` repeats bit 31.
- Writes to `x0` are discarded. Other effects still happen: a load into `x0`
  still accesses memory and can fault; a jump with `rd=x0` still jumps.

The shared instruction rules and behavior tables follow the
[RV32I specification](https://docs.riscv.org/reference/isa/v20260120/unpriv/rv32.html).

## Formats and immediates

Instruction bit 0 is the least-significant bit, matching `word_t.bits[0]`.
The opcode occupies `inst[6:0]`. Where present, `rd=inst[11:7]`,
`funct3=inst[14:12]`, `rs1=inst[19:15]`, `rs2=inst[24:20]`, and
`funct7=inst[31:25]`. Fields absent from a format must not be interpreted as
register operands.

In this table, `concat(...)` joins fields from most to least significant.
Immediate reconstruction is fixed wiring and sign-bit replication.

| Format | Used for | Reconstructed operand |
| --- | --- | --- |
| R | Two register operands | No immediate |
| I | Arithmetic, loads, JALR | `I = sext12(inst[31:20])` |
| I-shift | Immediate shifts | `shamt = inst[24:20]`; upper bits select/validate the operation |
| S | Stores | `S = sext12(concat(inst[31:25], inst[11:7]))` |
| B | Conditional branches | `Boff = sext13(concat(inst[31], inst[7], inst[30:25], inst[11:8], 0))` |
| U | Upper immediates | `U = concat(inst[31:12], twelve zero bits)` |
| J | JAL | `Joff = sext21(concat(inst[31], inst[19:12], inst[20], inst[30:21], 0))` |

`Boff` and `Joff` already include their low zero bit; do not shift them again.
System instructions have their own fixed fields and do not use a general
arithmetic immediate.

Encodings below are `format; opcode / funct3 / funct7`, with hexadecimal
opcodes and binary function fields. `-` means that field does not select the
operation in that row. For ECALL/EBREAK, the complete 32-bit encoding is given.
Use the [official encoding listings](https://docs.riscv.org/reference/isa/v20260120/unpriv/rv-32-64g.html)
and [machine-readable definitions](https://github.com/riscv/riscv-opcodes/blob/master/extensions/rv_i)
when building the decoder; matching only the opcode or bit 30 is insufficient.

## Register arithmetic, logic, and shifts (10)

All rows read `A` and `B`, write `D`, and otherwise advance the PC normally.
The register shift amount is `k = B[4:0]`; higher bits of B are ignored.

| Instruction | Encoding | Effect | Required circuits | Test focus | Status |
| --- | --- | --- | --- | --- | --- |
| ADD | R; 0x33 / 000 / 0000000 | `D = A + B` | Adder | Carry across bytes; wraparound | Pending |
| SUB | R; 0x33 / 000 / 0100000 | `D = A - B` | Add/subtract | Borrow; equal operands; wraparound | Pending |
| SLL | R; 0x33 / 001 / 0000000 | `D = SHL(A, k)` | Left shifter | 0/1/31; ignore B[31:5] | Pending |
| SLT | R; 0x33 / 010 / 0000000 | `D = bool32(s(A) < s(B))` | Signed comparator | Negative/positive; signed extrema; equality | Pending |
| SLTU | R; 0x33 / 011 / 0000000 | `D = bool32(u(A) < u(B))` | Unsigned comparator | High bit set; zero; equality | Pending |
| XOR | R; 0x33 / 100 / 0000000 | `D = A XOR B` | Word XOR | Equal/complementary patterns; each bit | Pending |
| SRL | R; 0x33 / 101 / 0000000 | `D = SHR(A, k)` | Logical right shifter | High bit set; zero fill; 0/31 | Pending |
| SRA | R; 0x33 / 101 / 0100000 | `D = SAR(A, k)` | Arithmetic right shifter | Both signs; sign fill; 0/31 | Pending |
| OR | R; 0x33 / 110 / 0000000 | `D = A OR B` | Word OR | Zero/all-ones; complementary patterns | Pending |
| AND | R; 0x33 / 111 / 0000000 | `D = A AND B` | Word AND | Zero/all-ones; disjoint patterns | Pending |

## Immediate arithmetic, logic, and shifts (9)

These read `A` and write `D`. In non-shift rows, `I` is sign-extended even
for unsigned comparisons and bitwise operations. Immediate shifts use `shamt`.

| Instruction | Encoding | Effect | Required circuits | Test focus | Status |
| --- | --- | --- | --- | --- | --- |
| ADDI | I; 0x13 / 000 / - | `D = A + I` | Immediate wiring, adder | -2048/2047; wraparound; zero | Pending |
| SLTI | I; 0x13 / 010 / - | `D = bool32(s(A) < s(I))` | Immediate wiring, signed comparator | Negative immediate; equality | Pending |
| SLTIU | I; 0x13 / 011 / - | `D = bool32(u(A) < u(I))` | Immediate wiring, unsigned comparator | Sign-extend -1 before unsigned comparison | Pending |
| XORI | I; 0x13 / 100 / - | `D = A XOR I` | Immediate wiring, word XOR | Immediate -1 inverts all bits | Pending |
| ORI | I; 0x13 / 110 / - | `D = A OR I` | Immediate wiring, word OR | Negative immediate sets upper bits | Pending |
| ANDI | I; 0x13 / 111 / - | `D = A AND I` | Immediate wiring, word AND | -1 preserves input; positive masks | Pending |
| SLLI | I-shift; 0x13 / 001 / 0000000 | `D = SHL(A, shamt)` | Left shifter | 0/1/31; reject unsupported upper fields | Pending |
| SRLI | I-shift; 0x13 / 101 / 0000000 | `D = SHR(A, shamt)` | Logical right shifter | Zero fill; distinguish SRAI | Pending |
| SRAI | I-shift; 0x13 / 101 / 0100000 | `D = SAR(A, shamt)` | Arithmetic right shifter | Sign fill; distinguish SRLI | Pending |

## Upper immediates (2)

Neither instruction reads a source register. Both write `D`.

| Instruction | Encoding | Effect | Required circuits | Test focus | Status |
| --- | --- | --- | --- | --- | --- |
| LUI | U; 0x37 / - / - | `D = U` | U wiring, writeback selection | Low 12 bits zero; high bit retained | Pending |
| AUIPC | U; 0x17 / - / - | `D = pc + U` | U wiring, adder, PC input selection | Current PC versus PC+4; wraparound | Pending |

## Conditional branches (6)

Branches read `A` and `B`, write no general-purpose register, and choose
`next_pc = pc + Boff` when the condition is true, otherwise `pc + 4`.
Each needs B-immediate wiring, target addition, PC selection, and alignment checks.

| Instruction | Encoding | Branch condition | Condition circuit | Test focus | Status |
| --- | --- | --- | --- | --- | --- |
| BEQ | B; 0x63 / 000 / - | `A == B` | Equality | Taken/not taken; both offset signs | Pending |
| BNE | B; 0x63 / 001 / - | `A != B` | Equality, NOT | Taken/not taken; equality | Pending |
| BLT | B; 0x63 / 100 / - | `s(A) < s(B)` | Signed comparator | Opposite signs; equal operands | Pending |
| BGE | B; 0x63 / 101 / - | `s(A) >= s(B)` | Signed comparator, NOT | Equality must take branch | Pending |
| BLTU | B; 0x63 / 110 / - | `u(A) < u(B)` | Unsigned comparator | High-bit values differ from BLT | Pending |
| BGEU | B; 0x63 / 111 / - | `u(A) >= u(B)` | Unsigned comparator, NOT | Equality; high-bit values | Pending |

For base RV32I, a taken target must be four-byte aligned even though branch
offsets have two-byte granularity. A non-taken branch must not fault merely
because its unused target is misaligned.

## Jumps (2)

Both write the link `D = pc + 4` on successful execution. Read any source
before writing the destination, including JALR with `rd=rs1`.

| Instruction | Encoding | Next PC | Required circuits | Test focus | Status |
| --- | --- | --- | --- | --- | --- |
| JAL | J; 0x6F / - / - | `pc + Joff` | J wiring, adders, PC/link selection | Positive/negative offset; link; rd=x0 | Pending |
| JALR | I; 0x67 / 000 / - | `clear_bit0(A + I)` | I wiring, adders, low-bit tie-off, PC/link selection | Odd target clears bit 0; rd=rs1; negative offset | Pending |

JALR uses a byte offset, not a scaled branch offset. Clearing bit 0 does not
clear bit 1: both jumps still require four-byte target alignment in base RV32I.

## Loads (5)

Each load reads `A`, forms `address = A + I`, reads memory, and writes `D`.
It needs an adder, the RAM interface, width selection, and writeback selection.
`M8`/`M16`/`M32` below read that many bits at the calculated byte address.

| Instruction | Encoding | Loaded value | Additional circuit | Test focus | Status |
| --- | --- | --- | --- | --- | --- |
| LB | I; 0x03 / 000 / - | `D = sext8(M8)` | Sign extension | 0x7F/0x80/0xFF; negative offset | Pending |
| LH | I; 0x03 / 001 / - | `D = sext16(M16)` | Sign extension | 0x7FFF/0x8000; byte assembly | Pending |
| LW | I; 0x03 / 010 / - | `D = M32` | Word assembly | All bytes distinct; high bit retained | Pending |
| LBU | I; 0x03 / 100 / - | `D = zext8(M8)` | Zero extension | 0x80/0xFF produce positive words | Pending |
| LHU | I; 0x03 / 101 / - | `D = zext16(M16)` | Zero extension | 0x8000/0xFFFF; upper bits zero | Pending |

Also test loads into `x0`, memory boundaries, access faults, and the chosen
alignment/endianness policy. Discarding a destination must not skip the access.

## Stores (3)

Each store reads `A` and `B`, forms `address = A + S`, and updates memory.
Stores have no `rd` and must not write a general-purpose register. They need
an adder, byte-lane wiring/write enables, and the RAM interface.

| Instruction | Encoding | Stored value | Test focus | Status |
| --- | --- | --- | --- | --- |
| SB | S; 0x23 / 000 / - | `M8 = lo8(B)` | Discard upper bits; preserve neighboring bytes | Pending |
| SH | S; 0x23 / 001 / - | `M16 = lo16(B)` | Byte order; preserve neighboring bytes | Pending |
| SW | S; 0x23 / 010 / - | `M32 = B` | Four distinct bytes; register state unchanged | Pending |

Also test negative offsets, address boundaries, and faults before committing
memory changes. Data-alignment behavior depends on the execution environment.

## Ordering and environment (3)

| Instruction | Encoding | Architectural purpose | RIVET work / planned tests | Status |
| --- | --- | --- | --- | --- |
| FENCE | I; 0x0F / 000 / - | Order selected memory and I/O accesses | Define ordering model; decode without register or RAM writes | Pending |
| ECALL | I; full word 0x00000073 | Request an execution-environment trap | Define host-visible event; distinguish EBREAK; preserve faulting PC | Pending |
| EBREAK | I; full word 0x00100073 | Request a breakpoint trap | Define debugger/stop event; distinguish ECALL; preserve faulting PC | Pending |

For FENCE, `fm=inst[31:28]`, `pred=inst[27:24]`, and `succ=inst[23:20]`.
Base implementations ignore its `rs1` and `rd` fields; they are not operands.
The predecessor/successor bits name I/O input, I/O output, memory reads, and
memory writes. Reserved FENCE configurations must retain the base FENCE
behavior; FENCE.TSO can conservatively use ordinary FENCE ordering.

A single CPU with immediate, ordered array accesses and no devices could
satisfy FENCE without extra state changes. That is a proposed environment
choice, not an implemented shortcut. ECALL and EBREAK must produce explicit
events; a Linux syscall interface or an exit convention is not supplied by
RV32I itself.

## Scope and decisions still open

| Area | Decision |
| --- | --- |
| CPU scope | RV32I; user-mode execution; no privileged architecture, interrupts, devices, or OS boot |
| RAM implementation | Array-backed storage, deliberately outside the NAND circuit model |
| Memory layout | Size, valid addresses, loading programs, and read/write permissions still to define |
| Byte order | Still to choose; little-endian is the proposed initial configuration |
| Misaligned data access | Still to choose: support it or report an explicit fault; naturally aligned accesses remain required |
| Fault/event reporting | Still to define as a simulator interface; privileged trap CSRs/handlers are outside initial scope |
| FENCE | Base instruction remains a target; minimal ordered-memory behavior proposed above |
| ECALL/EBREAK | Base instructions remain targets; host handling and any service ABI still to define |
| Other extensions | M, A, floating point, compressed instructions, Zicsr (CSR instructions), and Zifencei (FENCE.I) deferred |

Assembler aliases do not add instruction circuits: for example, `NOP` encodes
as `ADDI x0,x0,0`, `MV rd,rs` as `ADDI rd,rs,0`, and `RET` as
`JALR x0,x1,0`. Base HINT encodings may execute through their ordinary base
instruction paths. PAUSE/FENCE.TSO use FENCE encodings and do not add separate
rows to this 40-instruction checklist. This does not imply support for their
associated extensions. Do not classify every instruction with `rd=x0` as a NOP.

Unsupported extensions and invalid encodings need a defined decode outcome.
They must not accidentally select a base operation through incomplete function
field checks. The exact unsupported/reserved-encoding policy is still open.

## Build and verification order

- [x] Build and test add/subtract, bitwise operations, shifts, and comparisons.
- [x] Assemble and test the ALU computation and result-selection network.
- [ ] Wire instruction fields and reconstruct all immediate formats; verify
  each connection and sign boundary independently.
- [ ] Build instruction recognition and control circuits; check full required
  encoding fields and define unsupported-encoding outcomes.
- [ ] Add operand/writeback selection and the PC; connect decode, register reads,
  ALU, and register updates. Execute arithmetic instructions first.
- [ ] Add branch/jump target selection and alignment outcomes.
- [ ] Define the RAM/environment decisions, then add loads, stores, and events.
- [ ] Run encoded instruction programs and check complete state transitions.

For each instruction, end-to-end tests should begin with an encoded 32-bit
instruction and check the resulting PC, destination, unaffected registers,
memory, and event outcome. Include `rd=x0`, aliased source/destination
registers, boundary values, and neighboring unsupported encodings where
applicable. Test failed operations for unintended partial state updates.

Track component tests separately from instruction tests. Ordinary C arithmetic
in tests is useful as an independent oracle; deriving expected results from
the same simulated circuit would hide shared mistakes.
