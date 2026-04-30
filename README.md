# GASM - High-Level Assembler (HLA)

`gasm` is an experimental high-level assembler written in C++.
The project focuses on a front-end pipeline (lexer → parser → IR) and a small command-line interface for selecting inputs and output format.

## Status

This project is in an early prototype stage.

Current state:
- **Three-phase Pipeline**:
  - **Phase 1 (Lexer)** → `vector<TokenString>` (raw lexemes with line info)
  - **Phase 2 (Parser)** → `vector<Token>` (classified tokens)
  - **Phase 3 (IR)** → `vector<IRNode>` (IR-ready stream with symbol resolution)
- **Symbol Management**: `SymbolTable` tracks user-defined labels and validates the application entry point.
- **Entry Point Resolution**: Correctly identifies the address of the label specified by the `entry` directive.
- **CLI Workflow**: Choose inputs interactively, list available `.asm` files, or provide a direct path; select the output format.
- **Output Modes**: `--emit ir` writes a textual `.ir` artifact; `--emit bin` writes a compact binary IR container.
- **Bare Metal & OS Support**: Includes a comprehensive set of tokens for BIOS (Legacy) and UEFI (modern) development.
- **Instruction Classification**: Tokens are clearly categorized into architecture-specific sets (x86, ARM, RISC-V).
- String literals inside `"..."` are kept as a single `STRING(...)` token.
- `#` starts a comment and ignores the rest of the line.

## Requirements

- A C++ compiler with C++26 support
- CMake 3.16+
- Ninja (optional; recommended for single-config builds)

## Platform & Architecture Support

`gasm` targets three major architectures with specific platform support:
- **x86 (64-bit)**: Windows (Win64 ABI), Linux (System V ABI), **Legacy BIOS (Real/Protected Mode)**.
- **AArch64**: Linux (SVC), Windows on ARM (bl/adr).
- **RISC-V (32/64-bit)**: Linux (ecall), Bare Metal/Embedded.
- **Firmware**: **UEFI (EFI format)** support via dedicated protocol tokens.

## Examples

The project now includes **100+ examples** demonstrating various features:
- Linux Syscalls (`syscall`, `svc`, `ecall`)
- Windows API calls (`MessageBox`, shadow space)
- **Legacy BIOS**: Keyboard I/O, VGA, GDT/IDT management (`cli`, `lgdt`, `out`).
- **UEFI**: Boot services, protocol handling, memory map resolution (`stall`, `allocate_pool`).
- High-level constructs (`if`, `else`, `while`, `struct`, `macro`)

You can find them in:
- `examples/x86/`

## Build and Run

Note: depending on the CMake generator you use, the final executable may be located directly under `build/` (Ninja, Make) or under a configuration subfolder like `build/Debug/` or `build/Release/` (Visual Studio). When using the Visual Studio generator pass `--config <Config>` to `cmake --build`.

### Configure & build (cross-platform)

```bash
cmake -S . -B build
cmake --build build
# For multi-config generators (Visual Studio):
cmake --build build --config Release
```

### Show help / run (Ninja or single-config builds)

Windows (PowerShell):
```powershell
.\build\gasm.exe --help
# or simply run the default build which compiles `index.asm` if present:
.\build\gasm.exe
```

Linux / macOS:
```bash
./build/gasm --help
./build/gasm
```

### Common usage examples

Compile a specific file and emit textual IR (default):
```bash
./build/gasm examples/x86/02_math.asm --emit ir
```

Emit a binary IR artifact:
```bash
./build/gasm examples/x86/02_math.asm --emit bin --output out.bin
```

List discovered `.asm` files:
```bash
./build/gasm --list-inputs
```

Pick an input interactively:
```bash
./build/gasm --pick
```

You can also pass options using short flags: `-i/--input`, `-e/--emit`, `-o/--output`, `-h/--help`.

