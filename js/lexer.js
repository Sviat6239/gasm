const range = (prefix, from, to) => Array.from({ length: to - from + 1 }, (_, index) => `${prefix}${from + index}`);

const keywordSpecialTypes = new Map([
    ['function', 'endf'],
    ['uint64', 'int64'],
]);

const sharedKeywordWords = [
    'format', 'win_32', 'win_64', 'elf_32', 'elf_64', 'bin', 'efi_32', 'efi_64',
    'arch', 'x86_16', 'x86_32', 'x86_64', 'entry', 'declare',
    'db', 'dw', 'dd', 'dq', 'rb', 'rw', 'rd', 'rq', 'int8', 'int16', 'int32', 'int64',
    'uint8', 'uint16', 'uint32', 'float', 'double', 'char',
    'struct', 'ends', 'macro', 'endm', 'if', 'else', 'switch', 'case', 'while', 'do',
    'for', 'input',
    'mov', 'add', 'sub', 'mul', 'div', 'sqr', 'pow', 'cmp', 'jmp', 'jnz', 'inc', 'dec',
    'xor', 'and', 'or', 'not', 'shl', 'shr', 'sar', 'rol', 'ror', 'ret', 'int', 'syscall',
    'ldr', 'str', 'orr', 'eor', 'bic', 'lsl', 'lsr', 'asr', 'tst', 'b', 'bl_op', 'bx_op',
    'adr', 'sdiv', 'udiv', 'bfi', 'ubfx', 'cbz', 'cbnz', 'lui', 'auipc', 'lw', 'sw', 'ld',
    'sd', 'addi', 'slt', 'slti', 'jal', 'jalr', 'li', 'la', 'ecall', 'beq', 'bne', 'blt',
    'bge', 'out', 'in', 'cli', 'sti', 'lidt', 'lgdt', 'smsw', 'lmsw', 'invlpg', 'wbinvd',
    'rdmsr', 'wrmsr', 'rdtsr', 'cpuid', 'iret', 'pushfd', 'popfd', 'lahf', 'sahf', 'stall',
    'reset', 'allocate_pages', 'free_pages', 'get_memory_map', 'allocate_pool', 'free_pool',
    'set_watchdog_timer', 'connect_controller', 'disconnect_controller', 'open_protocol',
    'locate_handle', 'locate_device_path', 'install_protocol_interface',
    'reinstall_protocol_interface', 'uninstall_protocol_interface', 'handle_protocol',
    'register_protocol_notify', 'locate_handle_buffer', 'print', 'call', 'import',
    'export', 'return', 'break', 'continue',
    'push', 'pop', 'lea', 'nop', 'xchg', 'xadd', 'bsf', 'bsr', 'bt', 'bts', 'btr', 'btc',
    'test', 'cmovz', 'cmovnz', 'cmova', 'cmovae', 'cmovb', 'cmovbe', 'cmovg', 'cmovge',
    'cmovl', 'cmovle', 'leave', 'enter', 'hlt', 'cld', 'std', 'stc', 'clc', 'cmc', 'rep',
    'repe', 'repne', 'stos', 'lods', 'movs', 'scas', 'cmps', 'imul', 'idiv', 'neg', 'adc',
    'sbb', 'fld', 'fst', 'fstp', 'fadd', 'fsub', 'fmul', 'fdiv', 'fsqrt', 'fabs', 'fchs',
    'fcom', 'movd', 'movq', 'movaps', 'movups', 'addps', 'subps', 'mulps', 'divps',
    'sqrtps', 'addpd', 'subpd', 'mulpd', 'divpd', 'sqrtpd', 'andps', 'orps', 'xorps',
    'vaddps', 'vsubps', 'vmulps', 'vdivps', 'vxorps', 'vandps', 'vorps', 'jz', 'je', 'jne',
    'ja', 'jae', 'jb', 'jbe', 'jg', 'jge', 'jl', 'jle', 'jo', 'jno', 'js', 'jns',
    'adds', 'subs', 'negs', 'adcs', 'sbc', 'sbcs', 'madd', 'msub', 'smull', 'umull',
    'smaddl', 'umaddl', 'ands', 'bics', 'mvn', 'ldrb', 'ldrh', 'ldrsw', 'ldp', 'stp',
    'strb', 'strh', 'bl', 'blr', 'br', 'tbz', 'tbnz', 'cmn', 'svc', 'hvc', 'smc', 'eret',
    'isb', 'dsb', 'dmb', 'msr', 'mrs', 'fcmp', 'fneg', 'fmov', 'sll', 'sltu', 'srl', 'sra',
    'sltiu', 'xori', 'ori', 'andi', 'slli', 'srli', 'srai', 'lb', 'lh', 'lbu', 'lhu', 'sb',
    'sh', 'bltu', 'bgeu', 'mulh', 'mulhsu', 'mulhu', 'divu', 'rem', 'remu', 'lr_w', 'sc_w',
    'amoswap_w', 'amoadd_w', 'amoxor_w', 'amoand_w', 'amoor_w', 'amomin_w', 'amomax_w',
    'amominu_w', 'amomaxu_w', 'csrrw', 'csrrs', 'csrrc', 'csrrwi', 'csrrsi', 'csrrci',
    'ebreak', 'c.add', 'c.addi', 'c.li', 'c.lui', 'c.mv', 'c.j', 'c.jal', 'c.beqz',
    'c.bnez', 'c.lw', 'c.sw', 'c.srli', 'c.srai', 'c.andi', 'c.sub', 'c.xor', 'c.or',
    'c.and'
];

