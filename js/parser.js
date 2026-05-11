import { InstructionNode, RegisterNode, ProgramNode } from "./ast";

export function parser(tokens) {
    let current = 0;

    const directiveTokens = new Set(['arch', 'format', 'entry']);
    const instructionTokens = new Set([
        'mov', 'add', 'sub', 'mul', 'div', 'sqr', 'pow', 'cmp', 'jmp', 'jnz',
        'inc', 'dec', 'xor', 'and', 'or', 'not', 'shl', 'shr', 'sar', 'rol', 'ror',
        'ret', 'int', 'syscall',
        'ldr', 'str', 'orr', 'eor', 'bic', 'lsl', 'lsr', 'asr', 'tst', 'b', 'bl_op',
        'bx_op', 'adr', 'sdiv', 'udiv', 'bfi', 'ubfx', 'cbz', 'cbnz',
        'lui', 'auipc', 'lw', 'sw', 'ld', 'sd', 'addi', 'slt', 'slti', 'jal', 'jalr',
        'beq', 'bne', 'blt', 'bge',
        'out', 'in', 'cli', 'sti', 'lidt', 'lgdt', 'smsw', 'lmsw', 'invlpg', 'wbinvd',
        'rdmsr', 'wrmsr', 'rdtsr', 'cpuid', 'iret', 'pushfd', 'popfd', 'lahf', 'sahf',
        'stall', 'reset', 'allocate_pages', 'free_pages', 'get_memory_map',
        'allocate_pool', 'free_pool', 'set_watchdog_timer', 'connect_controller',
        'disconnect_controller', 'open_protocol', 'locate_handle',
        'locate_device_path', 'install_protocol_interface',
        'reinstall_protocol_interface', 'uninstall_protocol_interface',
        'handle_protocol', 'register_protocol_notify', 'locate_handle_buffer',
        'print', 'call', 'import', 'export', 'return', 'break', 'continue'
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

    function peek(offset = 0) {
        return tokens[current + offset];
    }

    function advance() {
        return tokens[current++];
    }

    function match(type) {
        if (peek() && peek().type === type) {
            current++;
            return true;
        }
        return false;
    }

    function parseOperand() {
        const token = peek();
        if (!token) {
            throw new TypeError('Unexpected end of input');
        }
        if (token.type === 'number') {
            advance();
            return { type: 'NumberLiteral', value: token.value };
        }
        if (token.type === 'string') {
            advance();
            return { type: 'StringLiteral', value: token.value };
        }

        if (registerTokens.has(token.type)) {
            advanced();
            return new RegisterNode(token.value);
        }

        if (token.type === 'name') {
            advance();
            return {
                type: 'Identifier',
                name: token.value
            }
        }
        throw new TypeError(`Unexpected token in operand: ${token.type} (value: ${token.value})`);
    }

    function parseDirective() {
        const directive = advance();
        const valueToken = peek();
        if (!valueToken) {
            throw new TypeError('Expected directive value');
        }
        advance();
        match('semicolon');
        return {
            type: 'Directive',
            name: directive.type.toUpperCase(),
            value: valueToken.value,
        };
    }

    function parseDeclare() {
        advance();
        const idToken = peek();
        if (!idToken) {
            throw new TypeError('Expected identifier after declare');
        }
        advance();
        const typeToken = peek();
        if (!typeToken) {
            throw new TypeError('Expected type after identifier');
        }
        advance();
        let isArray = false;
        if (match('lbracket')) {
            isArray = true;
            while (peek() && peek().type !== 'rbracket') {
                advance();
            }
            if (!match('rbracket')) {
                throw new TypeError('Expected closing bracket');
            }
        }
        let init = null;
        if (match('assign')) {
            init = parseOperand();
        }
        match('semicolon');
        return {
            type: 'Declare',
            id: { type: 'Identifier', name: idToken.value },
            varType: typeToken.value,
            isArray,
            init,
        };
    }

    function parseLabel() {
        const nameToken = advance();
        if (!match('colon')) {
            throw new TypeError('Expected colon after label');
        }
        return { type: 'Label', name: nameToken.value };
    }

    function parseInstruction() {
        const instr = advance();
        const args = [];
        while (peek() && peek().type !== 'semicolon') {
            if (match('comma')) {
                continue;
            }
            args.push(parseOperand());
        }
        match('semicolon');
        return new InstructionNode(instr.value, args);
    }

    function walk() {
        let token = tokens[current];

        if (!token) {
            throw new TypeError('Unexpected end of input');
        }

        if (directiveTokens.has(token.type)) {
            return parseDirective();
        }

        if (token.type === 'declare') {
            return parseDeclare();
        }

        if (token.type === 'name' && peek(1) && peek(1).type === 'colon') {
            return parseLabel();
        }

        if (instructionTokens.has(token.type)) {
            return parseInstruction();
        }

        if (token.type === 'number') {
            current++;

            return {
                type: 'NumberLiteral',
                value: token.value,
            };
        }

        if (token.type === 'string') {
            current++;

            return {
                type: 'StringLiteral',
                value: token.value
            };
        }

        if (token.type === 'name') {
            current++;

            return {
                type: 'Identifier',
                name: token.value,
            };
        }

        throw new TypeError('Unexpected token: ' + token.type);
    }

    let ast = {
        type: 'Program',
        body: [],
    };

    while (current < tokens.length) {
        ast.body.push(walk());
    }

    return ast;
}