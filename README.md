# GASM

GASM is a toy assembly-like language prototype written in C. The current
repository contains an experimental frontend lexer/parser and a set of sample
`.as` sources used to exercise the language shape.

## Version

- `0.1.0`

## Current State

- `frontend/lexer.c` and `frontend/lexer.h` define token kinds for keywords,
  operators, identifiers, numeric literals, string literals, mutability, and a
  set of primitive type names.
- `frontend/parser.c` and `frontend/parser.h` define AST node types and parser
  entry points for declarations, `echo`, identifiers, literals, and basic
  binary expressions.
- `code.as` contains a sample program that uses explicit mutability and data
  types in `let` declarations.
- `gamma/` contains additional `.as` examples.
- `include/` contains platform-specific `.ll` snippets.
- `legacy/` is an older implementation and is intentionally not described
  here.

## Language Surface

The current lexer recognizes:

- `let`, `echo`
- `mut`, `umut`
- primitive type names such as `i64`, `i32`, `i16`, `i8`, `ui64`, `ui32`,
  `ui16`, `ui8`, `f64`, `f32`, `str`, and `char`
- identifiers
- integer and floating-point literals
- string literals
- arithmetic and grouping tokens such as `+`, `-`, `*`, `/`, `(`, `)`

The parser is structured to build AST nodes for:

- program blocks
- numeric and string values
- variable references
- `let` assignments with explicit mutability and type metadata
- `echo` statements
- binary expressions

## Examples

The bundled `code.as` sample demonstrates declarations like:

```text
let mut i32 number = 54;
let umut f64 pi = 3.14;
let mut str msg = "Hello World";
echo (number);
```

## Repository Layout

- `code.as` - main sample source file
- `gamma/` - additional example programs
- `frontend/` - lexer and parser prototype
- `include/` - platform-specific `.ll` include snippets
- `output.ll` - generated LLVM-like output sample
- `README.md` - project overview
