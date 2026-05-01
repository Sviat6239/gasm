#include "ast.h"
#include "symbols.h"

#include <utility>

using namespace std;

namespace
{

    bool isDirectiveHead(Tokens::Token type)
    {
        switch (type)
        {
        case Tokens::FORMAT:
        case Tokens::ARCH:
        case Tokens::ENTRY:
            return true;
        default:
            return false;
        }
    }

    bool isInstructionHead(Tokens::Token type)
    {
        switch (type)
        {
        case Tokens::MOV:
        case Tokens::ADD:
        case Tokens::SUB:
        case Tokens::MUL:
        case Tokens::DIV:
        case Tokens::SQR:
        case Tokens::POW:
        case Tokens::CMP:
        case Tokens::JMP:
        case Tokens::JNZ:
        case Tokens::INC:
        case Tokens::DEC:
        case Tokens::XOR:
        case Tokens::AND:
        case Tokens::OR:
        case Tokens::NOT:
        case Tokens::SHL:
        case Tokens::SHR:
        case Tokens::SAR:
        case Tokens::ROL:
        case Tokens::ROR:
        case Tokens::RET:
        case Tokens::INT:
        case Tokens::SYSCALL:
        case Tokens::LDR:
        case Tokens::STR:
        case Tokens::ORR:
        case Tokens::EOR:
        case Tokens::BIC:
        case Tokens::LSL:
        case Tokens::LSR:
        case Tokens::ASR:
        case Tokens::TST:
        case Tokens::B:
        case Tokens::BL_OP:
        case Tokens::BX_OP:
        case Tokens::ADR:
        case Tokens::SDIV:
        case Tokens::UDIV:
        case Tokens::BFI:
        case Tokens::UBFX:
        case Tokens::CBZ:
        case Tokens::CBNZ:
        case Tokens::LUI:
        case Tokens::AUIPC:
        case Tokens::LW:
        case Tokens::SW:
        case Tokens::LD:
        case Tokens::SD:
        case Tokens::ADDI:
        case Tokens::SLT:
        case Tokens::SLTI:
        case Tokens::JAL:
        case Tokens::JALR:
        case Tokens::BEQ:
        case Tokens::BNE:
        case Tokens::BLT:
        case Tokens::BGE:
        case Tokens::PRINT:
        case Tokens::CALL:
            return true;
        default:
            return false;
        }
    }

    bool isOpeningToken(Tokens::Token type)
    {
        return type == Tokens::LPAREN || type == Tokens::LBRACKET || type == Tokens::LBRACE;
    }

    bool isNoLeadingSpaceToken(Tokens::Token type)
    {
        return type == Tokens::COMMA || type == Tokens::COLON || type == Tokens::SEMICOLON ||
               type == Tokens::RPAREN || type == Tokens::RBRACKET || type == Tokens::RBRACE;
    }

    string formatTokenSequence(const vector<Token> &tokens)
    {
        string result;
        for (size_t i = 0; i < tokens.size(); ++i)
        {
            const auto &token = tokens[i];
            if (token.lexeme.empty())
            {
                continue;
            }

            if ((token.type == Tokens::GREATER || token.type == Tokens::LESS) && i + 1 < tokens.size() && tokens[i + 1].type == Tokens::ASSIGN)
            {
                if (!result.empty() && result.back() != ' ' && result.back() != '(' && result.back() != '[' && result.back() != '{')
                {
                    result += ' ';
                }
                result += token.lexeme;
                result += '=';
                ++i;
                continue;
            }

            if (isOpeningToken(token.type))
            {
                if (!result.empty() && result.back() == ' ')
                {
                    result.pop_back();
                }
                result += token.lexeme;
                continue;
            }

            if (isNoLeadingSpaceToken(token.type))
            {
                if (!result.empty() && result.back() == ' ')
                {
                    result.pop_back();
                }
                result += token.lexeme;
                if (token.type == Tokens::COMMA)
                {
                    result += ' ';
                }
                continue;
            }

            if (!result.empty() && result.back() != ' ' && result.back() != '(' && result.back() != '[' && result.back() != '{')
            {
                result += ' ';
            }

            result += token.lexeme;
        }

        if (!result.empty() && result.back() == ' ')
        {
            result.pop_back();
        }

        return result;
    }

