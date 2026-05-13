import { tokenizer } from "./js/lexer.js";
import { parser } from "./js/parser.js";

//console.log(tokenizer('mov rax, 19;'));

console.log(parser(tokenizer('mov rax, 19; add rax, 19;')));