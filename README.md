# RIVET

**RISC-V Interpreter and Virtual Execution Target**

RIVET is a from-scratch virtual execution target written in C. It starts with
small logic components, builds up through combinational and sequential state,
and aims to grow into a minimal RV32I RISC-V instruction decoder and execution
model.

The project favors clarity over completeness. The goal is to make the path from bits to instructions readable, performance is not a priority.

## Status

RIVET is under active development.

Currently implemented:

- Basic bit types and fixed-width bit containers
- Logic gates built from lower-level primitives
- Combinational components, including muxes, demuxes, decoders, adders, and
  equality checks
- Sequential latch primitives
- Flip-flops, 32-bit registers, and a register file with mux-based reads and decoded writes
- Unit tests for core components
- Makefile-based build and test workflow

Planned:

- Wider word-level components
- Memory model
- RV32I instruction representation
- RV32I instruction decoding
- Fetch-decode-execute loop
- Assembly-level test programs
- Simple tracing or debugging utilities

## Motivation

RIVET is a systems programming project for exploring how computation is
represented below the usual software abstraction layer: logic, state,
instruction encoding, decoding, and execution.

The long-term goal is to construct a small, readable RISC-V execution target
from first principles.

## Build

On Unix-like systems:

```bash
make
```

On Windows with MinGW:

```bash
mingw32-make
```

## Run Tests

On Unix-like systems:

```bash
make test
```

On Windows with MinGW:

```bash
mingw32-make test
```

## Project Structure

```text
include/    Public headers
src/        Implementation files
tests/      Unit tests
Makefile    Build and test commands
```

## Roadmap

See the [RV32I instruction checklist](docs/rv32i.md) for encodings, behavior,
required circuits, implementation status, and planned tests.

- [x] Logic components
- [x] Combinational components
- [x] Sequential latch primitives
- [x] Unit test structure
- [x] Word-level data structures
- [x] Register file
- [ ] Memory model
- [ ] RV32I instruction representation
- [ ] RV32I decoder
- [ ] Fetch-decode-execute loop
- [ ] Assembly program execution

The register file contains 32 flip-flop-based 32-bit registers. Read addresses
use five selector bits with `s0` as the least-significant bit; call
`register_file_read` twice on the same state for two independent reads.
`register_file_step` returns the state after one write step. Reads of the old
state see the old value, and reads of the returned state see the updated value.
Register `x0` always reads as zero and ignores writes. RAM will use an array
as an intentional abstraction rather than a gate-level implementation.

## Scope

Initial target:

- RV32I
- User mode only
- Small, readable execution model

Out of scope for the first version:

- Privileged mode
- Interrupts
- Devices
- Booting an operating system
- Pipelining or microarchitectural optimization

## License

RIVET is licensed under the GNU Affero General Public License v3.0 or later.

See [LICENSE](LICENSE) for details.
