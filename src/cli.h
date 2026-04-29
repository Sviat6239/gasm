#pragma once

#include "tokens.h"
#include <vector>
#include <string>
#include <filesystem>

using namespace std;

string emitModeName(EmitMode mode);
bool parseEmitMode(const string& value, EmitMode& mode);
filesystem::path projectRoot();
vector<filesystem::path> discoverInputs(const filesystem::path& root);
void printUsage(const string& exeName, const filesystem::path& root);
void printInputList(const vector<filesystem::path>& inputs);
bool parseArguments(int argc, char* argv[], CliOptions& options, string& error);
bool resolveInput(const filesystem::path& root, const string& requested, string& resolved);
bool chooseInputInteractively(const vector<filesystem::path>& inputs, string& chosen);
string defaultOutputPath(const string& inputPath, EmitMode mode);