const x86RegisterWords = [
    'rax', 'rbx', 'rcx', 'rdx', 'rsp', 'rbp', 'rsi', 'rdi',
    'r8', 'r9', 'r10', 'r11', 'r12', 'r13', 'r14', 'r15',
    'eax', 'ebx', 'ecx', 'edx', 'esp', 'ebp', 'esi', 'edi',
    'r8d', 'r9d', 'r10d', 'r11d', 'r12d', 'r13d', 'r14d', 'r15d',
    'ax', 'bx', 'cx', 'dx', 'sp', 'bp', 'si', 'di',
    'r8w', 'r9w', 'r10w', 'r11w', 'r12w', 'r13w', 'r14w', 'r15w',
    'al', 'bl', 'cl', 'dl', 'ah', 'bh', 'ch', 'dh',
    'spl', 'bpl', 'sil', 'dil',
    'r8b', 'r9b', 'r10b', 'r11b', 'r12b', 'r13b', 'r14b', 'r15b',
    'cs', 'ds', 'es', 'fs', 'gs', 'ss',
    'rip', 'eip', 'ip', 'rflags', 'eflags', 'flags'
];

const armRegisterWords = [
    ...range('x', 0, 30),
    ...range('w', 0, 30)
];

const riscvRegisterWords = [
    'x31',
    'zero', 'ra', 'sp', 'gp', 'tp', 't0', 't1', 't2', 's0', 'fp', 's1',
    'a0', 'a1', 'a2', 'a3', 'a4', 'a5', 'a6', 'a7',
    's2', 's3', 's4', 's5', 's6', 's7', 's8', 's9', 's10', 's11',
    't3', 't4', 't5', 't6',
    ...range('f', 0, 31),
    ...range('d', 0, 31),
    'ft0', 'ft1', 'ft2', 'ft3', 'ft4', 'ft5', 'ft6', 'ft7',
    'fs0', 'fs1', 'fa0', 'fa1', 'fa2', 'fa3', 'fa4', 'fa5', 'fa6', 'fa7',
    'fs2', 'fs3', 'fs4', 'fs5', 'fs6', 'fs7', 'fs8', 'fs9', 'fs10', 'fs11',
    'ft8', 'ft9', 'ft10', 'ft11',
    'pc'
];

const keywordWords = new Set([
    ...sharedKeywordWords,
    ...x86RegisterWords,
    ...armRegisterWords,
    ...riscvRegisterWords
]);

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

        const WORD_CHAR = /[a-z0-9_]/i;
        if (/[a-z]/i.test(char)) {
            let value = '';
            while (current < input.length && WORD_CHAR.test(char)) {
                value += char;
                char = input[++current];
            }

            if (value === 'c' && char === '.' && /[a-z]/i.test(input[current + 1] || '')) {
                value += char;
                char = input[++current];
                while (current < input.length && WORD_CHAR.test(char)) {
                    value += char;
                    char = input[++current];
                }
            }

            const specialType = keywordSpecialTypes.get(value);
            if (specialType) {
                tokens.push({ type: specialType, value });
            } else if (keywordWords.has(value)) {
                tokens.push({ type: value, value });
            } else {
                tokens.push({ type: 'name', value });
            }
            continue;
        }
        throw new TypeError('Unknown charecter' + char);
    }

    return tokens;
}