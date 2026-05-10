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
        'rax', 'rbx', 'rcx', 'rdx', 'rsp', 'sbp', 'rsi',
    ])

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
        if (registerTokens.has(token.type) || token.type === 'name') {
            advance();
            return {
                type: registerTokens.has(token.type) ? 'Register' : 'Identifier',
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
        return {
            type: 'Instruction',
            name: instr.value.toUpperCase(),
            args,
        };
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