import { tokenizer } from "./lexer";
import { parser } from "./parser";

export class ASTNode {
    constructor(body) {
        this.type = this.type;
    }
}

export class ProgramNode extends ASTNode {
    constructor(body) {
        super('Program');
        this.body = body;
    }
}

export class InstructionNode extends ASTNode {
    constructor(name, args) {
        super('Instruction');
        this.name = name.toUpperCase();
        this.args = args;
    }
}

export class RegisterNode extends ASTNode {
    constructor(name) {
        super('Register');
        this.name = name;
    }
}

export class DirectiveNode extends ASTNode {
    constructor(name, value) {
        super('Directive');
        this.name = name.toUpperCase();
        this.value = value;
    }
}