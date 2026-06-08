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
- Unit tests for core components
- Makefile-based build and test workflow

Planned:

- Wider word-level components
- Register and memory models
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

- [x] Logic components
- [x] Combinational components
- [x] Sequential latch primitives
- [x] Unit test structure
- [ ] Word-level data structures
- [ ] Register file
- [ ] Memory model
- [ ] RV32I instruction representation
- [ ] RV32I decoder
- [ ] Fetch-decode-execute loop
- [ ] Assembly program execution

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
