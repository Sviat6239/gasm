# GASM - High-Level Assembler (HLA)

`gasm` is an experimental high-level assembler written in C++.
Right now, the project focuses on the very first front-end step: splitting source lines into tokens.

## Status

This project is in an early prototype stage.

Current state:
- A `Tokens::Token` enum is defined for the language vocabulary.
- `main.cpp` reads `index.asm` line by line.
- A basic tokenizer splits tokens by whitespace and punctuation: `:`, `;`, `,`, `=`, `"`, `<`, `>`, `(`, `)`, `[`, `]`, `{`, `}`.
- Tokens are stored as `vector<vector<string>>` (per-line token list) and printed.
- Token classification, parser, and code generation are not implemented yet.

## Example Input

Current sample input (`index.asm`):

```asm
format win32;
declare number dw = 84;
entry _start;

_start:
    mov rax, 84;
    add rax, number;
    print rax;
```

## Current Behavior

The current prototype:
- treats spaces/tabs/newlines as token boundaries,
- emits punctuation as standalone tokens (`:`, `;`, `,`, `=`, `"`, `<`, `>`, `(`, `)`, `[`, `]`, `{`, `}`),
- keeps tokens grouped by source line,
- prints each token as `[token]`.

Example output shape:

```text
[format] [win32] [;]
[declare] [number] [dw] [=] [84] [;]
...
```

## Token Vocabulary

`Tokens::Token` currently includes the following planned language tokens:

- Output formats: `format`, `win32`, `win64`, `elf32`, `elf64`
- Declarations and structure keywords: `entry`, `declare`, `struct`, `endstruct`, `macro`, `endmacro`, `if`, `else`
- Data directives and types: `db`, `dw`, `dd`, `dq`, `int8`, `int16`, `int32`, `int64`, `uint8`, `uint16`, `uint32`, `uint64`, `float`, `double`, `char`
- Statements and punctuation: `=`, `:`, `;`, `,`, `string`, `number`
- Instructions: `mov`, `add`, `sub`, `mul`, `div`, `sqr`, `pow`, `cmp`, `jmp`, `jnz`, `inc`, `dec`, `print`
- Registers:
  - 64-bit: `rax`, `rbx`, `rcx`, `rdx`, `rsp`, `rbp`, `rsi`, `rdi`, `r8`-`r15`
  - 32-bit: `eax`, `ebx`, `ecx`, `edx`, `esp`, `ebp`, `esi`, `edi`, `r8d`-`r15d`
  - 16-bit: `ax`, `bx`, `cx`, `dx`, `sp`, `bp`, `si`, `di`, `r8w`-`r15w`
  - 8-bit: `al`, `bl`, `cl`, `dl`, `ah`, `bh`, `ch`, `dh`, `spl`, `bpl`, `sil`, `dil`, `r8b`-`r15b`
  - Segment and special registers: `cs`, `ds`, `es`, `fs`, `gs`, `ss`, `rip`, `eip`, `ip`, `rflags`, `eflags`, `flags`

Token classification is still a future step; right now the program only splits and prints raw strings.

## Project Structure

- `main.cpp` - prototype front-end (`Tokens::Token`, file reading, token splitting, token dump)
- `index.asm` - sample HLA source file
- `CMakeLists.txt` - CMake build configuration (target: `rasm`)

## Build and Run

```bash
cmake -S . -B build
cmake --build build
./build/rasm
```

## Quick Verify

After running `rasm`, check that:
- punctuation appears as separate tokens (`[;]`, `[,]`, `[:]`, `[=]`, `[""]`),
- lines are printed in the same order as in `index.asm`,
- labels like `_start:` become `[_start] [:]`.

## Roadmap

- Add keyword-aware lexical token classification (map strings to `Tokens::Token`)
- Implement parser for directives, labels, and instructions
- Add semantic analysis (symbol table, type checks)
- Implement backend/code generation
- Add diagnostics with line/column information
- Add tests for tokenizer/parser behavior

## Motivation

The long-term goal of `gasm` is to make low-level programming more approachable by combining assembly-level control with a cleaner high-level syntax.

