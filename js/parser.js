import { tokenizer } from "./lexer";

export function parser(tokens) {
    let current = 0;

    function walk() {
        let token = tokens[current];

        if (token.type === 'number') {
            current++;

            return {
                type: 'NumberLiteral',
                value: token.value,
            };
        }

        if (token.type === 'format') {
            current++;

            return {
                type: 'FORMAT',
                value: token.value,
            };
        }

        if (token.type === 'win_32') {
            current++;

            return {
                type: 'WIN_32',
                value: token.value,
            };
        }

        if (token.type === 'win_64') {
            current++;

            return {
                type: 'WIN_64',
                value: token.value,
            };
        }

        if (token.type === 'elf_32') {
            current++;

            return {
                type: 'ELF_32',
                value: token.value,
            };
        }

        if (token.type === 'elf_64') {
            current++;

            return {
                type: 'ELF_64',
                value: token.value,
            };
        }

        if (token.type === 'bin') {
            current++;

            return {
                type: 'BIN',
                value: token.value,
            };
        }

        if (token.type === 'efi_32') {
            current++;

            return {
                type: 'EFI_32',
                value: token.value,
            };
        }

        if (token.type === 'efi_64') {
            current++;

            return {
                type: 'EFI_64',
                value: token.value,
            };
        }

        if (token.type === 'arch') {
            current++;

            return {
                type: 'ARCH',
                value: token.value,
            };
        }

        if (token.type === 'x86_16') {
            current++;

            return {
                type: 'X86_16',
                value: token.value,
            };
        }

        if (token.type === 'x86_32') {
            current++;

            return {
                type: 'X86_32',
                value: token.value,
            };
        }

        if (token.type === 'x86_64') {
            current++;

            return {
                type: 'X86_64',
                value: token.value,
            };
        }

        if (token.type === 'entry') {
            current++;

            return {
                type: 'ENTRY',
                value: token.value,
            };
        }

        if (token.type === 'declare') {
            current++;

            return {
                type: 'DECLARE',
                value: token.value,
            };
        }

        if (token.type === 'db') {
            current++;

            return {
                type: 'DB',
                value: token.value,
            };
        }

        if (token.type === 'dw') {
            current++;

            return {
                type: 'DW',
                value: token.value,
            };
        }

        if (token.type === 'dd') {
            current++;

            return {
                type: 'DD',
                value: token.value,
            };
        }

        if (token.type === 'dq') {
            current++;

            return {
                type: 'DQ',
                value: token.value,
            };
        }

        if (token.type === 'rb') {
            current++;

            return {
                type: 'RB',
                value: token.value,
            };
        }

        if (token.type === 'rw') {
            current++;

            return {
                type: 'RW',
                value: token.value,
            };
        }

        if (token.type === 'rd') {
            current++;

            return {
                type: 'RD',
                value: token.value,
            };
        }

        if (token.type === 'rq') {
            current++;

            return {
                type: 'RQ',
                value: token.value,
            };
        }

        if (token.type === 'int8') {
            current++;

            return {
                type: 'INT8',
                value: token.value,
            };
        }

        if (token.type === 'int16') {
            current++;

            return {
                type: 'INT16',
                value: token.value,
            };
        }

        if (token.type === 'int32') {
            current++;

            return {
                type: 'INT32',
                value: token.value,
            };
        }

        if (token.type === 'int64') {
            current++;

            return {
                type: 'INT64',
                value: token.value,
            };
        }

        if (token.type === 'uint8') {
            current++;

            return {
                type: 'UINT8',
                value: token.value,
            };
        }

        if (token.type === 'uint16') {
            current++;

            return {
                type: 'UINT16',
                value: token.value,
            };
        }

        if (token.type === 'uint32') {
            current++;

            return {
                type: 'UINT32',
                value: token.value,
            };
        }

        if (token.type === 'uint64') {
            current++;

            return {
                type: 'UINT64',
                value: token.value,
            };
        }

        if (token.type === 'float') {
            current++;

            return {
                type: 'FLOAT',
                value: token.value,
            };
        }

        if (token.type === 'double') {
            current++;

            return {
                type: 'DOUBLE',
                value: token.value,
            };
        }

        if (token.type === 'char') {
            current++;

            return {
                type: 'CHAR',
                value: token.value,
            };
        }

        if (token.type === 'struct') {
            current++;

            return {
                type: 'STRUCT',
                value: token.value,
            };
        }

        if (token.type === 'ends') {
            current++;

            return {
                type: 'ENDS',
                value: token.value,
            };
        }

        if (token.type === 'macro') {
            current++;

            return {
                type: 'MACRO',
                value: token.value,
            };
        }

        if (token.type === 'endm') {
            current++;

            return {
                type: 'ENDM',
                value: token.value,
            };
        }

        if (token.type === 'function') {
            current++;

            return {
                type: 'FUNCTION',
                value: token.value,
            };
        }

        if (token.type === 'endf') {
            current++;

            return {
                type: 'ENDF',
                value: token.value,
            };
        }

        if (token.type === 'if') {
            current++;

            return {
                type: 'IF',
                value: token.value,
            };
        }

        if (token.type === 'else') {
            current++;

            return {
                type: 'ELSE',
                value: token.value,
            };
        }

        if (token.type === 'switch') {
            current++;

            return {
                type: 'SWITCH',
                value: token.value,
            };
        }

        if (token.type === 'case') {
            current++;

            return {
                type: 'CASE',
                value: token.value,
            };
        }

        if (token.type === 'assign') {
            current++;

            return {
                type: 'ASSIGN',
                value: token.value,
            };
        }

        if (token.type === 'semicolon') {
            current++;

            return {
                type: 'SEMICOLON',
                value: token.value,
            };
        }

        if (token.type === 'comma') {
            current++;

            return {
                type: 'COMMA',
                value: token.value,
            };
        }

        if (token.type === 'lbrace') {
            current++;

            return {
                type: 'LBRACE',
                value: token.value,
            };
        }

        if (token.type === 'rbrace') {
            current++;

            return {
                type: 'RBRACE',
                value: token.value,
            };
        }

        if (token.type === 'lbracket') {
            current++;

            return {
                type: 'LBRACKET',
                value: token.value,
            };
        }

        if (token.type === 'rbracket') {
            current++;

            return {
                type: 'RBRACKET',
                value: token.value,
            };
        }

        if (token.type === 'lparent') {
            current++;

            return {
                type: 'LPARENT',
                value: token.value,
            };
        }

        if (token.type === 'rparent') {
            current++;

            return {
                type: 'RPARENT',
                value: token.value,
            };
        }

        if (token.type === 'less') {
            current++;

            return {
                type: 'LESS',
                value: token.value,
            };
        }

        if (token.type === 'greater') {
            current++;

            return {
                type: 'GREATER',
                value: token.value,
            };
        }

        if (token.type === 'lessOrEqual') {
            current++;

            return {
                type: 'LESSOREQUAL',
                value: token.value,
            };
        }

        if (token.type === 'greaterOrEqual') {
            current++;

            return {
                type: 'GREATEROREQUAL',
                value: token.value,
            };
        }

        if (token.type === 'notEqual') {
            current++;

            return {
                type: 'NOTEQUAL',
                value: token.value,
            };
        }

        if (token.type === 'isEqual') {
            current++;

            return {
                type: 'ISEQUAL',
                value: token.value,
            };
        }

        if (token.type === 'dot') {
            current++;

            return {
                type: 'DOT',
                value: token.value,
            };
        }

        if (token.type === 'star') {
            current++;

            return {
                type: 'STAR',
                value: token.value,
            };
        }

        if (token.type === 'module') {
            current++;

            return {
                type: 'MODULE',
                value: token.value,
            };
        }

        if (token.type === 'ampersand') {
            current++;

            return {
                type: 'AMPERSAND',
                value: token.value,
            };
        }

        if (token.type === 'logical_and') {
            current++;

            return {
                type: 'LOGICAL_AND',
                value: token.value,
            };
        }

        if (token.type === 'logical_or') {
            current++;

            return {
                type: 'LOGICAL_OR',
                value: token.value,
            };
        }

        if (token.type === 'plus') {
            current++;

            return {
                type: 'PLUS',
                value: token.value,
            };
        }

        if (token.type === 'minus') {
            current++;

            return {
                type: 'MINUS',
                value: token.value,
            };
        }

        if (token.type === 'divide') {
            current++;

            return {
                type: 'DIVIDE',
                value: token.value,
            };
        }

        if (token.type === 'incremental') {
            current++;

            return {
                type: 'INCREMENTAL',
                value: token.value,
            };
        }

        if (token.type === 'decremental') {
            current++;

            return {
                type: 'DECREMENTAL',
                value: token.value,
            };
        }

        if (token.type === 'mov') {
            current++;

            return {
                type: 'MOV',
                value: token.value,
            };
        }

        if (token.type === 'add') {
            current++;

            return {
                type: 'ADD',
                value: token.value,
            };
        }

        if (token.type === 'sub') {
            current++;

            return {
                type: 'SUB',
                value: token.value,
            };
        }

        if (token.type === 'mul') {
            current++;

            return {
                type: 'MUL',
                value: token.value,
            };
        }

        if (token.type === 'div') {
            current++;

            return {
                type: 'DIV',
                value: token.value,
            };
        }

        if (token.type === 'sqr') {
            current++;

            return {
                type: 'SQR',
                value: token.value,
            };
        }

        if (token.type === 'pow') {
            current++;

            return {
                type: 'POW',
                value: token.value,
            };
        }

        if (token.type === 'cmp') {
            current++;

            return {
                type: 'CMP',
                value: token.value,
            };
        }

        if (token.type === 'jmp') {
            current++;

            return {
                type: 'JMP',
                value: token.value,
            };
        }

        if (token.type === 'jnz') {
            current++;

            return {
                type: 'JNZ',
                value: token.value,
            };
        }

        if (token.type === 'inc') {
            current++;

            return {
                type: 'INC',
                value: token.value,
            };
        }

        if (token.type === 'dec') {
            current++;

            return {
                type: 'DEC',
                value: token.value,
            };
        }

        if (token.type === 'xor') {
            current++;

            return {
                type: 'XOR',
                value: token.value,
            };
        }

        if (token.type === 'and') {
            current++;

            return {
                type: 'AND',
                value: token.value,
            };
        }

        if (token.type === 'or') {
            current++;

            return {
                type: 'OR',
                value: token.value,
            };
        }

        if (token.type === 'not') {
            current++;

            return {
                type: 'NOT',
                value: token.value,
            };
        }

        if (token.type === 'shl') {
            current++;

            return {
                type: 'SHL',
                value: token.value,
            };
        }

        if (token.type === 'sar') {
            current++;

            return {
                type: 'SAR',
                value: token.value,
            };
        }

        if (token.type === 'rol') {
            current++;

            return {
                type: 'ROL',
                value: token.value,
            };
        }

        if (token.type === 'ror') {
            current++;

            return {
                type: 'ROR',
                value: token.value,
            };
        }

        if (token.type === 'ret') {
            current++;

            return {
                type: 'RET',
                value: token.value,
            };
        }

        if (token.type === 'int') {
            current++;

            return {
                type: 'INT',
                value: token.value,
            };
        }

        if (token.type === 'syscall') {
            current++;

            return {
                type: 'SYSCALL',
                value: token.value,
            };
        }

        if (token.type === 'ldr') {
            current++;

            return {
                type: 'LDR',
                value: token.value,
            };
        }

        if (token.type === 'str') {
            current++;

            return {
                type: 'STR',
                value: token.value,
            };
        }

        if (token.type === 'orr') {
            current++;

            return {
                type: 'ORR',
                value: token.value,
            };
        }

        if (token.type === 'eor') {
            current++;

            return {
                type: 'EOR',
                value: token.value,
            };
        }

        if (token.type === 'bic') {
            current++;

            return {
                type: 'BIC',
                value: token.value,
            };
        }

        if (token.type === 'lsl') {
            current++;

            return {
                type: 'LSL',
                value: token.value,
            };
        }

        if (token.type === 'lsr') {
            current++;

            return {
                type: 'LSL',
                value: token.value,
            };
        }

        if (token.type === 'asr') {
            current++;

            return {
                type: 'ASR',
                value: token.value,
            };
        }

        if (token.type === 'tst') {
            current++;

            return {
                type: 'TST',
                value: token.value,
            };
        }

        if (token.type === 'b') {
            current++;

            return {
                type: 'B',
                value: token.value,
            };
        }

        if (token.type === 'bl_op') {
            current++;

            return {
                type: 'BL_OP',
                value: token.value,
            };
        }

        if (token.type === 'bx_op') {
            current++;

            return {
                type: 'BX_OP',
                value: token.value,
            };
        }

        if (token.type === 'adr') {
            current++;

            return {
                type: 'ADR',
                value: token.value,
            };
        }

        if (token.type === 'sdiv') {
            current++;

            return {
                type: 'SDIV',
                value: token.value,
            };
        }

        if (token.type === 'udiv') {
            current++;

            return {
                type: 'UDIV',
                value: token.value,
            };
        }

        if (token.type === 'bfi') {
            current++;

            return {
                type: 'BFI',
                value: token.value,
            };
        }

        if (token.type === 'ubfx') {
            current++;

            return {
                type: 'UBFX',
                value: token.value,
            };
        }

        if (token.type === 'cbz') {
            current++;

            return {
                type: 'CBZ',
                value: token.value,
            };
        }

        if (token.type === 'cbnz') {
            current++;

            return {
                type: 'CBNZ',
                value: token.value,
            };
        }

        if (token.type === 'lui') {
            current++;

            return {
                type: 'LUI',
                value: token.value,
            };
        }

        if (token.type === 'auipc') {
            current++;

            return {
                type: 'AUIPC',
                value: token.value,
            };
        }

        if (token.type === 'lw') {
            current++;

            return {
                type: 'LW',
                value: token.value,
            };
        }

        if (token.type === 'sw') {
            current++;

            return {
                type: 'SW',
                value: token.value,
            };
        }

        if (token.type === 'ld') {
            current++;

            return {
                type: 'LD',
                value: token.value,
            };
        }

        if (token.type === 'sd') {
            current++;

            return {
                type: 'SD',
                value: token.value,
            };
        }

        if (token.type === 'addi') {
            current++;

            return {
                type: 'ADDI',
                value: token.value,
            };
        }

        if (token.type === 'slt') {
            current++;

            return {
                type: 'SLT',
                value: token.value,
            };
        }

        if (token.type === 'slti') {
            current++;

            return {
                type: 'SLTI',
                value: token.value,
            };
        }

        if (token.type === 'jal') {
            current++;

            return {
                type: 'JAL',
                value: token.value,
            };
        }

        if (token.type === 'jalr') {
            current++;

            return {
                type: 'JALR',
                value: token.value,
            };
        }

        if (token.type === 'beq') {
            current++;

            return {
                type: 'BEQ',
                value: token.value,
            };
        }

        if (token.type === 'bne') {
            current++;

            return {
                type: 'BNE',
                value: token.value,
            };
        }

        if (token.type === 'blt') {
            current++;

            return {
                type: 'BLT',
                value: token.value,
            };
        }

        if (token.type === 'bge') {
            current++;

            return {
                type: 'BGE',
                value: token.value,
            };
        }

        ///

        if (token.type === 'rax') {
            current++;

            return {
                type: 'RAX',
                value: token.value,
            };
        }

        if (token.type === 'rbx') {
            current++;

            return {
                type: 'RBX',
                value: token.value,
            };
        }

        if (token.type === 'rcx') {
            current++;

            return {
                type: 'RCX',
                value: token.value,
            };
        }

        if (token.type === 'rdx') {
            current++;

            return {
                type: 'RDX',
                value: token.value,
            };
        }

        if (token.type === 'rsp') {
            current++;

            return {
                type: 'RSP',
                value: token.value,
            };
        }

        if (token.type === 'rbp') {
            current++;

            return {
                type: 'RBP',
                value: token.value,
            };
        }

        if (token.type === 'rsi') {
            current++;

            return {
                type: 'RSI',
                value: token.value,
            };
        }

        if (token.type === 'rdi') {
            current++;

            return {
                type: 'RDI',
                value: token.value,
            };
        }

        if (token.type === 'r8') {
            current++;

            return {
                type: 'R8',
                value: token.value,
            };
        }

        if (token.type === 'r9') {
            current++;

            return {
                type: 'R9',
                value: token.value,
            };
        }

        if (token.type === 'r10') {
            current++;

            return {
                type: 'R10',
                value: token.value,
            };
        }

        if (token.type === 'r11') {
            current++;

            return {
                type: 'R11',
                value: token.value,
            };
        }

        if (token.type === 'r12') {
            current++;

            return {
                type: 'R12',
                value: token.value,
            };
        }

        if (token.type === 'r13') {
            current++;

            return {
                type: 'R13',
                value: token.value,
            };
        }

        if (token.type === 'r14') {
            current++;

            return {
                type: 'R14',
                value: token.value,
            };
        }

        if (token.type === 'r15') {
            current++;

            return {
                type: 'R15',
                value: token.value,
            };
        }

        if (token.type === 'eax') {
            current++;

            return {
                type: 'EAX',
                value: token.value,
            };
        }

        if (token.type === 'ebx') {
            current++;

            return {
                type: 'EBX',
                value: token.value,
            };
        }

        if (token.type === 'ecx') {
            current++;

            return {
                type: 'ECX',
                value: token.value,
            };
        }

        if (token.type === 'edx') {
            current++;

            return {
                type: 'EDX',
                value: token.value,
            };
        }

        if (token.type === 'esp') {
            current++;

            return {
                type: 'ESP',
                value: token.value,
            };
        }

        if (token.type === 'esi') {
            current++;

            return {
                type: 'ESI',
                value: token.value,
            };
        }

        if (token.type === 'edi') {
            current++;

            return {
                type: 'EDI',
                value: token.value,
            };
        }

        if (token.type === 'r8d') {
            current++;

            return {
                type: 'R8D',
                value: token.value,
            };
        }

        if (token.type === 'r9d') {
            current++;

            return {
                type: 'R9D',
                value: token.value,
            };
        }

        if (token.type === 'r10d') {
            current++;

            return {
                type: 'R10D',
                value: token.value,
            };
        }

        if (token.type === 'r11d') {
            current++;

            return {
                type: 'R11D',
                value: token.value,
            };
        }

        if (token.type === 'r12d') {
            current++;

            return {
                type: 'R12D',
                value: token.value,
            };
        }

        if (token.type === 'r13d') {
            current++;

            return {
                type: 'R13D',
                value: token.value,
            };
        }

        if (token.type === 'r14d') {
            current++;

            return {
                type: 'R14D',
                value: token.value,
            };
        }

        if (token.type === 'r15d') {
            current++;

            return {
                type: 'R15D',
                value: token.value,
            };
        }

        if (token.type === 'ax') {
            current++;

            return {
                type: 'AX',
                value: token.value,
            };
        }

        if (token.type === 'bx') {
            current++;

            return {
                type: 'BX',
                value: token.value,
            };
        }

        if (token.type === 'cx') {
            current++;

            return {
                type: 'CX',
                value: token.value,
            };
        }

        if (token.type === 'dx') {
            current++;

            return {
                type: 'DX',
                value: token.value,
            };
        }

        if (token.type === 'sp') {
            current++;

            return {
                type: 'SP',
                value: token.value,
            };
        }

        if (token.type === 'bp') {
            current++;

            return {
                type: 'BP',
                value: token.value,
            };
        }

        if (token.type === 'si') {
            current++;

            return {
                type: 'SI',
                value: token.value,
            };
        }

        if (token.type === 'di') {
            current++;

            return {
                type: 'DI',
                value: token.value,
            };
        }

        if (token.type === 'r8w') {
            current++;

            return {
                type: 'R8W',
                value: token.value,
            };
        }

        if (token.type === 'r9w') {
            current++;

            return {
                type: 'R9W',
                value: token.value,
            };
        }

        if (token.type === 'r10w') {
            current++;

            return {
                type: 'R10W',
                value: token.value,
            };
        }

        if (token.type === 'r11w') {
            current++;

            return {
                type: 'R11W',
                value: token.value,
            };
        }

        if (token.type === 'r12w') {
            current++;

            return {
                type: 'R12W',
                value: token.value,
            };
        }

        if (token.type === 'r13w') {
            current++;

            return {
                type: 'R13W',
                value: token.value,
            };
        }

        if (token.type === 'r14w') {
            current++;

            return {
                type: 'R14W',
                value: token.value,
            };
        }

        if (token.type === 'r15w') {
            current++;

            return {
                type: 'R15W',
                value: token.value,
            };
        }

        if (token.type === 'al') {
            current++;

            return {
                type: 'AL',
                value: token.value,
            };
        }

        if (token.type === 'bl') {
            current++;

            return {
                type: 'BL',
                value: token.value,
            };
        }

        if (token.type === 'cl') {
            current++;

            return {
                type: 'CL',
                value: token.value,
            };
        }

        if (token.type === 'dl') {
            current++;

            return {
                type: 'DL',
                value: token.value,
            };
        }

        if (token.type === 'ah') {
            current++;

            return {
                type: 'AH',
                value: token.value,
            };
        }

        if (token.type === 'bh') {
            current++;

            return {
                type: 'BH',
                value: token.value,
            };
        }

        if (token.type === 'ch') {
            current++;

            return {
                type: 'CH',
                value: token.value,
            };
        }

        if (token.type === 'dh') {
            current++;

            return {
                type: 'DH',
                value: token.value,
            };
        }

        if (token.type === 'spl') {
            current++;

            return {
                type: 'SPL',
                value: token.value,
            };
        }

        if (token.type === 'bpl') {
            current++;

            return {
                type: 'BPL',
                value: token.value,
            };
        }

        if (token.type === 'sil') {
            current++;

            return {
                type: 'SIL',
                value: token.value,
            };
        }

        if (token.type === 'dil') {
            current++;

            return {
                type: 'DIL',
                value: token.value,
            };
        }

        if (token.type === 'r8b') {
            current++;

            return {
                type: 'R8B',
                value: token.value,
            };
        }

        if (token.type === 'r9b') {
            current++;

            return {
                type: 'R9B',
                value: token.value,
            };
        }

        if (token.type === 'r10b') {
            current++;

            return {
                type: 'R10B',
                value: token.value,
            };
        }

        if (token.type === 'r11b') {
            current++;

            return {
                type: 'R11B',
                value: token.value,
            };
        }

        if (token.type === 'r12b') {
            current++;

            return {
                type: 'R12B',
                value: token.value,
            };
        }

        if (token.type === 'r13b') {
            current++;

            return {
                type: 'R13B',
                value: token.value,
            };
        }

        if (token.type === 'r14b') {
            current++;

            return {
                type: 'R14B',
                value: token.value,
            };
        }

        if (token.type === 'r15b') {
            current++;

            return {
                type: 'R15B',
                value: token.value,
            };
        }

        if (token.type === 'cs') {
            current++;

            return {
                type: 'CS',
                value: token.value,
            };
        }

        if (token.type === 'ds') {
            current++;

            return {
                type: 'DS',
                value: token.value,
            };
        }

        if (token.type === 'es') {
            current++;

            return {
                type: 'ES',
                value: token.value,
            };
        }

        if (token.type === 'fs') {
            current++;

            return {
                type: 'FS',
                value: token.value,
            };
        }

        if (token.type === 'gs') {
            current++;

            return {
                type: 'GS',
                value: token.value,
            };
        }

        if (token.type === 'ss') {
            current++;

            return {
                type: 'SS',
                value: token.value,
            };
        }

        if (token.type === 'rip') {
            current++;

            return {
                type: 'RIP',
                value: token.value,
            };
        }

        if (token.type === 'eip') {
            current++;

            return {
                type: 'EIP',
                value: token.value,
            };
        }

        if (token.type === 'ip') {
            current++;

            return {
                type: 'IP',
                value: token.value,
            };
        }

        if (token.type === 'rflags') {
            current++;

            return {
                type: 'RFLAGS',
                value: token.value,
            };
        }

        if (token.type === 'eflags') {
            current++;

            return {
                type: 'EFLAGS',
                value: token.value,
            };
        }

        if (token.type === 'flags') {
            current++;

            return {
                type: 'FLAGS',
                value: token.value,
            };
        }

        if (token.type === 'x0') {
            current++;

            return {
                type: 'X0',
                value: token.value,
            };
        }

        if (token.type === 'x1') {
            current++;

            return {
                type: 'X1',
                value: token.value,
            };
        }

        if (token.type === 'x2') {
            current++;

            return {
                type: 'X2',
                value: token.value,
            };
        }

        if (token.type === 'x3') {
            current++;

            return {
                type: 'X3',
                value: token.value,
            };
        }

        if (token.type === 'x4') {
            current++;

            return {
                type: 'X4',
                value: token.value,
            };
        }

        if (token.type === 'x5') {
            current++;

            return {
                type: 'X5',
                value: token.value,
            };
        }

        if (token.type === 'x6') {
            current++;

            return {
                type: 'X6',
                value: token.value,
            };
        }

        if (token.type === 'x7') {
            current++;

            return {
                type: 'X7',
                value: token.value,
            };
        }

        if (token.type === 'x8') {
            current++;

            return {
                type: 'X8',
                value: token.value,
            };
        }

        if (token.type === 'x9') {
            current++;

            return {
                type: 'X9',
                value: token.value,
            };
        }

        if (token.type === 'x10') {
            current++;

            return {
                type: 'X10',
                value: token.value,
            };
        }

        if (token.type === 'x11') {
            current++;

            return {
                type: 'x11',
                value: token.value,
            };
        }

        if (token.type === 'x12') {
            current++;

            return {
                type: 'X12',
                value: token.value,
            };
        }

        if (token.type === 'x13') {
            current++;

            return {
                type: 'X13',
                value: token.value,
            };
        }

        if (token.type === 'x14') {
            current++;

            return {
                type: 'X14',
                value: token.value,
            };
        }

        if (token.type === 'x15') {
            current++;

            return {
                type: 'X15',
                value: token.value,
            };
        }

        if (token.type === 'x16') {
            current++;

            return {
                type: 'X16',
                value: token.value,
            };
        }

        if (token.type === 'x17') {
            current++;

            return {
                type: 'X17',
                value: token.value,
            };
        }

        if (token.type === 'x18') {
            current++;

            return {
                type: 'X18',
                value: token.value,
            };
        }

        if (token.type === 'x19') {
            current++;

            return {
                type: 'X19',
                value: token.value,
            };
        }

        if (token.type === 'x20') {
            current++;

            return {
                type: 'X20',
                value: token.value,
            };
        }

        if (token.type === 'x21') {
            current++;

            return {
                type: 'X21',
                value: token.value,
            };
        }

        if (token.type === 'x22') {
            current++;

            return {
                type: 'X22',
                value: token.value,
            };
        }

        if (token.type === 'x23') {
            current++;

            return {
                type: 'X23',
                value: token.value,
            };
        }

        if (token.type === 'x24') {
            current++;

            return {
                type: 'X24',
                value: token.value,
            };
        }

        if (token.type === 'x25') {
            current++;

            return {
                type: 'X25',
                value: token.value,
            };
        }

        if (token.type === 'x26') {
            current++;

            return {
                type: 'X26',
                value: token.value,
            };
        }

        if (token.type === 'x27') {
            current++;

            return {
                type: 'X27',
                value: token.value,
            };
        }

        if (token.type === 'x28') {
            current++;

            return {
                type: 'X28',
                value: token.value,
            };
        }

        if (token.type === 'x29') {
            current++;

            return {
                type: 'X29',
                value: token.value,
            };
        }

        if (token.type === 'x30') {
            current++;

            return {
                type: 'X30',
                value: token.value,
            };
        }

        if (token.type === 'w0') {
            current++;

            return {
                type: 'W0',
                value: token.value,
            };
        }

        if (token.type === 'w1') {
            current++;

            return {
                type: 'W1',
                value: token.value,
            };
        }

        if (token.type === 'w2') {
            current++;

            return {
                type: 'W2',
                value: token.value,
            };
        }

        if (token.type === 'w3') {
            current++;

            return {
                type: 'W3',
                value: token.value,
            };
        }

        if (token.type === 'w4') {
            current++;

            return {
                type: 'W4',
                value: token.value,
            };
        }

        if (token.type === 'w5') {
            current++;

            return {
                type: 'W5',
                value: token.value,
            };
        }

        if (token.type === 'w6') {
            current++;

            return {
                type: 'W6',
                value: token.value,
            };
        }

        if (token.type === 'w7') {
            current++;

            return {
                type: 'W7',
                value: token.value,
            };
        }

        if (token.type === 'w8') {
            current++;

            return {
                type: 'W8',
                value: token.value,
            };
        }

        if (token.type === 'w9') {
            current++;

            return {
                type: 'W9',
                value: token.value,
            };
        }

        if (token.type === 'w10') {
            current++;

            return {
                type: 'W10',
                value: token.value,
            };
        }

        if (token.type === 'w11') {
            current++;

            return {
                type: 'W11',
                value: token.value,
            };
        }

        if (token.type === 'w12') {
            current++;

            return {
                type: 'W12',
                value: token.value,
            };
        }

        if (token.type === 'w13') {
            current++;

            return {
                type: 'W13',
                value: token.value,
            };
        }

        if (token.type === 'w14') {
            current++;

            return {
                type: 'W14',
                value: token.value,
            };
        }

        if (token.type === 'w15') {
            current++;

            return {
                type: 'W15',
                value: token.value,
            };
        }

        if (token.type === 'w16') {
            current++;

            return {
                type: 'W16',
                value: token.value,
            };
        }

        if (token.type === 'w17') {
            current++;

            return {
                type: 'W17',
                value: token.value,
            };
        }

        if (token.type === 'w18') {
            current++;

            return {
                type: 'W18',
                value: token.value,
            };
        }

        if (token.type === 'w19') {
            current++;

            return {
                type: 'W19',
                value: token.value,
            };
        }

        if (token.type === 'w20') {
            current++;

            return {
                type: 'W20',
                value: token.value,
            };
        }

        if (token.type === 'w21') {
            current++;

            return {
                type: 'W21',
                value: token.value,
            };
        }

        if (token.type === 'w22') {
            current++;

            return {
                type: 'W22',
                value: token.value,
            };
        }

        if (token.type === 'w23') {
            current++;

            return {
                type: 'W23',
                value: token.value,
            };
        }

        if (token.type === 'w24') {
            current++;

            return {
                type: 'W24',
                value: token.value,
            };
        }

        if (token.type === 'w25') {
            current++;

            return {
                type: 'W25',
                value: token.value,
            };
        }

        if (token.type === 'w26') {
            current++;

            return {
                type: 'W26',
                value: token.value,
            };
        }

        if (token.type === 'w27') {
            current++;

            return {
                type: 'W27',
                value: token.value,
            };
        }

        if (token.type === 'w28') {
            current++;

            return {
                type: 'W28',
                value: token.value,
            };
        }

        if (token.type === 'w29') {
            current++;

            return {
                type: 'W29',
                value: token.value,
            };
        }

        if (token.type === 'w30') {
            current++;

            return {
                type: 'W30',
                value: token.value,
            };
        }

        if (token.type === 'out') {
            current++;

            return {
                type: 'OUT',
                value: token.value,
            };
        }

        if (token.type === 'in') {
            current++;

            return {
                type: 'IN',
                value: token.value,
            };
        }

        if (token.type === 'cli') {
            current++;

            return {
                type: 'CLI',
                value: token.value,
            };
        }

        if (token.type === 'sti') {
            current++;

            return {
                type: 'STI',
                value: token.value,
            };
        }

        if (token.type === 'lidt') {
            current++;

            return {
                type: 'LIDT',
                value: token.value,
            };
        }

        if (token.type === 'lgdt') {
            current++;

            return {
                type: 'LGDT',
                value: token.value,
            };
        }

        if (token.type === 'smsw') {
            current++;

            return {
                type: 'SMSW',
                value: token.value,
            };
        }

        if (token.type === 'lmsw') {
            current++;

            return {
                type: 'LMSW',
                value: token.value,
            };
        }

        if (token.type === 'invlpg') {
            current++;

            return {
                type: 'INVLPG',
                value: token.value,
            };
        }

        if (token.type === 'wbinvd') {
            current++;

            return {
                type: 'WBINVD',
                value: token.value,
            };
        }

        if (token.type === 'rdmsr') {
            current++;

            return {
                type: 'RDMSR',
                value: token.value,
            };
        }

        if (token.type === 'wrmsr') {
            current++;

            return {
                type: 'WRMSR',
                value: token.value,
            };
        }

        if (token.type === 'rdtsr') {
            current++;

            return {
                type: 'RDTSR',
                value: token.value,
            };
        }

        if (token.type === 'cpuid') {
            current++;

            return {
                type: 'CPUID',
                value: token.value,
            };
        }

        if (token.type === 'iret') {
            current++;

            return {
                type: 'IRET',
                value: token.value,
            };
        }

        if (token.type === 'pushfd') {
            current++;

            return {
                type: 'PUSHFD',
                value: token.value,
            };
        }

        if (token.type === 'popfd') {
            current++;

            return {
                type: 'POPFD',
                value: token.value,
            };
        }

        if (token.type === 'lahf') {
            current++;

            return {
                type: 'LAHF',
                value: token.value,
            };
        }

        if (token.type === 'sahf') {
            current++;

            return {
                type: 'SAHF',
                value: token.value,
            };
        }

        if (token.type === 'stall') {
            current++;

            return {
                type: 'STALL',
                value: token.value,
            };
        }

        if (token.type === 'reset') {
            current++;

            return {
                type: 'RESET',
                value: token.value,
            };
        }

        if (token.type === 'allocate_pages') {
            current++;

            return {
                type: 'ALOCATE_PAGES',
                value: token.value,
            };
        }

        if (token.type === 'free_pages') {
            current++;

            return {
                type: 'FREE_PAGES',
                value: token.value,
            };
        }

        if (token.type === 'get_memory_map') {
            current++;

            return {
                type: 'GET_MEMORY_MAP',
                value: token.value,
            };
        }

        if (token.type === 'allocate_pool') {
            current++;

            return {
                type: 'ALOCATE_POOL',
                value: token.value,
            };
        }

        if (token.type === 'free_pool') {
            current++;

            return {
                type: 'FREE_POOL',
                value: token.value,
            };
        }

        if (token.type === 'set_watchdog_timer') {
            current++;

            return {
                type: 'SET_WATCHDOG_TIMER',
                value: token.value,
            };
        }

        if (token.type === 'connect_controller') {
            current++;

            return {
                type: 'CONNECT_CONTROLLER',
                value: token.value,
            };
        }

        if (token.type === 'disconnect_controller') {
            current++;

            return {
                type: 'DISCONNECT_CONTROLLER',
                value: token.value,
            };
        }

        if (token.type === 'open_protocol') {
            current++;

            return {
                type: 'OPEN_PROTOCOL',
                value: token.value,
            };
        }

        if (token.type === 'locate_handle') {
            current++;

            return {
                type: 'LOCATE_HANDLE',
                value: token.value,
            };
        }

        if (token.type === 'locate_device_path') {
            current++;

            return {
                type: 'LOCATE_DEVICE_PATH',
                value: token.value,
            };
        }

        if (token.type === 'install_protocol_interface') {
            current++;

            return {
                type: 'INSTALL_PROTOCOL_INTERFACE',
                value: token.value,
            };
        }

        if (token.type === 'reinstall_protocol_interface') {
            current++;

            return {
                type: 'REINSTALL_PROTOCOL_INTERFACE',
                value: token.value,
            };
        }

        if (token.type === 'uninstall_protocol_interface') {
            current++;

            return {
                type: 'UNINSTALL_PROTOCOL_INTERFACE',
                value: token.value,
            };
        }

        if (token.type === 'handle_protocol') {
            current++;

            return {
                type: 'HANDLE_PROTOCOL',
                value: token.value,
            };
        }

        if (token.type === 'register_protocol_notify') {
            current++;

            return {
                type: 'REGISTER_PROTOCOL_NOTIFY',
                value: token.value,
            };
        }

        if (token.type === 'locate_handle_buffer') {
            current++;

            return {
                type: 'LOCATE_HANDLE_BUFFER',
                value: token.value,
            };
        }

        if (token.type === 'print') {
            current++;

            return {
                type: 'PRINT',
                value: token.value,
            };
        }

        if (token.type === 'call') {
            current++;

            return {
                type: 'CALL',
                value: token.value,
            };
        }

        if (token.type === 'import') {
            current++;

            return {
                type: 'IMPORT',
                value: token.value,
            };
        }

        if (token.type === 'export') {
            current++;

            return {
                type: 'EXPORT',
                value: token.value,
            };
        }

        if (token.type === 'return') {
            current++;

            return {
                type: 'RETURN',
                value: token.value,
            };
        }

        if (token.type === 'break') {
            current++;

            return {
                type: 'BREAK',
                value: token.value,
            };
        }

        if (token.type === 'continue') {
            current++;

            return {
                type: 'CONTINUE',
                value: token.value,
            };
        }

        if (token.type === 'while') {
            current++;

            return {
                type: 'WHILE',
                value: token.value,
            };
        }

        if (token.type === 'do') {
            current++;

            return {
                type: 'DO',
                value: token.value,
            };
        }

        if (token.type === 'for') {
            current++;

            return {
                type: 'FOR',
                value: token.value,
            };
        }
    }
}