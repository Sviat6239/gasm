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
    }
}