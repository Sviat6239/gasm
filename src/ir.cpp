#include "ir.h"

#include <vector>

using namespace std;

namespace
{

    string joinChildTexts(const AstNode &node)
    {
        string result;
        for (const auto &child : node.children)
        {
            if (child.text.empty())
            {
                continue;
            }

            if (!result.empty())
            {
                result += ", ";
            }
            result += child.text;
        }

        return result;
    }

    string renderStatementValue(const AstNode &node)
    {
        if (node.kind == AstKind::Declaration)
        {
            if (node.children.size() >= 2)
            {
                return node.children[0].text + " = " + node.children[1].text;
            }

            if (!node.children.empty())
            {
                return node.children.front().text;
            }

            return node.text;
        }

        if (node.kind == AstKind::Directive)
        {
            if (!node.children.empty())
            {
                return node.children.front().text;
            }

            return node.text;
        }

        if (node.kind == AstKind::IfStatement)
        {
            if (!node.children.empty())
            {
                return node.children.front().text;
            }

            return node.text;
        }

        return node.text;
    }

    void collectIR(const AstNode &node, vector<IRNode> &ir, SymbolTable &symbolTable)
    {
        if (node.kind == AstKind::Label)
        {
            symbolTable.labels[node.text] = static_cast<int>(node.line);
            return;
        }

        if (node.kind == AstKind::Declaration || node.kind == AstKind::Directive)
        {
            if (node.kind == AstKind::Directive && node.token == Tokens::ENTRY && !node.children.empty())
            {
                symbolTable.entryLabel = node.children.front().text;
            }

            ir.push_back({node.token, renderStatementValue(node), node.line});
            return;
        }

        if (node.kind == AstKind::Instruction)
        {
            ir.push_back({node.token, joinChildTexts(node), node.line});
            return;
        }

        if (node.kind == AstKind::IfStatement)
        {
            string condition = !node.children.empty() ? node.children.front().text : node.text;
            ir.push_back({Tokens::IF, condition, node.line});

            if (node.children.size() > 1)
            {
                collectIR(node.children[1], ir, symbolTable);
            }

            if (node.children.size() > 2)
            {
                ir.push_back({Tokens::ELSE, string(), node.children[2].line != 0 ? node.children[2].line : node.line});
                collectIR(node.children[2], ir, symbolTable);
            }

            return;
        }

        for (const auto &child : node.children)
        {
            collectIR(child, ir, symbolTable);
        }
    }

} // namespace

vector<IRNode> buildIR(const AstProgram &program, SymbolTable &symbolTable)
{
    vector<IRNode> ir;
    for (const auto &statement : program.statements)
    {
        collectIR(statement, ir, symbolTable);
    }

    return ir;
}
