export function tokenizer(input) {
    let curent = 0;
    let tokens = [];

    while (current < input.length) {
        let char = input[current];
        if (char === '(') {
            tokens.push({
                type: 'leftParent',
                value: '(',
            })
        }
        if (char === ')') {
            tokens.push({
                type: 'rightParent',
                value: ')',
            })
        }
        let NUMBERS = /[0-9]/;
        if (NUMBERS.test(char)) {
            let value = '';
            while (NUMBERS.test(char)) {
                value += char;
                char = input[++current];
            }
            tokens.push({ type: 'number', value });
            continue;
        }
        let LETTERS = /[a-z]/i;
        if (LETTERS.test(char)) {
            let value = '';
            while (LETTERS.test(char)) {
                value += char;
                char = input[++current];
            }
            tokens.push({ type: 'name', value });
            continue;
        }
        throw new TypeError('Unknown charecter' + char);
    }

    return tokens;
}