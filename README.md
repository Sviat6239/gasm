# GASM - High-Level Assembler (HLA)

`gasm` is an experimental high-level assembler written in C++.
Right now, the project focuses on the very first front-end step: splitting source lines into tokens.

## Status

This project is in an early prototype stage.

Current state:
- A `Tokens::Token` enum is defined for the language vocabulary.
- `main.cpp` reads `index.asm` line by line.
- A basic tokenizer splits tokens by whitespace and punctuation: `:`, `;`, `,`, `=`, `"`, `<`, `>`, `(`, `)`, `[`, `]`, `{`, `}`.
- String literals inside `"..."` are kept as a single `STRING(...)` token.
- `#` starts a comment and ignores the rest of the line.
- Tokens are stored as `vector<vector<string>>` (per-line token list) and printed as `TOKEN(value)`.
- Token classification, parser, and code generation are not implemented yet.

## Example Input

Current sample input (`index.asm`):

```asm
arch x86;
format elf64;

declare number dw = 84;
declare msg1 char[] = "Grether than 150";
declare msg2 char[] = "Less than 150";

entry _start;
# simple comment

_start:
    mov rax, 84;
    add rax, number;
    if(rax >= 150){
        print msg1;
    } else {
        print msg2;
    }
    print rax;
```

## Current Behavior

The current prototype:
- treats spaces/tabs/newlines as token boundaries,
- emits punctuation as standalone tokens (`:`, `;`, `,`, `=`, `"`, `<`, `>`, `(`, `)`, `[`, `]`, `{`, `}`),
- handles string literals and comments,
- prints each token as `TOKEN(value)`.

Example output shape:

```text
ARCH(arch) X86(x86) SEMICOLON(;)
FORMAT(format) ELF64(elf64) SEMICOLON(;)
DECLARE(declare) IDENTIFIER(number) DW(dw) ASSIGN(=) NUMBER(84) SEMICOLON(;)
DECLARE(declare) IDENTIFIER(msg1) CHAR(char) LEFTHESE([) RIGHTHESE(]) ASSIGN(=) STRING(Grether than 150) SEMICOLON(;)
DECLARE(declare) IDENTIFIER(msg2) CHAR(char) LEFTHESE([) RIGHTHESE(]) ASSIGN(=) STRING(Less than 150) SEMICOLON(;)
ENTRY(entry) IDENTIFIER(_start) SEMICOLON(;)
IDENTIFIER(_start) COLON(:)
... 
```

## Token Vocabulary

`Tokens::Token` currently includes the following tokens:

- Output formats: `format`, `win32`, `win64`, `elf32`, `elf64`
- Architecture tags: `arch`, `x86`, `aarch`, `aarch64`, `rv32`, `rv64`
- Declarations and structure keywords: `entry`, `declare`, `struct`, `endstruct`, `macro`, `endmacro`, `if`, `else`
- Data directives and types: `db`, `dw`, `dd`, `dq`, `int8`, `int16`, `int32`, `int64`, `uint8`, `uint16`, `uint32`, `uint64`, `float`, `double`, `char`
- Statements and punctuation: `=`, `:`, `;`, `,`, `(`, `)`, `[`, `]`, `{`, `}`, `<`, `>`, `string`, `number`
- Instructions: `mov`, `add`, `sub`, `mul`, `div`, `sqr`, `pow`, `cmp`, `jmp`, `jnz`, `inc`, `dec`, `print`, `call`
- Registers:
  - x86 (64/32/16/8-bit): `rax`-`r15`, `eax`-`r15d`, `ax`-`r15w`, `al`-`r15b`, `rip`, `flags`, segments.
  - AArch64: `x0`-`x30`, `w0`-`w30`.
  - ARM: `r0`-`r7`.

Token classification is partial: keywords, registers, and punctuation are mapped to tokens; unknown words become `IDENTIFIER(...)`.

## Notes

- `>=` is not a single token yet; it is split into `>` and `=`.
- `#` comments are line-based.
- `"..."` string literals can contain spaces and punctuation without being split.

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
- punctuation appears as separate tokens (`SEMICOLON(;)`, `COLON(:)`, `ASSIGN(=)`),
- lines are printed in the same order as in `index.asm`,
- labels like `_start:` become `IDENTIFIER(_start) COLON(:)`.

## Roadmap

- Add keyword-aware lexical token classification (map strings to `Tokens::Token`)
- Implement parser for directives, labels, and instructions
- Add semantic analysis (symbol table, type checks)
- Implement backend/code generation
- Add diagnostics with line/column information
- Add tests for tokenizer/parser behavior

## Motivation

The long-term goal of `gasm` is to make low-level programming more approachable by combining assembly-level control with a cleaner high-level syntax.
