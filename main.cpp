//std includes
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <map>
#include <set>
#include <stack>

//llvm includes
#include "llvm/CodeGen/Passes.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Analysis/TargetTransformInfo.h"

//llvm IR includes
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Intrinsics.h"

//namespaces
using namespace std;
using namespace llvm;
using namespace Intrinsic;

int main() {
    vector<vector<string>> code_lines;
    vector<vector<string>> output;

    map<string, string> int_variables;
    map<string, string> str_variables;

    set<string> needed_functions;
    set<string> needed_constants;

    int temp_buffer_count = 0;
    int str_to_print_count = 0;
    int if_label_count = 0;

    stack<int> if_stac;

    map<string, string> string_buffers;

    unordered_map<string, string> functions = {

    };

    unordered_map<string, string> constants = {

    };

    unordered_map<string, string> key_words = {
        
    };

    //llvm content init
    LLVMContext context;
    Module* module = new Module("gasm_module", context);
    IRBuilder<> builder(context);

    FunctionType* funcType = FunctionType::get(builder.getInt32Ty(), false);
    Function* mainFunc = Function::Create(funcType, Function::ExternalLinkage, "main", module);
    BasicBlock* entry = BasicBlock::Create(context, "entry", mainFunc);
    builder.SetInsertPoint(entry);

    //reading file
    ifstream f("code.as");
    string line;

    //tokenizer
    if (f.is_open()){
        while (getline(f, line)){
            if(!line.empty()){
                vector<string> parts;
                stringstream ss(line);
                string word;

                while (ss >> word){
                    parts.push_back(word);
                }

                if (!parts.empty()){
                    code_lines.push_back(parts);
                }
            }
        }
        f.close();
    }

    //main loop
    for (const auto& row : code_lines){
        if (row.empty()) continue;

        if (row[0] == "let") {
            if (row.size() > 1) {
                string token = row[1];
                size_t colonPos = token.find(':');
                if (colonPos != string::npos) {
                    string type = token.substr(0, colonPos);
                    string name = token.substr(colonPos + 1);

                    cout << type << endl;
                    cout << name << endl;
                }
            }
        } else if (row[0] == "const"){
            if (row.size() > 1){
                string token = row[1];
                size_t colonPos = token.find(':');
                if (colonPos != string::npos) {
                    string type = token.substr(0, colonPos);
                    string name = token.substr(colonPos + 1);

                    cout << type << endl;
                    cout << name << endl;
                }
            }
        }

    }

    return 0;
}