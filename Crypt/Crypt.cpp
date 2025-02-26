#include <assert.h>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

uint8_t MIN_KEY = 0;
uint8_t MAX_KEY = 255;

uint8_t MAX_POS = 7;

const std::string ENCRYPT_MODE_STR = "crypt";
const std::string DECRYPT_MODE_STR = "decrypt";
const std::string USAGE_HINT = "crypt.exe <crypt/decrypt> <input file> <output file> <key> ";

enum class CryptMode
{
	ENCRYPT,
	DECRYPT,
};

struct Args
{
	CryptMode mode = CryptMode::ENCRYPT;
	std::ifstream input;
	std::ofstream output;
	uint8_t key = 0;
};

void AssertIsBitPositionInRange(uint8_t position)
{
	if (position > MAX_POS)
	{
		throw std::out_of_range("Position of bit is out of range. Must be in range from 0 to "
			+ std::to_string(MAX_POS));
	}
}

void AssertIsKeyInRange(int key)
{
	if (key < MIN_KEY || key > MAX_KEY)
	{
		throw std::out_of_range("Wrong key. Must be in range from "
			+ std::to_string(MIN_KEY)
			+ " to "
			+ std::to_string(MAX_KEY));
	}
}

uint8_t GetKeyFromString(const std::string& str)
{
	try
	{
		int key = std::stoi(str);

		AssertIsKeyInRange(key);

		return static_cast<uint8_t>(key);
	}
	catch (const std::exception&)
	{
		throw;
	}
}

CryptMode GetCryptModeFromString(const std::string& str)
{
	if (str == ENCRYPT_MODE_STR)
	{
		return CryptMode::ENCRYPT;
	}
	else if (str == DECRYPT_MODE_STR)
	{
		return CryptMode::DECRYPT;
	}

	throw std::runtime_error("Wrong program mode: " + str + "Must be "
		+ ENCRYPT_MODE_STR
		+ " or "
		+ DECRYPT_MODE_STR);
}

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		throw std::runtime_error("Wrong argument count. Usage: " + USAGE_HINT);
	}

	Args args;

	args.mode = GetCryptModeFromString(argv[1]);

	args.input.open(argv[2]);

	args.output.open(argv[3]);

	if (!args.input.is_open() || !args.output.is_open())
	{
		throw std::runtime_error("Failed to open file. ");
	}

	args.key = GetKeyFromString(argv[4]);

	return args;
}

void SwapBit(uint8_t& byte, uint8_t startPos, uint8_t destPos)
{
	AssertIsBitPositionInRange(startPos);
	AssertIsBitPositionInRange(destPos);

	uint8_t startBit = (byte >> startPos) & 1;
	uint8_t destBit = (byte >> destPos) & 1;

	byte &= ~(1 << startPos);
	byte |= (destBit << startPos);

	byte &= ~(1 << destPos);
	byte |= (startBit << destPos);
}

void ProcessEncrypt(const Args& args)
{
	uint8_t value = 0b10101010;
	std::cout << "Start value " << static_cast<int>(value) << std::endl;
	assert(value == 170);

	SwapBit(value, 0, 7);

	std::cout << "Swapped value " << static_cast<int>(value) << std::endl;
	assert(value == 43);
}

void ProcessDecrypt(const Args& args)
{
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);

		if (args.mode == CryptMode::ENCRYPT)
		{
			ProcessEncrypt(args);
		}
		else
		{
			ProcessDecrypt(args);
		}

		return EXIT_SUCCESS;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;

		return EXIT_FAILURE;
	}
}