    AstNode makeTokenLeaf(const Token &token)
    {
        AstNode node;
        node.kind = AstKind::TokenLeaf;
        node.token = token.type;
        node.text = token.lexeme;
        node.line = token.line;
        return node;
    }

    AstNode makeExpressionNode(const vector<Token> &tokens, AstKind kind)
    {
        AstNode node;
        node.kind = kind;
        node.line = tokens.empty() ? 0 : tokens.front().line;
        node.text = formatTokenSequence(tokens);
        node.token = tokens.empty() ? Tokens::ERROR : tokens.front().type;
        for (const auto &token : tokens)
        {
            node.children.push_back(makeTokenLeaf(token));
        }
        return node;
    }

    pair<vector<Token>, vector<Token>> splitOnceTopLevel(const vector<Token> &tokens, Tokens::Token delimiter)
    {
        vector<Token> left;
        vector<Token> right;
        vector<Token> *current = &left;
        int parenDepth = 0;
        int bracketDepth = 0;
        int braceDepth = 0;

        for (const auto &token : tokens)
        {
            if (parenDepth == 0 && bracketDepth == 0 && braceDepth == 0 && token.type == delimiter)
            {
                current = &right;
                continue;
            }

            current->push_back(token);

            switch (token.type)
            {
            case Tokens::LPAREN:
                ++parenDepth;
                break;
            case Tokens::RPAREN:
                if (parenDepth > 0)
                {
                    --parenDepth;
                }
                break;
            case Tokens::LBRACKET:
                ++bracketDepth;
                break;
            case Tokens::RBRACKET:
                if (bracketDepth > 0)
                {
                    --bracketDepth;
                }
                break;
            case Tokens::LBRACE:
                ++braceDepth;
                break;
            case Tokens::RBRACE:
                if (braceDepth > 0)
                {
                    --braceDepth;
                }
                break;
            default:
                break;
            }
        }

        return {left, right};
    }

    vector<vector<Token>> splitTopLevel(const vector<Token> &tokens, Tokens::Token delimiter)
    {
        vector<vector<Token>> segments;
        vector<Token> current;
        int parenDepth = 0;
        int bracketDepth = 0;
        int braceDepth = 0;

        for (const auto &token : tokens)
        {
            if (parenDepth == 0 && bracketDepth == 0 && braceDepth == 0 && token.type == delimiter)
            {
                if (!current.empty())
                {
                    segments.push_back(current);
                    current.clear();
                }
                continue;
            }

            current.push_back(token);

            switch (token.type)
            {
            case Tokens::LPAREN:
                ++parenDepth;
                break;
            case Tokens::RPAREN:
                if (parenDepth > 0)
                {
                    --parenDepth;
                }
                break;
            case Tokens::LBRACKET:
                ++bracketDepth;
                break;
            case Tokens::RBRACKET:
                if (bracketDepth > 0)
                {
                    --bracketDepth;
                }
                break;
            case Tokens::LBRACE:
                ++braceDepth;
                break;
            case Tokens::RBRACE:
                if (braceDepth > 0)
                {
                    --braceDepth;
                }
                break;
            default:
                break;
            }
        }

        if (!current.empty())
        {
            segments.push_back(current);
        }

        return segments;
    }

    vector<Token> collectBalanced(const vector<Token> &tokens, size_t &index, Tokens::Token open, Tokens::Token close)
    {
        vector<Token> collected;
        if (index >= tokens.size() || tokens[index].type != open)
        {
            return collected;
        }

        int depth = 0;
        while (index < tokens.size())
        {
            const Token token = tokens[index++];
            if (token.type == open)
            {
                ++depth;
                if (depth > 1)
                {
                    collected.push_back(token);
                }
                continue;
            }

            if (token.type == close)
            {
                --depth;
                if (depth == 0)
                {
                    break;
                }
                collected.push_back(token);
                continue;
            }

            if (depth >= 1)
            {
                collected.push_back(token);
            }
        }

        return collected;
    }

