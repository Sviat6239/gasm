# GASM - Experimental C Prototype

GASM is a small C prototype for a toy assembly-like language. It reads
`code.as`, tokenizes each line, strips `//` comments, and prints the parsed
tokens together with a few debug markers for `let` and `echo` lines.

## Version

- `0.0.3` - initial working prototype with a single C interpreter in
  `gasm.c` and a sample program in `code.as`.

## Current status

- `gasm.c` reads `code.as` and processes it line by line.
- Comments starting with `//` are removed before tokenization.
- Semicolons are stripped before parsing.
- Each non-empty line is split into tokens and printed as `Line N: ...`.
- `let` lines generate simple LLVM IR with `alloca` and `store`.
- `echo` lines generate LLVM IR with `load` and `printf`.
- Parsed `let` and `echo` lines are written to `output.ll`.
- The program prints section headers for reading, tokenizing, and code generation.
- Unknown commands are reported with `Unknown command: ...`.

## What works now

- Parsing declaration-style lines such as:
  `let mut i32 number = 54;`
- Parsing immutable declarations:
  `let umut f64 pi = 3.14;`
- Supporting `i32`, `f32`, `f64`, and `str` types in the LLVM mapping.
- Keeping quoted strings together as one token:
  `let mut str msg = "Hello World";`
- Handling `echo (name);` for declared variables.
- Ignoring comment text after `//`.

## Known limitations

- No expression parsing.
- No arithmetic or block syntax.
- No conditionals or loops.
- `let` handling is still positional and assumes the current sample layout.
- `echo` expects a previously declared variable name.
- Unsupported lines fall through as unknown commands.

## Quick checks

Compile and run the prototype against the bundled sample:

```bash
gcc gasm.c -o a.exe
.\a.exe
```

The current `code.as` sample prints the parsing stages, generates LLVM-like
lines for `let` and `echo`, and creates `output.ll`.

## Examples

The `code.as` file contains the current demo program:

- mutable integer value
- mutable float value
- immutable float constant
- string value
- `echo (...)` statements
- reassignment-like line

## Project layout

- `gasm.c` - interpreter / tokenizer prototype
- `code.as` - sample source file
- `output.ll` - generated output file with LLVM-like lines
- `compile.ps1` - legacy build script, not used by the current prototype
- `LICENSE` - project license
