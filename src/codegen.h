#pragma once

#include "tokens.h"
#include <string>
#include <filesystem>
#include <vector>

using namespace std;

enum class Architecture
{
	X86,
	X86_64,
	ARM32,
	ARM64,
	RISC_V32,
	RISC_V64,
};

// Small machine-code container returned by backend encoders.
// The `bytes` payload is written in little-endian order.
struct Instructions
{
	Architecture arch;
	vector<uint8_t> bytes;
	string mnemonic;
};

// Encode one IR node into x86-64 machine code.
// Unsupported forms return an empty `bytes` vector.
Instructions generate_x86_64(const IRNode &ir);