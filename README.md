# GASM - Experimental HLA Prototype (JavaScript)

GASM is a small JavaScript prototype for tokenizing and partially parsing a
high-level assembler syntax. The repository currently focuses on the front-end
scaffolding (tokenizer and a token-to-node mapper). AST/IR/codegen and a CLI are
not implemented yet.

## Status

- Tokenizer implemented in `js/lexer.js`.
- Parser implemented in `js/parser.js` (maps a single token to a node; it does
  not build a full Program AST yet).
- `js/ast.js`, `js/ir.js`, and `js/codegen.js` are placeholders.
- `index.js` is empty (no CLI yet).

## What works today

- Numeric literals: digits only.
- String literals in single or double quotes (basic escapes: `\n`, `\t`, and
  a raw escaped character).
- Identifiers and a large keyword list for directives, instructions, and
  registers.
- Tokens are returned as `{ type, value }` objects.

## Known limitations

- Punctuation tokens (`;`, `:`, `,`, `[]`, `()`, operators) are not tokenized
  yet.
- Comments are not supported (`#` will throw an error).
- The parser does not iterate over all tokens and does not return a Program AST.
- No runtime, CLI, or build system is included yet.

## Quick check (tokenizer only)

Use input without punctuation:

```bash
node --input-type=module -e "import { tokenizer } from './js/lexer.js'; console.log(tokenizer('mov rax'))"
```

## Examples

The `examples/` folder contains sample sources organized by architecture:

- `examples/x86/`
- `examples/aarch64/`
- `examples/riscv/`
- `examples/bios/`
- `examples/uefi/`

## Project structure

- `js/lexer.js` - tokenizer
- `js/parser.js` - token-to-node mapper
- `js/ast.js` - placeholder
- `js/ir.js` - placeholder
- `js/codegen.js` - placeholder
- `index.asm` - sample input file

## Notes

- The keyword vocabulary is defined directly in `js/lexer.js`.
- Examples may use punctuation and comments that are not tokenized yet.
