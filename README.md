# GASM - Experimental PHP Prototype

GASM is a small PHP prototype for a toy assembly-like language. It reads
`code.as`, tokenizes each line with a simple regex, tracks mutable and
immutable values, and prints values through `echo(...)`.

## Version

- `0.0.1` - initial working prototype with a single PHP interpreter in
  `gasm.php` and a sample program in `code.as`.

## Current status

- `gasm.php` reads `code.as` and processes it line by line.
- `let` declarations are supported for mutable (`mut`) and immutable (`umut`)
  values.
- Variables store a `type` and a `value`.
- `echo(...)` prints literals, variables, and constants in order.
- Simple reassignment is supported with `name = value`.

## What works now

- Declaration syntax in the current sample form:
  `let mut:i32:number = 54;`
- Immutable declarations:
  `let umut:f64:pi = 3.14;`
- String values in quotes:
  `let mut:str:msg = "Hello World";`
- Printing values:
  `echo (number float_num);`
- Reassigning mutable values:
  `number = 100;`

## Known limitations

- No expression parsing.
- No arithmetic or block syntax.
- No comments.
- No conditionals or loops.
- Tokens are extracted with a very small regex, so unsupported characters are
  ignored or skipped rather than handled by a real lexer.

## Quick checks

Run the interpreter against the bundled sample:

```bash
php .\gasm.php
```

The current `code.as` sample prints:

```bash
54 5.14
5.14
3.14
Hello
100
```

## Examples

The `code.as` file contains the current demo program:

- mutable integer value
- mutable float value
- immutable float constant
- string value
- `echo(...)` output
- mutable reassignment

## Project layout

- `gasm.php` - interpreter
- `code.as` - sample source file
- `compile.ps1` - legacy build script, not used by the PHP prototype
- `LICENSE` - project license
