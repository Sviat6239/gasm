export function parser(tokens) {
    let current = 0;

    const directiveTokens = new Set(['arch', 'format', 'entry']);
    const instructionTokens = new Set([
        // Common / shared
        'mov', 'add', 'sub', 'mul', 'div', 'sqr', 'pow', 'cmp', 'jmp', 'jnz',
        'inc', 'dec', 'xor', 'and', 'or', 'not', 'shl', 'shr', 'sar', 'rol', 'ror',
        'ret', 'int', 'syscall',
        'ldr', 'str', 'orr', 'eor', 'bic', 'lsl', 'lsr', 'asr', 'tst', 'b', 'bl_op',
        'bx_op', 'adr', 'sdiv', 'udiv', 'bfi', 'ubfx', 'cbz', 'cbnz',
        'lui', 'auipc', 'lw', 'sw', 'ld', 'sd', 'addi', 'slt', 'slti', 'jal', 'jalr',
        'li', 'la', 'ecall',
        'beq', 'bne', 'blt', 'bge',
        'out', 'in', 'cli', 'sti', 'lidt', 'lgdt', 'smsw', 'lmsw', 'invlpg', 'wbinvd',
        'rdmsr', 'wrmsr', 'rdtsr', 'cpuid', 'iret', 'pushfd', 'popfd', 'lahf', 'sahf',
        'stall', 'reset', 'allocate_pages', 'free_pages', 'get_memory_map',
        'allocate_pool', 'free_pool', 'set_watchdog_timer', 'connect_controller',
        'disconnect_controller', 'open_protocol', 'locate_handle',
        'locate_device_path', 'install_protocol_interface',
        'reinstall_protocol_interface', 'uninstall_protocol_interface',
        'handle_protocol', 'register_protocol_notify', 'locate_handle_buffer',
        'print', 'call', 'import', 'export', 'return', 'break', 'continue',

        // X86 / X86-64 specific
        'push', 'pop', 'lea', 'nop', 'xchg', 'xadd', 'bsf', 'bsr', 'bt', 'bts', 'btr', 'btc',
        'test', 'cmovz', 'cmovnz', 'cmova', 'cmovae', 'cmovb', 'cmovbe', 'cmovg', 'cmovge',
        'cmovl', 'cmovle', 'leave', 'enter', 'hlt', 'cld', 'std', 'stc', 'clc', 'cmc',
        'rep', 'repe', 'repne', 'stos', 'lods', 'movs', 'scas', 'cmps',
        'imul', 'idiv', 'neg', 'adc', 'sbb',
        'fld', 'fst', 'fstp', 'fadd', 'fsub', 'fmul', 'fdiv', 'fsqrt', 'fabs', 'fchs', 'fcom',
        'movd', 'movq', 'movaps', 'movups', 'addps', 'subps', 'mulps', 'divps', 'sqrtps',
        'addpd', 'subpd', 'mulpd', 'divpd', 'sqrtpd', 'andps', 'orps', 'xorps',
        'vaddps', 'vsubps', 'vmulps', 'vdivps', 'vxorps', 'vandps', 'vorps',
        'jz', 'je', 'jne', 'ja', 'jae', 'jb', 'jbe', 'jg', 'jge', 'jl', 'jle', 'jo', 'jno', 'js', 'jns',

        // ARM64 / AArch64 specific
        'adds', 'subs', 'negs', 'adcs', 'sbc', 'sbcs', 'madd', 'msub', 'smull', 'umull',
        'smaddl', 'umaddl', 'ands', 'bics', 'mvn',
        'ldrb', 'ldrh', 'ldrsw', 'ldp', 'stp', 'strb', 'strh',
        'bl', 'blr', 'br', 'tbz', 'tbnz',
        'cmn', 'svc', 'hvc', 'smc', 'eret', 'isb', 'dsb', 'dmb', 'msr', 'mrs',
        'fcmp', 'fneg', 'fmov',

        // RISC-V RV32I/RV64I and extensions
        'sll', 'sltu', 'srl', 'sra', 'sltiu', 'xori', 'ori', 'andi', 'slli', 'srli', 'srai',
        'lb', 'lh', 'lbu', 'lhu', 'sb', 'sh', 'bltu', 'bgeu',
        'mulh', 'mulhsu', 'mulhu', 'divu', 'rem', 'remu',
        'lr_w', 'sc_w', 'amoswap_w', 'amoadd_w', 'amoxor_w', 'amoand_w', 'amoor_w',
        'amomin_w', 'amomax_w', 'amominu_w', 'amomaxu_w',
        'csrrw', 'csrrs', 'csrrc', 'csrrwi', 'csrrsi', 'csrrci',
        'c.add', 'c.addi', 'c.li', 'c.lui', 'c.mv', 'c.j', 'c.jal', 'c.beqz', 'c.bnez',
        'c.lw', 'c.sw', 'c.srli', 'c.srai', 'c.andi', 'c.sub', 'c.xor', 'c.or', 'c.and',
        'ebreak'
    ]);

    const registerTokens = new Set([
        // x86-64 General Purpose (64-bit)
        'rax', 'rbx', 'rcx', 'rdx', 'rsp', 'rbp', 'rsi', 'rdi',
        'r8', 'r9', 'r10', 'r11', 'r12', 'r13', 'r14', 'r15',

        // x86 (32-bit)
        'eax', 'ebx', 'ecx', 'edx', 'esp', 'ebp', 'esi', 'edi',
        'r8d', 'r9d', 'r10d', 'r11d', 'r12d', 'r13d', 'r14d', 'r15d',

        // x86 (16-bit)
        'ax', 'bx', 'cx', 'dx', 'sp', 'bp', 'si', 'di',
        'r8w', 'r9w', 'r10w', 'r11w', 'r12w', 'r13w', 'r14w', 'r15w',

        // x86 (8-bit)
        'al', 'bl', 'cl', 'dl', 'ah', 'bh', 'ch', 'dh',
        'spl', 'bpl', 'sil', 'dil',
        'r8b', 'r9b', 'r10b', 'r11b', 'r12b', 'r13b', 'r14b', 'r15b',

        // x86 Segment & Special
        'cs', 'ds', 'es', 'fs', 'gs', 'ss',
        'rip', 'eip', 'ip', 'rflags', 'eflags', 'flags',

        // ARM64 (64-bit X registers)
        'x0', 'x1', 'x2', 'x3', 'x4', 'x5', 'x6', 'x7', 'x8', 'x9', 'x10',
        'x11', 'x12', 'x13', 'x14', 'x15', 'x16', 'x17', 'x18', 'x19', 'x20',
        'x21', 'x22', 'x23', 'x24', 'x25', 'x26', 'x27', 'x28', 'x29', 'x30',

        // ARM64 (32-bit W registers)
        'w0', 'w1', 'w2', 'w3', 'w4', 'w5', 'w6', 'w7', 'w8', 'w9', 'w10',
        'w11', 'w12', 'w13', 'w14', 'w15', 'w16', 'w17', 'w18', 'w19', 'w20',
        'w21', 'w22', 'w23', 'w24', 'w25', 'w26', 'w27', 'w28', 'w29', 'w30',

        // RISC-V General Purpose (x0-x31), the same names with ARM
        'x31',

        // RISC-V Integer ABI Names
        'zero', 'ra', 'sp', 'gp', 'tp', 't0', 't1', 't2', 's0', 'fp', 's1',
        'a0', 'a1', 'a2', 'a3', 'a4', 'a5', 'a6', 'a7',
        's2', 's3', 's4', 's5', 's6', 's7', 's8', 's9', 's10', 's11',
        't3', 't4', 't5', 't6',

        // RISC-V Floating-Point (f0-f31 / d0-d31)
        'f0', 'f1', 'f2', 'f3', 'f4', 'f5', 'f6', 'f7', 'f8', 'f9', 'f10',
        'f11', 'f12', 'f13', 'f14', 'f15', 'f16', 'f17', 'f18', 'f19', 'f20',
        'f21', 'f22', 'f23', 'f24', 'f25', 'f26', 'f27', 'f28', 'f29', 'f30', 'f31',

        'd0', 'd1', 'd2', 'd3', 'd4', 'd5', 'd6', 'd7', 'd8', 'd9', 'd10',
        'd11', 'd12', 'd13', 'd14', 'd15', 'd16', 'd17', 'd18', 'd19', 'd20',
        'd21', 'd22', 'd23', 'd24', 'd25', 'd26', 'd27', 'd28', 'd29', 'd30', 'd31',

        // RISC-V Floating-Point ABI Names
        'ft0', 'ft1', 'ft2', 'ft3', 'ft4', 'ft5', 'ft6', 'ft7',
        'fs0', 'fs1', 'fa0', 'fa1', 'fa2', 'fa3', 'fa4', 'fa5', 'fa6', 'fa7',
        'fs2', 'fs3', 'fs4', 'fs5', 'fs6', 'fs7', 'fs8', 'fs9', 'fs10', 'fs11',
        'ft8', 'ft9', 'ft10', 'ft11',

        // System
        'pc'
    ]);

    function walk() {
        let token = tokens[current];

        if (token.type === 'equal') {
            if (tokens[++current].type == 'equal') {
                ++current;
                return {
                    type: 'ComparisonE',
                    value: token.value + token.value,
                };
            } else {
                return {
                    type: 'Equal',
                    value: token.value,
                }
            }
        }

        if (token.type === 'star') {
            current++;
            return {
                type: 'Pointer',
                value: token.value,
            };
        }

        if (token.type === 'hash') {
            current++;
            return {
                type: 'Comment',
                value: token.value,
            };
        }

        if (token.type === 'not') {
            if (tokens[++current].type === 'equal') {
                ++current;
                return {
                    type: 'ComparisonN',
                    value: token.value + "=",
                };
            } else {
                return {
                    type: 'Not',
                    value: token.value
                };
            }
        }

        if (token.type === 'plus') {
            if (tokens[++current].type === 'equal') {
                ++current;
                return {
                    type: 'IncByNum',
                    value: "+=",
                };
            } else if (tokens[current.type === 'plus']) {
                ++current;
                return {
                    type: 'IncByOne',
                    value: "++",
                };
            } else {
                return {
                    type: 'Plus',
                    value: "+",
                };
            }
        }

        if (token.type === 'minus') {
            if (tokens[++current].type === 'minus') {
                current++;
                return {
                    type: 'DecByOne',
                    value: "--",
                };
            } else if (tokens[current].type === 'equal') {
                current++;
                return {
                    type: 'DecByNum',
                    value: "-=",
                };
            } else if (tokens[current].type === 'greater') {
                current++;
                return {
                    type: 'Arrow',
                    value: "->",
                };
            } else {
                return {
                    type: 'Minus',
                    value: token.value,
                };
            }
        }



        throw new TypeError('Unexpected token: ' + token.type);

    }

    let ast = new ProgramNode();

    while (current < tokens.length) {
        ast.body.push(walk());
    }

    return ast;
}