Default behavior (when no `--input` is provided): `index.asm` is used if present in the project root. Default emit mode is `ir` and the default output path is the input path with `.ir` (or `.bin`) extension.
XOR(xor) RBX(rbx) COMMA(,) RBX(rbx) SEMICOLON(;)
LDR(ldr) X0(x0) COMMA(,) LEFTHESE([) SP(sp) RIGHTHESE(]) SEMICOLON(;)
...
```

## Token Vocabulary

`Tokens::Token` currently includes a wide range of tokens for multi-architecture and low-level support:

- **Output formats & Arch**: `format`, `win32`, `win64`, `elf32`, `elf64`, `bin` (Legacy), `efi` (UEFI), `arch`, `x86`, `aarch64`, `rv32`, `rv64`.
- **Keywords**: `entry`, `declare`, `struct`, `endstruct`, `macro`, `endmacro`, `if`, `else`, `print`, `call`.
- **Data Types**: `db`, `dw`, `dd`, `dq`, `int8`-`int64`, `uint8`-`uint64`, `float`, `double`, `char`.
- **BIOS / Low-Level**: `out`, `in`, `cli`, `sti`, `hlt`, `lidt`, `lgdt`, `smsw`, `lmsw`, `invlpg`, `wbinvd`, `rdmsr`, `wrmsr`, `rdtsc`, `cpuid`, `iret`.
- **UEFI Protocols**: `stall`, `reset`, `allocate_pages`, `get_memory_map`, `allocate_pool`, `open_protocol`, `locate_handle`.
- **Instructions (Multi-Arch)**:
  - **x86/General**: `mov`, `add`, `sub`, `mul`, `div`, `sqr`, `pow`, `cmp`, `jmp`, `jnz`, `inc`, `dec`, `xor`, `and`, `or`, `not`, `shl`, `shr`, `sar`, `rol`, `ror`, `ret`, `int`, `syscall`.
  - **AArch64/ARM**: `ldr`, `str`, `orr`, `eor`, `bic`, `lsl`, `lsr`, `asr`, `tst`, `b`, `bl`, `bx`, `adr`, `sdiv`, `udiv`, `bfi`, `ubfx`, `cbz`, `cbnz`.
  - **RISC-V**: `lui`, `auipc`, `lw`, `sw`, `ld`, `sd`, `addi`, `slt`, `slti`, `jal`, `jalr`, `beq`, `bne`, `blt`, `bge`.
- **Registers**:
  - **x86**: `rax`-`r15`, `eax`-`r15d`, `ax`-`r15w`, `al`-`r15b`, `rip`, `flags`, segments.
  - **AArch64/ARM**: `x0`-`x30`, `w0`-`w30`, `v0`-`v31`, `r0`-`r7`, `cpsr`, `spsr`.
  - **RISC-V**: ABI aliases (`zero`, `ra`, `sp`, `gp`, `tp`, `t0-t6`, `s0-s11`, `a0-a7`) and numeric `x0-x31`.

## Semantic Verification

Each time you run the compiler, it performs a basic **Symbol Resolution** pass:
- Resolves labels to their respective line numbers.
- Validates that the entry point specified by `entry <label>` exists in the symbol table.
- Reports resolution status (e.g., `Status: RESOLVED at line X`).

## Notes

- `>=` is not a single token yet; it is split into `>` and `=`.
- `#` comments are line-based.
- `"..."` string literals can contain spaces and punctuation without being split.

## Project Structure

- `main.cpp` - prototype front-end (lexer → parser → IR, CLI, symbol resolution)
- `index.asm` - sample HLA source file
- `examples/` - categorized multi-platform code snippets
- `CMakeLists.txt` - CMake build configuration (target: `gasm`)

## Build and Run

### Show help (Windows)

```powershell
cmake -S . -B build
cmake --build build
.\build\gasm.exe --help
```

### Compile default `index.asm` to textual IR (Windows)

```powershell
.\build\gasm.exe
```

### Compile a specific file (Windows)

```powershell
.\build\gasm.exe examples/x86/02_math.asm --emit ir
```

### Write binary IR instead of `.ir` (Windows)

```powershell
.\build\gasm.exe examples/x86/02_math.asm --emit bin --output out.bin
```

### List available source files (Windows)

```powershell
.\build\gasm.exe --list-inputs
```

You can also run `.uild\gasm.exe --pick` to choose a source file interactively.

### Linux build

Make sure you have `cmake` and a C++ compiler installed.

```bash
cmake -S . -B build
cmake --build build
```

### Linux run

```bash
./build/gasm --help
./build/gasm
./build/gasm examples/x86/02_math.asm --emit ir
./build/gasm examples/x86/02_math.asm --emit bin --output out.bin
./build/gasm --list-inputs
```

You can also run `./build/gasm --pick` to choose a source file interactively.

## Quick Verify

After running `gasm`, check that:
- punctuation appears as separate tokens (`SEMICOLON(;)`, `COLON(:)`, `ASSIGN(=)`),
- the selected output file is created,
- labels like `_start:` become `IDENTIFIER(_start) COLON(:)` in the generated IR.

## Roadmap

- Enrich IR nodes with instruction/operand structure
- Implement parser for directives, labels, and instructions
- Add semantic analysis (symbol table, type checks)
- Implement backend/code generation
- Add diagnostics with line/column information
- Add tests for tokenizer/parser behavior
- Replace the temporary binary IR container with a real code-generation backend

## Motivation

The long-term goal of `gasm` is to make low-level programming more approachable by combining assembly-level control with a cleaner high-level syntax.
