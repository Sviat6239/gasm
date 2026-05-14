# GASM - Experimental HLA Prototype (JavaScript)

GASM is a JavaScript prototype for tokenizing and partially parsing a
high-level assembler-like syntax across x86, AArch64, and RISC-V examples.
The current focus is front-end parsing (tokens -> AST-like nodes) with a
table-driven lexer and a lightweight parser.

## Version

- `0.0.1` - initial working prototype with lexer, parser, AST node classes,
  and a runnable parser demo in `index.js`.

## Current status

- `js/lexer.js` is implemented with keyword tables for directives,
  instructions, registers, operators, punctuation, and RISC-V compressed forms.
- `js/parser.js` is implemented and builds `ProgramNode` with instruction,
  label, variable declaration, register, number, string, and identifier nodes.
- `js/ast.js` defines many node classes used by the parser and future features.
- `js/ir.js` and `js/codegen.js` exist but are currently empty.
- `index.js` is not a CLI; it runs a hardcoded parser demo snippet.

## What works now

- Decimal numeric literals (`0-9` digits).
- String literals in single or double quotes with basic escapes (`\n`, `\t`).
- Tokenization of punctuation and operators:
  `; : , { } [ ] ( ) = == != < <= > >= && || ++ -- . * % & + - /`.
- Unknown words are tokenized as `{ type: 'name', value }`.
- Parser handles:
  - instruction statements with operands and commas,
  - labels (`name:`),
  - variable declarations (`declare name type[...] = ...`),
  - output as `ProgramNode` with node instances from `js/ast.js`.
- Supported instruction groups currently include:
  - x86 / x86-64 basics and common SSE/FPU mnemonics,
  - ARM64/AArch64 arithmetic, branch, system, and floating-point mnemonics,
  - RISC-V base integer, M/A/CSR, pseudo-instructions (`li`, `la`, `ecall`),
    and compressed `c.*` forms.

## Known limitations

- Comments are not supported in lexer input (`#` throws `Unknown charecter`).
- Parser is still partial:
  - no expression trees or block parsing (`if`, `while`, `for`, etc.),
  - some AST/parser branches are unfinished/buggy.
- `index.js` is a demo script, not a command-line interface.

## Quick checks

Tokenizer only:

```bash
node --input-type=module -e "import { tokenizer } from './js/lexer.js'; console.log(tokenizer('mov rax, 19;'))"
```

Tokenizer + parser (minimal working example):

```bash
node --input-type=module -e "import { tokenizer } from './js/lexer.js'; import { parser } from './js/parser.js'; console.dir(parser(tokenizer('mov rax, 19; add rax, 1;')), { depth: null });"
```

Current demo input from `index.js`:

```bash
node --input-type=module -e "import { tokenizer } from './js/lexer.js'; import { parser } from './js/parser.js'; console.dir(parser(tokenizer('declare msg char[] = \"Hello Win64!\"; mov rax, 19; add rax, 19; sub rax, rbx;')), { depth: null });"
```

## Examples

The `examples/` folder contains sample sources by target:

- `examples/x86/`
- `examples/aarch64/`
- `examples/riscv/`
- `examples/bios/`
- `examples/uefi/`

## Project layout

- `js/lexer.js` - tokenizer
- `js/parser.js` - parser (token stream to AST-like nodes)
- `js/ast.js` - node type definitions
- `js/ir.js` - reserved for IR stage (empty)
- `js/codegen.js` - reserved for codegen stage (empty)
- `index.js` - local parser demo script
- `index.asm` - sample source file
