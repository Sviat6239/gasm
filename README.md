# GASM - Experimental C Prototype

GASM is a small C prototype for a toy assembly-like language. It reads
`code.as`, tokenizes each line, strips `//` comments, and prints the parsed
tokens together with a few debug markers for `let` and `echo` lines.

## Version

- `0.0.1` - initial working prototype with a single C interpreter in
  `gasm.c` and a sample program in `code.as`.

## Current status

- `gasm.c` reads `code.as` and processes it line by line.
- Comments starting with `//` are removed before tokenization.
- Each non-empty line is split into tokens and printed as `Line N: ...`.
- `let` lines are detected and logged as `let`.
- `echo` lines are detected and logged as `echo`.

## What works now

- Tokenizing declaration-style lines such as:
  `let mut i32 number = 54;`
- Tokenizing immutable declarations:
  `let umut f64 pi = 3.14;`
- Keeping quoted strings together as one token:
  `let mut str msg = "Hello World";`
- Splitting parentheses into separate tokens:
  `echo (number);`
- Ignoring comment text after `//`.

## Known limitations

- No expression parsing.
- No arithmetic or block syntax.
- No variable evaluation or execution semantics.
- No conditionals or loops.
- `let` handling is still hardcoded and does not yet map tokens to real
  variable definitions.

## Quick checks

Compile and run the prototype against the bundled sample:

```bash
gcc gasm.c -o a.exe
.\a.exe
```

The current `code.as` sample prints tokenized lines, then `let` / `echo`
markers for matching statements.

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
- `compile.ps1` - legacy build script, not used by the current prototype
- `LICENSE` - project license
