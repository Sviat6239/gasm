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
            } else if (value === '(') {
                tokens.push({ type: 'lparent', value: value });
            } else if (value === ')') {
                tokens.push({ type: 'rparent', value: value });
            } else if (value === '<') {
                tokens.push({ type: 'less', value: value });
            } else if (value === '>') {
                tokens.push({ type: 'greater', value: value });
            } else if (value === '<=') {
                tokens.push({ type: 'lessOrEqual', value: value });
            } else if (value === '>=') {
                tokens.push({ type: 'greaterOrEqual', value: value });
            }
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
            else {
                tokens.push({ type: 'name', value });
            }
            continue;
        }
        throw new TypeError('Unknown charecter' + char);
    }

    return tokens;
}