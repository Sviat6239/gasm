import { tokenizer } from "./lexer.js";
import { parser } from "./parser.js";

export class ASTNode {
    constructor(body) {
        this.type = this.type;
    }
}

export class NumberNode extends ASTNode {
    constructor(value) {
        super('Number');
        this.value = value;
    }
}

export class StringNode extends ASTNode {
    constructor(value) {
        super('String');
        this.value = value;
    }
}

export class BoolNode extends ASTNode {
    constructor(value) {
        super('Boolean');
        this.value = value;
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

export class ForNode extends ASTNode {
    constructor(condition, body) {
        super('ForLoop');
        this.init = this.init;
        this.condition = condition;
        this.step = step;
        this.body = body;
    }
}

export class WhileNode extends ASTNode {
    constructor(condition, body) {
        super('WhileLoop');
        this.condition = condition;
        this.body = body;
    }
}


export class DoWhileNode extends ASTNode {
    constructor(condition, body) {
        super('DoWhileLoop');
        this.condition = condition;
        this.body = body;
    }
}

export class IfNode extends ASTNode {
    constructor(condition, thenBranch, elseBranch) {
        super('IfNode');
        this.condition = condition;
        this.thenBranch = thenBranch;
        this.elseBranch = elseBranch;
    }
}

export class SwitchNode extends ASTNode {
    constructor(expresion, cases, defaultCase) {
        super('SwitchNode');
        this.expresion = expresion;
        this.cases = cases;
        this.defaultCase = defaultCase;
    }
}

export class CaseNode extends ASTNode {
    constructor(value, body) {
        super('CaseNode');
        this.value = value;
        this.body = body;
    }
}

export class IdentifierNode extends ASTNode {
    constructor(name) {
        super('IdentifierNode');
        this.name = name;
    }
}

export class PrintNode extends ASTNode {
    constructor(value) {
        super('PrintNode');
        this.value = value;
    }
}

export class InputNode extends ASTNode {
    constructor(token, promt) {
        super('InputNode');
        this.token = token;
        this.promt = prompt;
    }
}

export class SemicolonNode extends ASTNode {
    constructor() {
        super('Semicolon');
    }
}

export class ColonNode extends ASTNode {
    constructor() {
        super('Colon');
    }
}

export class BinaryOperationNode extends ASTNode {
    constructor(operator, leftNode, rightNode) {
        super('BinaryOperationNode');
        this.operator = operator;
        this.leftNode = leftNode;
        this.rightNode = rightNode;
    }
}