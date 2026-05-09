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
    }
}