    AstNode parseStatement(const vector<Token> &tokens, size_t &index);

    AstNode parseBlock(const vector<Token> &tokens, size_t &index, const string &text)
    {
        AstNode node;
        node.kind = AstKind::Block;
        node.text = text;
        node.line = index < tokens.size() ? tokens[index].line : 0;

        if (index < tokens.size() && tokens[index].type == Tokens::LBRACE)
        {
            ++index;
        }

        while (index < tokens.size() && tokens[index].type != Tokens::RBRACE)
        {
            if (tokens[index].type == Tokens::SEMICOLON)
            {
                ++index;
                continue;
            }

            size_t before = index;
            AstNode child = parseStatement(tokens, index);
            if (child.kind != AstKind::Empty)
            {
                node.children.push_back(move(child));
            }
            else if (index == before)
            {
                ++index;
            }
        }

        if (index < tokens.size() && tokens[index].type == Tokens::RBRACE)
        {
            ++index;
        }

        return node;
    }

    AstNode parseIfStatement(const vector<Token> &tokens, size_t &index)
    {
        const Token ifToken = tokens[index++];

        AstNode node;
        node.kind = AstKind::IfStatement;
        node.token = ifToken.type;
        node.text = ifToken.lexeme;
        node.line = ifToken.line;

        vector<Token> conditionTokens;
        if (index < tokens.size() && tokens[index].type == Tokens::LPAREN)
        {
            conditionTokens = collectBalanced(tokens, index, Tokens::LPAREN, Tokens::RPAREN);
        }
        else
        {
            while (index < tokens.size() && tokens[index].type != Tokens::LBRACE && tokens[index].type != Tokens::SEMICOLON && tokens[index].type != Tokens::RBRACE)
            {
                conditionTokens.push_back(tokens[index++]);
            }
        }

        if (!conditionTokens.empty())
        {
            node.children.push_back(makeExpressionNode(conditionTokens, AstKind::Expression));
        }

        if (index < tokens.size() && tokens[index].type == Tokens::LBRACE)
        {
            node.children.push_back(parseBlock(tokens, index, "then"));
        }
        else
        {
            AstNode thenNode = parseStatement(tokens, index);
            if (thenNode.kind != AstKind::Empty)
            {
                AstNode thenBlock;
                thenBlock.kind = AstKind::Block;
                thenBlock.text = "then";
                thenBlock.line = thenNode.line;
                thenBlock.children.push_back(move(thenNode));
                node.children.push_back(move(thenBlock));
            }
        }

        if (index < tokens.size() && tokens[index].type == Tokens::ELSE)
        {
            const Token elseToken = tokens[index++];
            AstNode elseBlock;
            elseBlock.kind = AstKind::Block;
            elseBlock.text = "else";
            elseBlock.line = elseToken.line;

            if (index < tokens.size() && tokens[index].type == Tokens::LBRACE)
            {
                elseBlock = parseBlock(tokens, index, "else");
            }
            else
            {
                AstNode elseNode = parseStatement(tokens, index);
                if (elseNode.kind != AstKind::Empty)
                {
                    elseBlock.children.push_back(move(elseNode));
                }
            }

            node.children.push_back(move(elseBlock));
        }

        return node;
    }

    AstNode buildFlatStatementNode(const vector<Token> &statementTokens)
    {
        if (statementTokens.empty())
        {
            return {};
        }

        const Token &head = statementTokens.front();
        vector<Token> tail(statementTokens.begin() + 1, statementTokens.end());

        AstNode node;
        node.token = head.type;
        node.text = head.lexeme;
        node.line = head.line;

        if (head.type == Tokens::DECLARE)
        {
            node.kind = AstKind::Declaration;
            auto [left, right] = splitOnceTopLevel(tail, Tokens::ASSIGN);
            if (!left.empty())
            {
                node.children.push_back(makeExpressionNode(left, AstKind::Expression));
            }
            if (!right.empty())
            {
                node.children.push_back(makeExpressionNode(right, AstKind::Expression));
            }
            return node;
        }

        if (isDirectiveHead(head.type))
        {
            node.kind = AstKind::Directive;
            if (!tail.empty())
            {
                node.children.push_back(makeExpressionNode(tail, AstKind::Expression));
            }
            return node;
        }

        if (isInstructionHead(head.type))
        {
            node.kind = AstKind::Instruction;
            for (const auto &operandTokens : splitTopLevel(tail, Tokens::COMMA))
            {
                if (!operandTokens.empty())
                {
                    node.children.push_back(makeExpressionNode(operandTokens, AstKind::Operand));
                }
            }
            return node;
        }

        node.kind = AstKind::Expression;
        node.children.push_back(makeExpressionNode(statementTokens, AstKind::Expression));
        return node;
    }

