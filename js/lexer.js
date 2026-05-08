export function tokenizer(input) {
    let current = 0;
    let tokens = [];

    while (current < input.length) {
        let char = input[current];
        if (char === '(') {
            tokens.push({
                type: 'leftParent',
                value: '(',
            })
            current++;
            continue
        }

        if (char === ')') {
            tokens.push({
                type: 'rightParent',
                value: ')',
            })
            current++;
            continue;
        }

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
            else {
                tokens.push({ type: 'name', value });
            }
            continue;
        }
        throw new TypeError('Unknown charecter' + char);
    }

    return tokens;
}