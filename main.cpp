#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <cstdint>

#include "src/tokens.h"
#include "src/utils.h"
#include "src/lexer.h"
#include "src/parser.h"
#include "src/ir.h"
#include "src/symbols.h"
#include "src/cli.h"
#include "src/output.h"

using namespace std;


int main(int argc, char* argv[]) {
    SymbolTable symbolTable;

    CliOptions options;
    string cliError;
    if (!parseArguments(argc, argv, options, cliError)) {
        cerr << cliError << endl;
        printUsage(argc > 0 ? argv[0] : "gasm", projectRoot());
        return 1;
    }

    filesystem::path root = projectRoot();
    vector<filesystem::path> inputs = discoverInputs(root);

    if (options.showHelp) {
        printUsage(argc > 0 ? argv[0] : "gasm", root);
        if (!inputs.empty()) {
            cout << '\n';
            printInputList(inputs);
        }
        return 0;
    }

    if (options.listInputs) {
        printInputList(inputs);
        return 0;
    }

    if (options.pickInput || options.inputPath.empty()) {
        if (!chooseInputInteractively(inputs, options.inputPath)) {
            cerr << "No input file selected." << endl;
            return 1;
        }
    }

    string resolvedInput;
    if (!resolveInput(root, options.inputPath, resolvedInput)) {
        cerr << "Failed to open source file: " << options.inputPath << endl;
        return 1;
    }

    ifstream code(resolvedInput);

    if (!code.is_open()) {
        cerr << "Failed to open source file: " << resolvedInput << endl;
        return 1;
    }

    // Phase 1: Lexer
    vector<TokenString> rawTokens = lex(code);
    if (rawTokens.empty()) {
        return 1;
    }

    // Phase 2: Parser
    vector<Token> parsedTokens = parse(rawTokens);

    // Phase 3: IR
    vector<IRNode> ir = buildIR(parsedTokens, symbolTable);

    string outputPath = options.outputPath.empty() ? defaultOutputPath(resolvedInput, options.emitMode) : options.outputPath;
    bool writeOk = false;
    if (options.emitMode == EmitMode::Ir) {
        writeOk = writeTextIr(outputPath, parsedTokens, ir, symbolTable);
    } else {
        writeOk = writeBinaryIrArtifact(outputPath, ir, symbolTable);
    }

    if (!writeOk) {
        return 1;
    }

    cout << "Compiled: " << resolvedInput << '\n';
    cout << "Emit mode: " << emitModeName(options.emitMode) << '\n';
    cout << "Output: " << outputPath << endl;
    printEntryResolution(symbolTable);

    return 0;
}
