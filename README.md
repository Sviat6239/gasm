# GASM - High-Level Assembler (HLA)

`gasm` is an experimental high-level assembler written in C++.
The project aims to provide a cleaner, more readable assembly-like language and later translate it into lower-level output.

## Status

This project is in an early prototype stage.

Current state:
- Token enum is defined for core language elements.
- Source loading from `index.asm` is started.
- Full lexer/parser/code generation is not implemented yet.

## Example Syntax

Current sample input (`index.asm`):

```asm
format win32;
declare number dw = 84;

mov rax, 84;
add rax, number;
print rax;
```

## Planned Language Features

- Output formats: `win32`, `win64`, `elf32`, `elf64`
- Data directives: `db`, `dw`, `dd`, `dq`
- Instructions: `mov`, `add`, `print`
- Registers:
  - 64-bit: `rax`, `rbx`, `rcx`, `rdx`
  - 32-bit: `eax`, `ebx`, `ecx`, `edx`
  - 16-bit: `ax`, `bx`, `cx`, `dx`

## Project Structure

- `main.cpp` - compiler front-end prototype (tokens + source reading skeleton)
- `index.asm` - example HLA source file
- `CMakeLists.txt` - CMake build config

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Roadmap

- Implement lexer/tokenizer
- Implement parser for directives and instructions
- Add semantic analysis (symbols, type checks)
- Implement backend/code generation
- Add clear diagnostics with line/column info
- Add tests for lexer/parser behavior

## Motivation

The long-term goal of `gasm` is to make low-level programming more approachable by combining assembly-level control with a cleaner high-level syntax.

