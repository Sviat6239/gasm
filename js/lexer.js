export function tokenizer(input) {
    let current = 0;
    let tokens = [];

    while (current < input.length) {
        let char = input[current];
        if (char === '(') {
            tokens.push({
                type: 'leftParent',
                value: '(',
            })
            current++;
            continue
        }

        if (char === ')') {
            tokens.push({
                type: 'rightParent',
                value: ')',
            })
            current++;
            continue;
        }

        let NUMBERS = /[0-9]/;
        if (NUMBERS.test(char)) {
            let value = '';
            while (current < input.length && NUMBERS.test(char)) {
                value += char;
                char = input[++current];
            }
            tokens.push({ type: 'number', value });
            continue;
        }

        let WHITESPACE = /\s/;
        if (WHITESPACE.test(char)) {
            current++;
            continue;
        }

        let LETTERS = /[a-z0-9_]/i;
        if (/[a-z]/i.test(char)) {
            let value = '';
            while (current < input.length && LETTERS.test(char)) {
                value += char;
                char = input[++current];
            }
            //Directives and configuration
            if (value === 'format') {
                tokens.push({ type: 'format', value: value });
            } else if (value === 'win_32') {
                tokens.push({ type: 'win_32', value: value });
            } else if (value === 'win_64') {
                tokens.push({ type: 'win_64', value: value });
            } else if (value === 'elf_32') {
                tokens.push({ type: 'elf_32', value: value });
            } else if (value === 'elf_64') {
                tokens.push({ type: 'elf_64', value });
            } else if (value === 'bin') {
                tokens.push({ type: 'bin', value: value });
            } else if (value === 'efi_32') {
                tokens.push({ type: 'efi_32', value: value });
            } else if (value === 'efi_64') {
                tokens.push({ type: 'efi_64', value: value });
            } else if (value === 'arch') {
                tokens.push({ type: 'arch', value: value });
            } else if (value === 'x86_16') {
                tokens.push({ type: 'x86_16', value: value });
            } else if (value === 'x86_32') {
                tokens.push({ type: 'x86_32', value: value });
            } else if (value === 'x86_64') {
                tokens.push({ type: 'x86_64', value: value });
            } else if (value === 'entry') {
                tokens.push({ type: 'entry', value: value });
            } else if (value === 'declare') {
                tokens.push({ type: 'declare', value: value });
            }
            //Identifier and literals
            else if (value === 'db') {
                tokens.push({ type: 'db', value: value });
            } else if (value === 'dw') {
                tokens.push({ type: 'dw', value: value });
            } else if (value === 'dd') {
                tokens.push({ type: 'dd', value: value });
            } else if (value === 'dq') {
                tokens.push({ type: 'dq', value: value });
            } else if (value === 'rb') {
                tokens.push({ type: 'rb', value: value });
            } else if (value === 'rw') {
                tokens.push({ type: 'rw', value: value });
            } else if (value === 'rd') {
                tokens.push({ type: 'rd', value: value });
            } else if (value === 'rq') {
                tokens.push({ type: 'rq', value: value });
            } else if (value === 'int8') {
                tokens.push({ type: 'int8', value: value });
            } else if (value === 'int16') {
                tokens.push({ type: 'int16', value: value });
            } else if (value === 'int32') {
                tokens.push({ type: 'int32', value: value });
            } else if (value === 'int64') {
                tokens.push({ type: 'int64', value: value });
            } else if (value === 'uint8') {
                tokens.push({ type: 'uint8', value: value });
            } else if (value === 'uint16') {
                tokens.push({ type: 'uint16', value: value });
            } else if (value === 'uint32') {
                tokens.push({ type: 'uint32', value: value });
            } else if (value === 'uint64') {
                tokens.push({ type: 'int64', value: value });
            } else if (value === 'float') {
                tokens.push({ type: 'float', value: value });
            } else if (value === 'double') {
                tokens.push({ type: 'double', value: value });
            } else if (value === 'char') {
                tokens.push({ type: 'char', value: value });
            }
            //Structural directives
            else if (value === 'struct') {
                tokens.push({ type: 'struct', value: value });
            } else if (value === 'ends') {
                tokens.push({ type: 'ends', value: value });
            } else if (value === 'macro') {
                tokens.push({ type: 'macro', value: value });
            } else if (value === 'endm') {
                tokens.push({ type: 'endm', value: value });
            }
            //Control flow
            else if (value === 'if') {
                tokens.push({ type: 'if', value: value });
            } else if (value === 'else') {
                tokens.push({ type: 'else', value: value });
            } else if (value === 'switch') {
                tokens.push({ type: 'switch', value: value });
            } else if (value === 'case') {
                tokens.push({ type: 'case', value: value });
            }
            //Operators and punctuation
            else if (value === '=') {
                tokens.push({ type: 'assign', value: value });
            } else if (value === ':') {
                tokens.push({ type: ':', value: value });
            } else if (value === ';') {
                tokens.push({ type: 'semicolon', value: value });
            } else if (value === ',') {
                tokens.push({ type: 'comma', value: value });
            } else if (value === '{') {
                tokens.push({ type: 'lbrace', value: value });
            } else if (value === '}') {
                tokens.push({ type: 'rbrace', value: value });
            } else if (value === '[') {
                tokens.push({ type: 'lbracket', value: value });
            } else if (value === ']') {
                tokens.push({ type: 'rbracket', value: value });
            } else if (value === '<') {
                tokens.push({ type: 'less', value: value });
            } else if (value === '>') {
                tokens.push({ type: 'greater', value: value });
            } else if (value === '<=') {
                tokens.push({ type: 'lessOrEqual', value: value });
            } else if (value === '>=') {
                tokens.push({ type: 'greaterOrEqual', value: value });
            }
            else {
                tokens.push({ type: 'name', value });
            }
            continue;
        }
        throw new TypeError('Unknown charecter' + char);
    }

    return tokens;
}