export function tokenizer(input) {
    let current = 0;
    let tokens = [];

    while (current < input.length) {
        let char = input[current];

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

        if (char === '"' || char === "'") {
            let quote = char;
            let value = '';
            char = input[++current];
            while (current < input.length && char !== quote) {
                if (char === '\\') {
                    const next = input[++current];
                    if (next === 'n') value += '\n';
                    else if (next === 't') value += '\t';
                    else value += next;
                    char = input[++current];
                    continue;
                }
                value += char;
                char = input[++current];
            }
            current++;
            tokens.push({ type: 'string', value });
            continue;
        }

        let twoChar = input.slice(current, current + 2);
        if (twoChar === '==') {
            tokens.push({ type: 'isEqual', value: twoChar });
            current += 2;
            continue;
        }
        if (twoChar === '!=') {
            tokens.push({ type: 'notEqual', value: twoChar });
            current += 2;
            continue;
        }
        if (twoChar === '<=') {
            tokens.push({ type: 'lessOrEqual', value: twoChar });
            current += 2;
            continue;
        }
        if (twoChar === '>=') {
            tokens.push({ type: 'greaterOrEqual', value: twoChar });
            current += 2;
            continue;
        }
        if (twoChar === '&&') {
            tokens.push({ type: 'logical_and', value: twoChar });
            current += 2;
            continue;
        }
        if (twoChar === '||') {
            tokens.push({ type: 'logical_or', value: twoChar });
            current += 2;
            continue;
        }
        if (twoChar === '++') {
            tokens.push({ type: 'incremental', value: twoChar });
            current += 2;
            continue;
        }
        if (twoChar === '--') {
            tokens.push({ type: 'decremental', value: twoChar });
            current += 2;
            continue;
        }

        if (char === '=') {
            tokens.push({ type: 'assign', value: char });
            current++;
            continue;
        }
        if (char === ':') {
            tokens.push({ type: 'colon', value: char });
            current++;
            continue;
        }
        if (char === ';') {
            tokens.push({ type: 'semicolon', value: char });
            current++;
            continue;
        }
        if (char === ',') {
            tokens.push({ type: 'comma', value: char });
            current++;
            continue;
        }
        if (char === '{') {
            tokens.push({ type: 'lbrace', value: char });
            current++;
            continue;
        }
        if (char === '}') {
            tokens.push({ type: 'rbrace', value: char });
            current++;
            continue;
        }
        if (char === '[') {
            tokens.push({ type: 'lbracket', value: char });
            current++;
            continue;
        }
        if (char === ']') {
            tokens.push({ type: 'rbracket', value: char });
            current++;
            continue;
        }
        if (char === '(') {
            tokens.push({ type: 'lparent', value: char });
            current++;
            continue;
        }
        if (char === ')') {
            tokens.push({ type: 'rparent', value: char });
            current++;
            continue;
        }
        if (char === '<') {
            tokens.push({ type: 'less', value: char });
            current++;
            continue;
        }
        if (char === '>') {
            tokens.push({ type: 'greater', value: char });
            current++;
            continue;
        }
        if (char === '.') {
            tokens.push({ type: 'dot', value: char });
            current++;
            continue;
        }
        if (char === '*') {
            tokens.push({ type: 'star', value: char });
            current++;
            continue;
        }
        if (char === '%') {
            tokens.push({ type: 'module', value: char });
            current++;
            continue;
        }
        if (char === '&') {
            tokens.push({ type: 'ampersand', value: char });
            current++;
            continue;
        }
        if (char === '+') {
            tokens.push({ type: 'plus', value: char });
            current++;
            continue;
        }
        if (char === '-') {
            tokens.push({ type: 'minus', value: char });
            current++;
            continue;
        }
        if (char === '/') {
            tokens.push({ type: 'divide', value: char });
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
            } else if (value === 'function') {
                tokens.push({ type: 'endf', value: value });
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
            // x86 and ARM instructions
            else if (value === 'mov') {
                tokens.push({ type: 'mov', value: value });
            } else if (value === 'add') {
                tokens.push({ type: 'add', value: value });
            } else if (value === 'sub') {
                tokens.push({ type: 'sub', value: value });
            } else if (value === 'mul') {
                tokens.push({ type: 'mul', value: value });
            } else if (value === 'div') {
                tokens.push({ type: 'div', value: value });
            } else if (value === 'sqr') {
                tokens.push({ type: 'sqr', value: value });
            } else if (value === 'pow') {
                tokens.push({ type: 'pow', value: value });
            } else if (value === 'cmp') {
                tokens.push({ type: 'cmp', value: value });
            } else if (value === 'jmp') {
                tokens.push({ type: 'jmp', value: value });
            } else if (value === 'jnz') {
                tokens.push({ type: 'jnz', value: value });
            } else if (value === 'inc') {
                tokens.push({ type: 'inc', value: value });
            } else if (value === 'dec') {
                tokens.push({ type: 'dec', value: value });
            } else if (value === 'xor') {
                tokens.push({ type: 'xor', value: value });
            } else if (value === 'and') {
                tokens.push({ type: 'and', value: value });
            } else if (value === 'or') {
                tokens.push({ type: 'or', value: value });
            } else if (value === 'not') {
                tokens.push({ type: 'not', value: value });
            } else if (value === 'shl') {
                tokens.push({ type: 'shl', value: value });
            } else if (value === 'shr') {
                tokens.push({ type: 'shr', value: value });
            } else if (value === 'sar') {
                tokens.push({ type: 'sar', value: value });
            } else if (value === 'rol') {
                tokens.push({ type: 'rol', value: value });
            } else if (value === 'ror') {
                tokens.push({ type: 'ror', value: value });
            } else if (value === 'ret') {
                tokens.push({ type: 'ret', value: value });
            } else if (value === 'int') {
                tokens.push({ type: 'int', value: value });
            } else if (value === 'syscall') {
                tokens.push({ type: 'syscall', value: value });
            } else if (value === 'ldr') {
                tokens.push({ type: 'ldr', value: value });
            } else if (value === 'str') {
                tokens.push({ type: 'str', value: value });
            } else if (value === 'orr') {
                tokens.push({ type: 'orr', value: value });
            } else if (value === 'eor') {
                tokens.push({ type: 'eor', value: value });
            } else if (value === 'bic') {
                tokens.push({ type: 'bic', value: value });
            } else if (value === 'lsl') {
                tokens.push({ type: 'lsl', value: value });
            } else if (value === 'lsr') {
                tokens.push({ type: 'lsr', value: value });
            } else if (value === 'asr') {
                tokens.push({ type: 'asr', value: value });
            } else if (value === 'tst') {
                tokens.push({ type: 'tst', value: value });
            } else if (value === 'b') {
                tokens.push({ type: 'b', value: value });
            } else if (value === 'bl_op') {
                tokens.push({ type: 'bl_op', value: value });
            } else if (value === 'bx_op') {
                tokens.push({ type: 'bx_op', value: value });
            } else if (value === 'adr') {
                tokens.push({ type: 'adr', value: value });
            } else if (value === 'sdiv') {
                tokens.push({ type: 'sdiv', value: value });
            } else if (value === 'udiv') {
                tokens.push({ type: 'udiv', value: value });
            } else if (value === 'bfi') {
                tokens.push({ type: 'bfi', value: value });
            } else if (value === 'ubfx') {
                tokens.push({ type: 'ubfx', value: value });
            } else if (value === 'cbz') {
                tokens.push({ type: 'cbz', value: value });
            } else if (value === 'cbnz') {
                tokens.push({ type: 'cbnz', value: value });
            } else if (value === 'lui') {
                tokens.push({ type: 'lui', value: value });
            } else if (value === 'auipc') {
                tokens.push({ type: 'auipc', value: value });
            } else if (value === 'lw') {
                tokens.push({ type: 'lw', value: value });
            } else if (value === 'sw') {
                tokens.push({ type: 'sw', value: value });
            } else if (value === 'ld') {
                tokens.push({ type: 'ld', value: value });
            } else if (value === 'sd') {
                tokens.push({ type: 'sd', value: value });
            } else if (value === 'addi') {
                tokens.push({ type: 'addi', value: value });
            } else if (value === 'slt') {
                tokens.push({ type: 'slt', value: value });
            } else if (value === 'slti') {
                tokens.push({ type: 'slti', value: value });
            } else if (value === 'jal') {
                tokens.push({ type: 'jal', value: value });
            } else if (value === 'jalr') {
                tokens.push({ type: 'jalr', value: value });
            } else if (value === 'li') {
                tokens.push({ type: 'li', value: value });
            } else if (value === 'la') {
                tokens.push({ type: 'la', value: value });
            } else if (value === 'ecall') {
                tokens.push({ type: 'ecall', value: value });
            } else if (value === 'beq') {
                tokens.push({ type: 'beq', value: value });
            } else if (value === 'bne') {
                tokens.push({ type: 'bne', value: value });
            } else if (value === 'blt') {
                tokens.push({ type: 'blt', value: value });
            } else if (value === 'bge') {
                tokens.push({ type: 'bge', value: value });
            }
            //x86 register names
            else if (value === 'rax') {
                tokens.push({ type: 'rax', value: value });
            } else if (value === 'rbx') {
                tokens.push({ type: 'rbx', value: value });
            } else if (value === 'rcx') {
                tokens.push({ type: 'rcx', value: value });
            } else if (value === 'rdx') {
                tokens.push({ type: 'rdx', value: value });
            } else if (value === 'rsp') {
                tokens.push({ type: 'rsp', value: value });
            } else if (value === 'rbp') {
                tokens.push({ type: 'rbp', value: value });
            } else if (value === 'rsi') {
                tokens.push({ type: 'rsi', value: value });
            } else if (value === 'rdi') {
                tokens.push({ type: 'rdi', value: value });
            } else if (value === 'r8') {
                tokens.push({ type: 'r8', value: value });
            } else if (value === 'r9') {
                tokens.push({ type: 'r9', value: value });
            } else if (value === 'r10') {
                tokens.push({ type: 'r10', value: value });
            } else if (value === 'r11') {
                tokens.push({ type: 'r11', value: value });
            } else if (value === 'r12') {
                tokens.push({ type: 'r12', value: value });
            } else if (value === 'r13') {
                tokens.push({ type: 'r13', value: value });
            } else if (value === 'r14') {
                tokens.push({ type: 'r14', value: value });
            } else if (value === 'r15') {
                tokens.push({ type: 'r15', value: value });
            } else if (value === 'eax') {
                tokens.push({ type: 'eax', value: value });
            } else if (value === 'ebx') {
                tokens.push({ type: 'ebx', value: value });
            } else if (value === 'ecx') {
                tokens.push({ type: 'ecx', value: value });
            } else if (value === 'edx') {
                tokens.push({ type: 'edx', value: value });
            } else if (value === 'esp') {
                tokens.push({ type: 'esp', value: value });
            } else if (value === 'esi') {
                tokens.push({ type: 'esi', value: value });
            } else if (value === 'edi') {
                tokens.push({ type: 'edi', value: value });
            } else if (value === 'r8d') {
                tokens.push({ type: 'r8d', value: value });
            } else if (value === 'r9d') {
                tokens.push({ type: 'r9d', value: value });
            } else if (value === 'r10d') {
                tokens.push({ type: 'r10d', value: value });
            } else if (value === 'r11d') {
                tokens.push({ type: 'r11d', value: value });
            } else if (value === 'r12d') {
                tokens.push({ type: 'r12d', value: value });
            } else if (value === 'r13d') {
                tokens.push({ type: 'r13d', value: value });
            } else if (value === 'r14d') {
                tokens.push({ type: 'r14d', value: value });
            } else if (value === 'r15d') {
                tokens.push({ type: 'r15d', value: value });
            } else if (value === 'ax') {
                tokens.push({ type: 'ax', value: value });
            } else if (value === 'bx') {
                tokens.push({ type: 'bx', value: value });
            } else if (value === 'cx') {
                tokens.push({ type: 'cx', value: value });
            } else if (value === 'dx') {
                tokens.push({ type: 'dx', value: value });
            } else if (value === 'sp') {
                tokens.push({ type: 'sp', value: value });
            } else if (value === 'bp') {
                tokens.push({ type: 'bp', value: value });
            } else if (value === 'si') {
                tokens.push({ type: 'si', value: value });
            } else if (value === 'di') {
                tokens.push({ type: 'di', value: value });
            } else if (value === 'r8w') {
                tokens.push({ type: 'r8w', value: value });
            } else if (value === 'r9w') {
                tokens.push({ type: 'r9w', value: value });
            } else if (value === 'r10w') {
                tokens.push({ type: 'r10w', value: value });
            } else if (value === 'r11w') {
                tokens.push({ type: 'r11w', value: value });
            } else if (value === 'r12w') {
                tokens.push({ type: 'r12w', value: value });
            } else if (value === 'r13w') {
                tokens.push({ type: 'r13w', value: value });
            } else if (value === 'r14w') {
                tokens.push({ type: 'r14w', value: value });
            } else if (value === 'r15w') {
                tokens.push({ type: 'r15w', value: value });
            } else if (value === 'al') {
                tokens.push({ type: 'al', value: value });
            } else if (value === 'bl') {
                tokens.push({ type: 'bl', value: value });
            } else if (value === 'cl') {
                tokens.push({ type: 'cl', value: value });
            } else if (value === 'dl') {
                tokens.push({ type: 'dl', value: value });
            } else if (value === 'ah') {
                tokens.push({ type: 'ah', value: value });
            } else if (value === 'bh') {
                tokens.push({ type: 'bh', value: value });
            } else if (value === 'ch') {
                tokens.push({ type: 'ch', value: value });
            } else if (value === 'dh') {
                tokens.push({ type: 'dh', value: value });
            } else if (value === 'spl') {
                tokens.push({ type: 'spl', value: value });
            } else if (value === 'bpl') {
                tokens.push({ type: 'bpl', value: value });
            } else if (value === 'sil') {
                tokens.push({ type: 'sil', value: value });
            } else if (value === 'dil') {
                tokens.push({ type: 'dil', value: value });
            } else if (value === 'r8b') {
                tokens.push({ type: 'r8b', value: value });
            } else if (value === 'r9b') {
                tokens.push({ type: 'r9b', value: value });
            } else if (value === 'r10b') {
                tokens.push({ type: 'r10b', value: value });
            } else if (value === 'r11b') {
                tokens.push({ type: 'r11b', value: value });
            } else if (value === 'r12b') {
                tokens.push({ type: 'r12b', value: value });
            } else if (value === 'r13b') {
                tokens.push({ type: 'r13b', value: value });
            } else if (value === 'r14b') {
                tokens.push({ type: 'r14b', value: value });
            } else if (value === 'r15b') {
                tokens.push({ type: 'r15b', value: value });
            } else if (value === 'cs') {
                tokens.push({ type: 'cs', value: value });
            } else if (value === 'ds') {
                tokens.push({ type: 'ds', value: value });
            } else if (value === 'es') {
                tokens.push({ type: 'es', value: value });
            } else if (value === 'fs') {
                tokens.push({ type: 'fs', value: value });
            } else if (value === 'gs') {
                tokens.push({ type: 'gs', value: value });
            } else if (value === 'ss') {
                tokens.push({ type: 'ss', value: value });
            } else if (value === 'rip') {
                tokens.push({ type: 'rip', value: value });
            } else if (value === 'eip') {
                tokens.push({ type: 'eip', value: value });
            } else if (value === 'ip') {
                tokens.push({ type: 'ip', value: value });
            } else if (value === 'rflags') {
                tokens.push({ type: 'rflags', value: value });
            } else if (value === 'eflags') {
                tokens.push({ type: 'eflags', value: value });
            } else if (value === 'flags') {
                tokens.push({ type: 'flags', value: value });
            }
            //ARM register names
            else if (value === 'x0') {
                tokens.push({ type: 'x0', value: value });
            } else if (value === 'x1') {
                tokens.push({ type: 'x1', value: value });
            } else if (value === 'x2') {
                tokens.push({ type: 'x2', value: value });
            } else if (value === 'x3') {
                tokens.push({ type: 'x3', value: value });
            } else if (value === 'x4') {
                tokens.push({ type: 'x4', value: value });
            } else if (value === 'x5') {
                tokens.push({ type: 'x5', value: value });
            } else if (value === 'x6') {
                tokens.push({ type: 'x6', value: value });
            } else if (value === 'x7') {
                tokens.push({ type: 'x7', value: value });
            } else if (value === 'x8') {
                tokens.push({ type: 'x8', value: value });
            } else if (value === 'x9') {
                tokens.push({ type: 'x9', value: value });
            } else if (value === 'x10') {
                tokens.push({ type: 'x10', value: value });
            } else if (value === 'x11') {
                tokens.push({ type: 'x11', value: value });
            } else if (value === 'x12') {
                tokens.push({ type: 'x12', value: value });
            } else if (value === 'x13') {
                tokens.push({ type: 'x13', value: value });
            } else if (value === 'x14') {
                tokens.push({ type: 'x14', value: value });
            } else if (value === 'x15') {
                tokens.push({ type: 'x15', value: value });
            } else if (value === 'x16') {
                tokens.push({ type: 'x16', value: value });
            } else if (value === 'x17') {
                tokens.push({ type: 'x17', value: value });
            } else if (value === 'x18') {
                tokens.push({ type: 'x18', value: value });
            } else if (value === 'x19') {
                tokens.push({ type: 'x19', value: value });
            } else if (value === 'x20') {
                tokens.push({ type: 'x20', value: value });
            } else if (value === 'x21') {
                tokens.push({ type: 'x21', value: value });
            } else if (value === 'x22') {
                tokens.push({ type: 'x22', value: value });
            } else if (value === 'x23') {
                tokens.push({ type: 'x23', value: value });
            } else if (value === 'x24') {
                tokens.push({ type: 'x24', value: value });
            } else if (value === 'x25') {
                tokens.push({ type: 'x25', value: value });
            } else if (value === 'x26') {
                tokens.push({ type: 'x26', value: value });
            } else if (value === 'x27') {
                tokens.push({ type: 'x27', value: value });
            } else if (value === 'x28') {
                tokens.push({ type: 'x28', value: value });
            } else if (value === 'x29') {
                tokens.push({ type: 'x29', value: value });
            } else if (value === 'x30') {
                tokens.push({ type: 'x30', value: value });
            } else if (value === 'w0') {
                tokens.push({ type: 'w0', value: value });
            } else if (value === 'w1') {
                tokens.push({ type: 'w1', value: value });
            } else if (value === 'w2') {
                tokens.push({ type: 'w2', value: value });
            } else if (value === 'w3') {
                tokens.push({ type: 'w3', value: value });
            } else if (value === 'w4') {
                tokens.push({ type: 'w4', value: value });
            } else if (value === 'w5') {
                tokens.push({ type: 'w5', value: value });
            } else if (value === 'w6') {
                tokens.push({ type: 'w6', value: value });
            } else if (value === 'w7') {
                tokens.push({ type: 'x7', value: value });
            } else if (value === 'w8') {
                tokens.push({ type: 'w8', value: value });
            } else if (value === 'w9') {
                tokens.push({ type: 'w9', value: value });
            } else if (value === 'w10') {
                tokens.push({ type: 'w10', value: value });
            } else if (value === 'w11') {
                tokens.push({ type: 'w11', value: value });
            } else if (value === 'w12') {
                tokens.push({ type: 'w12', value: value });
            } else if (value === 'w13') {
                tokens.push({ type: 'w13', value: value });
            } else if (value === 'w14') {
                tokens.push({ type: 'w14', value: value });
            } else if (value === 'w15') {
                tokens.push({ type: 'w15', value: value });
            } else if (value === 'w16') {
                tokens.push({ type: 'w16', value: value });
            } else if (value === 'w17') {
                tokens.push({ type: 'w17', value: value });
            } else if (value === 'w18') {
                tokens.push({ type: 'w18', value: value });
            } else if (value === 'w19') {
                tokens.push({ type: 'w19', value: value });
            } else if (value === 'w20') {
                tokens.push({ type: 'w20', value: value });
            } else if (value === 'w21') {
                tokens.push({ type: 'w21', value: value });
            } else if (value === 'w22') {
                tokens.push({ type: 'w22', value: value });
            } else if (value === 'w23') {
                tokens.push({ type: 'w23', value: value });
            } else if (value === 'w24') {
                tokens.push({ type: 'w24', value: value });
            } else if (value === 'w25') {
                tokens.push({ type: 'w25', value: value });
            } else if (value === 'w26') {
                tokens.push({ type: 'w26', value: value });
            } else if (value === 'w27') {
                tokens.push({ type: 'w27', value: value });
            } else if (value === 'w28') {
                tokens.push({ type: 'w28', value: value });
            } else if (value === 'w29') {
                tokens.push({ type: 'w29', value: value });
            } else if (value === 'w30') {
                tokens.push({ type: 'w30', value: value });
            }
            //risc-v register names
            else if (value === 'x31') {
                tokens.push({ type: 'x31', value: value });
            } else if (value === 'f0') {
                tokens.push({ type: 'f0', value: value });
            } else if (value === 'f1') {
                tokens.push({ type: 'f1', value: value });
            } else if (value === 'f2') {
                tokens.push({ type: 'f2', value: value });
            } else if (value === 'f3') {
                tokens.push({ type: 'f3', value: value });
            } else if (value === 'f4') {
                tokens.push({ type: 'f4', value: value });
            } else if (value === 'f5') {
                tokens.push({ type: 'f5', value: value });
            } else if (value === 'f6') {
                tokens.push({ type: 'f6', value: value });
            } else if (value === 'f7') {
                tokens.push({ type: 'f7', value: value });
            } else if (value === 'f8') {
                tokens.push({ type: 'f8', value: value });
            } else if (value === 'f9') {
                tokens.push({ type: 'f9', value: value });
            } else if (value === 'f10') {
                tokens.push({ type: 'f10', value: value });
            } else if (value === 'f11') {
                tokens.push({ type: 'f11', value: value });
            } else if (value === 'f12') {
                tokens.push({ type: 'f12', value: value });
            } else if (value === 'f13') {
                tokens.push({ type: 'f13', value: value });
            } else if (value === 'f14') {
                tokens.push({ type: 'f14', value: value });
            } else if (value === 'f15') {
                tokens.push({ type: 'f15', value: value });
            } else if (value === 'f16') {
                tokens.push({ type: 'f16', value: value });
            } else if (value === 'f17') {
                tokens.push({ type: 'f17', value: value });
            } else if (value === 'f18') {
                tokens.push({ type: 'f18', value: value });
            } else if (value === 'f19') {
                tokens.push({ type: 'f19', value: value });
            } else if (value === 'f20') {
                tokens.push({ type: 'f20', value: value });
            } else if (value === 'f21') {
                tokens.push({ type: 'f21', value: value });
            } else if (value === 'f22') {
                tokens.push({ type: 'f22', value: value });
            } else if (value === 'f23') {
                tokens.push({ type: 'f23', value: value });
            } else if (value === 'f24') {
                tokens.push({ type: 'f24', value: value });
            } else if (value === 'f25') {
                tokens.push({ type: 'f25', value: value });
            } else if (value === 'f26') {
                tokens.push({ type: 'f26', value: value });
            } else if (value === 'f27') {
                tokens.push({ type: 'f27', value: value });
            } else if (value === 'f28') {
                tokens.push({ type: 'f28', value: value });
            } else if (value === 'f29') {
                tokens.push({ type: 'f29', value: value });
            } else if (value === 'f30') {
                tokens.push({ type: 'f30', value: value });
            } else if (value === 'f31') {
                tokens.push({ type: 'f31', value: value });
            } else if (value === 'd0') {
                tokens.push({ type: 'd0', value: value });
            } else if (value === 'd1') {
                tokens.push({ type: 'd1', value: value });
            } else if (value === 'd2') {
                tokens.push({ type: 'd2', value: value });
            } else if (value === 'd3') {
                tokens.push({ type: 'd3', value: value });
            } else if (value === 'd4') {
                tokens.push({ type: 'd4', value: value });
            } else if (value === 'd5') {
                tokens.push({ type: 'd5', value: value });
            } else if (value === 'd6') {
                tokens.push({ type: 'd6', value: value });
            } else if (value === 'd7') {
                tokens.push({ type: 'd7', value: value });
            } else if (value === 'd8') {
                tokens.push({ type: 'd8', value: value });
            } else if (value === 'd9') {
                tokens.push({ type: 'd9', value: value });
            } else if (value === 'd10') {
                tokens.push({ type: 'd10', value: value });
            } else if (value === 'd11') {
                tokens.push({ type: 'd11', value: value });
            } else if (value === 'd12') {
                tokens.push({ type: 'd12', value: value });
            } else if (value === 'd13') {
                tokens.push({ type: 'd13', value: value });
            } else if (value === 'd14') {
                tokens.push({ type: 'd14', value: value });
            } else if (value === 'd15') {
                tokens.push({ type: 'd15', value: value });
            } else if (value === 'd16') {
                tokens.push({ type: 'd16', value: value });
            } else if (value === 'd17') {
                tokens.push({ type: 'd17', value: value });
            } else if (value === 'd18') {
                tokens.push({ type: 'd18', value: value });
            } else if (value === 'd19') {
                tokens.push({ type: 'd19', value: value });
            } else if (value === 'd20') {
                tokens.push({ type: 'd20', value: value });
            } else if (value === 'd21') {
                tokens.push({ type: 'd21', value: value });
            } else if (value === 'd22') {
                tokens.push({ type: 'd22', value: value });
            } else if (value === 'd23') {
                tokens.push({ type: 'd23', value: value });
            } else if (value === 'd24') {
                tokens.push({ type: 'd24', value: value });
            } else if (value === 'd25') {
                tokens.push({ type: 'd25', value: value });
            } else if (value === 'd26') {
                tokens.push({ type: 'd26', value: value });
            } else if (value === 'd27') {
                tokens.push({ type: 'd27', value: value });
            } else if (value === 'd28') {
                tokens.push({ type: 'd28', value: value });
            } else if (value === 'd29') {
                tokens.push({ type: 'd29', value: value });
            } else if (value === 'd30') {
                tokens.push({ type: 'd30', value: value });
            } else if (value === 'd31') {
                tokens.push({ type: 'd31', value: value });
            } else if (value === 'zero') {
                tokens.push({ type: 'zero', value: value });
            } else if (value === 'ra') {
                tokens.push({ type: 'ra', value: value });
            } else if (value === 'sp') {
                tokens.push({ type: 'sp', value: value });
            } else if (value === 'gp') {
                tokens.push({ type: 'gp', value: value });
            } else if (value === 'tp') {
                tokens.push({ type: 'tp', value: value });
            } else if (value === 't0') {
                tokens.push({ type: 't0', value: value });
            } else if (value === 't1') {
                tokens.push({ type: 't1', value: value });
            } else if (value === 't2') {
                tokens.push({ type: 't2', value: value });
            } else if (value === 's0') {
                tokens.push({ type: 's0', value: value });
            } else if (value === 'fp') {
                tokens.push({ type: 'fp', value: value });
            } else if (value === 's1') {
                tokens.push({ type: 's1', value: value });
            } else if (value === 'a0') {
                tokens.push({ type: 'a0', value: value });
            } else if (value === 'a1') {
                tokens.push({ type: 'a1', value: value });
            } else if (value === 'a2') {
                tokens.push({ type: 'a2', value: value });
            } else if (value === 'a3') {
                tokens.push({ type: 'a3', value: value });
            } else if (value === 'a4') {
                tokens.push({ type: 'a4', value: value });
            } else if (value === 'a5') {
                tokens.push({ type: 'a5', value: value });
            } else if (value === 'a6') {
                tokens.push({ type: 'a6', value: value });
            } else if (value === 'a7') {
                tokens.push({ type: 'a7', value: value });
            } else if (value === 's2') {
                tokens.push({ type: 's2', value: value });
            } else if (value === 's3') {
                tokens.push({ type: 's3', value: value });
            } else if (value === 's4') {
                tokens.push({ type: 's4', value: value });
            } else if (value === 's5') {
                tokens.push({ type: 's5', value: value });
            } else if (value === 's6') {
                tokens.push({ type: 's6', value: value });
            } else if (value === 's7') {
                tokens.push({ type: 's7', value: value });
            } else if (value === 's8') {
                tokens.push({ type: 's8', value: value });
            } else if (value === 's9') {
                tokens.push({ type: 's9', value: value });
            } else if (value === 's10') {
                tokens.push({ type: 's10', value: value });
            } else if (value === 's11') {
                tokens.push({ type: 's11', value: value });
            } else if (value === 't3') {
                tokens.push({ type: 't3', value: value });
            } else if (value === 't4') {
                tokens.push({ type: 't4', value: value });
            } else if (value === 't5') {
                tokens.push({ type: 't5', value: value });
            } else if (value === 't6') {
                tokens.push({ type: 't6', value: value });
            }
            //Low-lvl and bios specific operations
            else if (value === 'out') {
                tokens.push({ type: 'out', value: value });
            } else if (value === 'in') {
                tokens.push({ type: 'in', value: value });
            } else if (value === 'cli') {
                tokens.push({ type: 'cli', value: value });
            } else if (value === 'sti') {
                tokens.push({ type: 'sti', value: value });
            } else if (value === 'lidt') {
                tokens.push({ type: 'lidt', value: value });
            } else if (value === 'lgdt') {
                tokens.push({ type: 'lgdt', value: value });
            } else if (value === 'smsw') {
                tokens.push({ type: 'smsw', value: value });
            } else if (value === 'lmsw') {
                tokens.push({ type: 'lmsw', value: value });
            } else if (value === 'invlpg') {
                tokens.push({ type: 'invlpg', value: value });
            } else if (value === 'wbinvd') {
                tokens.push({ type: 'wbinvd', value: value });
            } else if (value === 'rdmsr') {
                tokens.push({ type: 'rdmsr', value: value });
            } else if (value === 'wrmsr') {
                tokens.push({ type: 'wrmsr', value: value });
            } else if (value === 'rdtsr') {
                tokens.push({ type: 'rdtsr', value: value });
            } else if (value === 'cpuid') {
                tokens.push({ type: 'cpuid', value: value });
            } else if (value === 'iret') {
                tokens.push({ type: 'iret', value: value });
            } else if (value === 'pushfd') {
                tokens.push({ type: 'pushfd', value: value });
            } else if (value === 'popfd') {
                tokens.push({ type: 'popfd', value: value });
            } else if (value === 'lahf') {
                tokens.push({ type: 'lahf', value: value });
            } else if (value === 'sahf') {
                tokens.push({ type: 'sahf', value: value });
            }
            //UEFI / protocol helpers
            else if (value === 'stall') {
                tokens.push({ type: 'stall', value: value });
            } else if (value === 'reset') {
                tokens.push({ type: 'reset', value: value });
            } else if (value === 'allocate_pages') {
                tokens.push({ type: 'allocate_pages', value: value });
            } else if (value === 'free_pages') {
                tokens.push({ type: 'free_pages', value: value });
            } else if (value === 'get_memory_map') {
                tokens.push({ type: 'get_memory_map', value: value });
            } else if (value === 'allocate_pool') {
                tokens.push({ type: 'allocate_pool', value: value });
            } else if (value === 'free_pool') {
                tokens.push({ type: 'free_pool', value: value });
            } else if (value === 'set_watchdog_timer') {
                tokens.push({ type: 'set_watchdog_timer', value: value });
            } else if (value === 'connect_controller') {
                tokens.push({ type: 'connect_controller', value: value });
            } else if (value === 'disconnect_controller') {
                tokens.push({ type: 'disconnect_controller', value: value });
            } else if (value === 'open_protocol') {
                tokens.push({ type: 'close_protocol', value: value });
            } else if (value === 'locate_handle') {
                tokens.push({ type: 'locate_handle', value: value });
            } else if (value === 'locate_device_path') {
                tokens.push({ type: 'locate_device_path', value: value });
            } else if (value === 'install_protocol_interface') {
                tokens.push({ type: 'install_protocol_interface', value: value });
            } else if (value === 'reinstall_protocol_interface') {
                tokens.push({ type: 'reinstall_protocol_interface', value: value });
            } else if (value === 'uninstall_protocol_interface') {
                tokens.push({ type: 'uninstall_protocol_interface', value: value });
            } else if (value === 'handle_protocol') {
                tokens.push({ type: 'handle_protocol', value: value });
            } else if (value === 'register_protocol_notify') {
                tokens.push({ type: 'register_protocol_notify', value: value });
            } else if (value === 'locate_handle_buffer') {
                tokens.push({ type: 'locate_handle_buffer', value: value });
            }
            // high-lvl operations
            else if (value === 'print') {
                tokens.push({ type: 'print', value: value });
            } else if (value === 'call') {
                tokens.push({ type: 'call', value: value });
            } else if (value === 'import') {
                tokens.push({ type: 'import', value: value });
            } else if (value === 'export') {
                tokens.push({ type: 'export', value: value });
            } else if (value === 'return') {
                tokens.push({ type: 'return', value: value });
            } else if (value === 'break') {
                tokens.push({ type: 'break', value: value });
            } else if (value === 'continue') {
                tokens.push({ type: 'continue', value: value });
            } else if (value === 'while') {
                tokens.push({ type: 'while', value: value });
            } else if (value === 'do') {
                tokens.push({ type: 'do', value: value });
            } else if (value === 'for') {
                tokens.push({ type: 'for', value: value });
            } else if (value === 'input') {
                tokens.push({ type: 'input', value: value });
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