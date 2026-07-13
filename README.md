# GASM - Experimental C Prototype

GASM is a small C prototype for a toy assembly-like language. It reads
`code.as`, tokenizes each line, strips `//` comments, and prints the parsed
tokens together with a few debug markers for `let` and `echo` lines.

## Version

- `0.0.4` - current prototype with a single C interpreter in `gasm.c` and a
  sample program in `code.as`.

## Current status

- `gasm.c` reads `code.as` line by line, strips `//` comments, and removes
  trailing semicolons before parsing.
- Non-empty lines are tokenized and printed as `Line N: ...` for debugging.
- `let` declarations generate LLVM IR with `alloca` and `store`.
- `echo` reads a declared variable, emits `load`, and prints it with `printf`.
- String values are stored as LLVM globals and printed through `@printf`.
- Parsed `let` and `echo` lines are written to `output.ll`.
- Other lines are currently skipped during code generation.
- The program prints section headers for reading, tokenizing, and code
  generation.

## What works now

- Parsing declaration-style lines such as `let mut i32 number = 54;`.
- Parsing immutable declarations such as `let umut f64 pi = 3.14;`.
- Supporting integer aliases `i8`, `i16`, `i32`, `i64`, `ui8`, `ui16`,
  `ui32`, `ui64`, `int8_t`, `int16_t`, `int32_t`, `int64_t`, `uint8_t`,
  `uint16_t`, `uint32_t`, `uint64_t`, and `char`.
- Supporting floating-point aliases `f32`, `float`, `f64`, and `double`.
- Supporting string values with quoted text kept together as one token, for
  example `let mut str msg = "Hello World";`.
- Handling `echo (name);` for previously declared variables.
- Ignoring comment text after `//`.

## Known limitations

- No expression parsing.
- No arithmetic or block syntax.
- No conditionals or loops.
- `let` handling is positional and expects the current token layout.
- Reassignment lines such as `number = number + 11;` are currently skipped.
- `echo` expects a previously declared variable name.

## Quick checks

Compile and run the prototype against the bundled sample:

```bash
gcc gasm.c -o a.exe
.\a.exe
```

The current `code.as` sample prints the parsing stages, generates LLVM-like
lines for `let` and `echo`, and creates `output.ll`. The sample also contains
a reassignment-like line that is currently skipped.

## Examples

The `code.as` file contains the current demo program:

- mutable integer value
- mutable float value
- immutable float constant
- string value
- `echo (...)` statements
- a reassignment-like line that is currently skipped

## Project layout

- `gasm.c` - interpreter / tokenizer prototype
- `code.as` - sample source file
- `output.ll` - generated output file with LLVM-like lines
- `compile.ps1` - legacy build script, not used by the current prototype
- `LICENSE` - project license
