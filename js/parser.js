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
    }
}