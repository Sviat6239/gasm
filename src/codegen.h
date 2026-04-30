#pragma once

#include "tokens.h"
#include <string>
#include <filesystem>
#include <vector>

using namespace std;

enum class Architecture {
	X86,
	X86_64,
	ARM32,
	ARM64,
	RISC_V32,
	RISC_V64,
};

struct Instructions {
	Architecture arch;
	vector<uint8_t> bytes;
	string mnemonic;
};