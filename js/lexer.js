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
    }
}