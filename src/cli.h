#pragma once

#include "tokens.h"
#include <vector>
#include <string>
#include <filesystem>

using namespace std;

static string emitModeName(EmitMode mode);
static bool parseEmitMode(const string& value, EmitMode& mode);
static filesystem::path projectRoot();
static vector<filesystem::path> discoverInputs(const filesystem::path& root);
static void printUsage(const string& exeName, const filesystem::path& root);
static void printInputList(const vector<filesystem::path>& inputs);
static bool parseArguments(int argc, char* argv[], CliOptions& options, string& error);
static bool resolveInput(const filesystem::path& root, const string& requested, string& resolved);
static bool chooseInputInteractively(const vector<filesystem::path>& inputs, string& chosen);
static string defaultOutputPath(const string& inputPath, EmitMode mode);