    AstNode parseStatement(const vector<Token> &tokens, size_t &index)
    {
        if (index >= tokens.size())
        {
            return {};
        }

        if (tokens[index].type == Tokens::SEMICOLON)
        {
            ++index;
            return {};
        }

        if (tokens[index].type == Tokens::RBRACE)
        {
            return {};
        }

        if (tokens[index].type == Tokens::ELSE)
        {
            ++index;
            return {};
        }

        if (tokens[index].type == Tokens::IF)
        {
            return parseIfStatement(tokens, index);
        }

        if (tokens[index].type == Tokens::LBRACE)
        {
            return parseBlock(tokens, index, "block");
        }

        if (tokens[index].type == Tokens::IDENTIFIER && index + 1 < tokens.size() && tokens[index + 1].type == Tokens::COLON)
        {
            const Token labelToken = tokens[index];
            index += 2;
            if (index < tokens.size() && tokens[index].type == Tokens::SEMICOLON)
            {
                ++index;
            }

            AstNode node;
            node.kind = AstKind::Label;
            node.token = labelToken.type;
            node.text = labelToken.lexeme;
            node.line = labelToken.line;
            return node;
        }

        vector<Token> statementTokens;
        while (index < tokens.size() && tokens[index].type != Tokens::SEMICOLON && tokens[index].type != Tokens::RBRACE)
        {
            statementTokens.push_back(tokens[index++]);
        }

        if (index < tokens.size() && tokens[index].type == Tokens::SEMICOLON)
        {
            ++index;
        }

        return buildFlatStatementNode(statementTokens);
    }

    string astKindName(AstKind kind)
    {
        switch (kind)
        {
        case AstKind::Program:
            return "program";
        case AstKind::Directive:
            return "directive";
        case AstKind::Declaration:
            return "declaration";
        case AstKind::Label:
            return "label";
        case AstKind::Instruction:
            return "instruction";
        case AstKind::IfStatement:
            return "if";
        case AstKind::Block:
            return "block";
        case AstKind::Operand:
            return "operand";
        case AstKind::Expression:
            return "expression";
        case AstKind::TokenLeaf:
            return "token";
        case AstKind::Empty:
        default:
            return "empty";
        }
    }

    void writeAstNode(ostream &out, const AstNode &node, size_t depth)
    {
        if (node.kind == AstKind::Empty)
        {
            return;
        }

        string indent(depth * 2, ' ');
        out << indent << astKindName(node.kind);

        if (!node.text.empty())
        {
            out << ' ' << node.text;
        }

        if (node.line != 0)
        {
            out << " @" << node.line;
        }

        if (node.kind == AstKind::TokenLeaf)
        {
            Token token{node.token, node.text, node.line};
            out << " [" << displayName(token) << "]";
        }

        out << '\n';

        for (const auto &child : node.children)
        {
            writeAstNode(out, child, depth + 1);
        }
    }

} // namespace

AstProgram buildAst(const vector<Token> &tokens)
{
    AstProgram program;
    size_t index = 0;

    while (index < tokens.size())
    {
        AstNode statement = parseStatement(tokens, index);
        if (statement.kind != AstKind::Empty)
        {
            program.statements.push_back(move(statement));
        }
    }

    return program;
}

void writeAst(ostream &out, const AstProgram &program)
{
    out << "[ast]\n";
    out << "program\n";
    for (const auto &statement : program.statements)
    {
        writeAstNode(out, statement, 1);
    }
}