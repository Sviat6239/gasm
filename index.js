import { tokenizer } from "./js/lexer.js";
import { parser } from "./js/parser.js";

//console.log(tokenizer('mov rax, 19;'));

console.dir(parser(tokenizer('mov rax, 19; add rax, 19; sub rax, rbx')), { depth: null });