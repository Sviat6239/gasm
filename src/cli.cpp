#include "cli.h"
#include "utils.h"
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <system_error>

using namespace std;

static string emitModeName(EmitMode mode) {
    return mode == EmitMode::Ir ? "ir" : "bin";
}

static bool parseEmitMode(const string& value, EmitMode& mode) {
    string normalized = toLowerCopy(value);
    if (normalized == "ir") {
        mode = EmitMode::Ir;
        return true;
    }
    if (normalized == "bin" || normalized == "binary") {
        mode = EmitMode::Binary;
        return false;
    }
    return false;
}

static filesystem::path projectRoot() {
    filesystem::path current = filesystem::current_path();
    for (int depth = 0; depth < 6; ++depth) {
        if (filesystem::exists(current / "index.asm") || filesystem::exists(current / "examples")) {
            return current;
        }
        if (!current.has_parent_path()) {
            break;
        }
        current = current.parent_path();
    }
    return filesystem::current_path();
}

static vector<filesystem::path> discoverInputs(const filesystem::path& root) {
    vector<filesystem::path> inputs;
    if (filesystem::exists(root / "index.asm")) {
        inputs.push_back(root / "index.asm");
    }

    filesystem::path examplesDir = root / "examples";
    if (!filesystem::exists(examplesDir)) {
        return inputs;
    }

    error_code ec;
    for (filesystem::recursive_directory_iterator it(examplesDir, ec), end; it != end && !ec; it.increment(ec)) {
        if (it->is_regular_file() && toLowerCopy(it->path().extension().string()) == ".asm") {
            inputs.push_back(it->path());
        }
    }

    sort(inputs.begin(), inputs.end());
    return inputs;
}

static void printUsage(const string& exeName, const filesystem::path& root) {
    cout << "Usage:\n"
         << "  " << exeName << " [input.asm] [--emit ir|bin] [--output FILE]\n"
         << "  " << exeName << " --input input.asm --emit ir|bin --output FILE\n"
         << "  " << exeName << " --pick\n"
         << "  " << exeName << " --list-inputs\n\n"
         << "Options:\n"
         << "  -h, --help           Show this help\n"
         << "  -i, --input PATH     Source file to compile\n"
         << "  -e, --emit MODE      Output mode: ir or bin\n"
         << "  -o, --output FILE    Output file path\n"
         << "      --pick           Choose input file interactively\n"
         << "      --list-inputs    List discovered .asm files\n\n"
         << "Defaults:\n"
         << "  input  -> index.asm if present\n"
         << "  emit   -> ir\n"
         << "  output -> input file with .ir or .bin extension\n\n"
         << "Detected project root: " << root.string() << endl;
}

static void printInputList(const vector<filesystem::path>& inputs) {
    if (inputs.empty()) {
        cout << "No .asm files found.\n";
        return;
    }

    cout << "Available inputs:\n";
    for (size_t i = 0; i < inputs.size(); ++i) {
        cout << "  [" << (i + 1) << "] " << inputs[i].string() << '\n';
    }
}

static bool parseArguments(int argc, char* argv[], CliOptions& options, string& error) {
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            options.showHelp = true;
            continue;
        }
        if (arg == "-i" || arg == "--input") {
            if (i + 1 >= argc) {
                error = "Missing value for --input";
                return false;
            }
            options.inputPath = argv[++i];
            continue;
        }
        if (arg == "-e" || arg == "--emit") {
            if (i + 1 >= argc) {
                error = "Missing value for --emit";
                return false;
            }
            if (!parseEmitMode(argv[++i], options.emitMode)) {
                error = "Unsupported --emit value. Use 'ir' or 'bin'.";
                return false;
            }
            continue;
        }
        if (arg == "-o" || arg == "--output") {
            if (i + 1 >= argc) {
                error = "Missing value for --output";
                return false;
            }
            options.outputPath = argv[++i];
            continue;
        }
        if (arg == "--pick") {
            options.pickInput = true;
            continue;
        }
        if (arg == "--list-inputs") {
            options.listInputs = true;
            continue;
        }
        if (!arg.empty() && arg.front() != '-') {
            if (options.inputPath.empty()) {
                options.inputPath = arg;
                continue;
            }
            error = "Unexpected extra positional argument: " + arg;
            return false;
        }

        error = "Unknown argument: " + arg;
        return false;
    }

    return true;
}

static bool resolveInput(const filesystem::path& root, const string& requested, string& resolved) {
    filesystem::path direct(requested);
    if (filesystem::exists(direct)) {
        resolved = direct.string();
        return true;
    }

    filesystem::path fromRoot = root / direct;
    if (filesystem::exists(fromRoot)) {
        resolved = fromRoot.string();
        return true;
    }

    return false;
}

static bool chooseInputInteractively(const vector<filesystem::path>& inputs, string& chosen) {
    if (inputs.empty()) {
        cout << "Enter path to an .asm file: ";
        getline(cin, chosen);
        return !chosen.empty();
    }

    cout << "Select input file:\n";
    for (size_t i = 0; i < inputs.size(); ++i) {
        cout << "  [" << (i + 1) << "] " << inputs[i].string() << '\n';
    }
    cout << "  [0] Enter a custom path\n";
    cout << "Choice: ";

    string choiceText;
    getline(cin, choiceText);
    if (choiceText.empty()) {
        return false;
    }

    try {
        int choice = stoi(choiceText);
        if (choice == 0) {
            cout << "Path: ";
            getline(cin, chosen);
            return !chosen.empty();
        }
        if (choice < 1 || static_cast<size_t>(choice) > inputs.size()) {
            return false;
        }
        chosen = inputs[static_cast<size_t>(choice - 1)].string();
        return true;
    } catch (...) {
        return false;
    }
}

static string defaultOutputPath(const string& inputPath, EmitMode mode) {
    filesystem::path output(inputPath);
    output.replace_extension(mode == EmitMode::Ir ? ".ir" : ".bin");
    return output.string();
}
