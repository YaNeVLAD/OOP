#include <assert.h>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

int MIN_KEY = 0;
int MAX_KEY = 255;

unsigned char MAX_POS = 7;

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
	unsigned char key = 0;
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

unsigned char GetKeyFromString(const std::string& str)
{
	try
	{
		int key = std::stoi(str);

		AssertIsKeyInRange(key);

		return static_cast<unsigned char>(key);
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

	throw std::runtime_error("Wrong program mode: " + str + " Must be "
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

	args.input.open(argv[2], std::ios::binary);

	args.output.open(argv[3], std::ios::binary);

	if (!args.input.is_open() || !args.output.is_open())
	{
		throw std::runtime_error("Failed to open file. ");
	}

	args.key = GetKeyFromString(argv[4]);

	return args;
}

void SwapBit(char& byte, uint8_t startPos, uint8_t destPos)
{
	AssertIsBitPositionInRange(startPos);
	AssertIsBitPositionInRange(destPos);

	char startBit = (byte >> startPos) & 1;
	char destBit = (byte >> destPos) & 1;

	byte &= ~(1 << startPos);
	byte |= (destBit << startPos);

	byte &= ~(1 << destPos);
	byte |= (startBit << destPos);
}

char GetEncryptedChar(const char ch, unsigned char key)
{
	char value = ch;

	value ^= key;

	SwapBit(value, 7, 5);
	SwapBit(value, 6, 1);
	SwapBit(value, 5, 0);
	SwapBit(value, 4, 7);
	SwapBit(value, 3, 6);
	SwapBit(value, 2, 4);
	SwapBit(value, 1, 3);
	SwapBit(value, 0, 2);

	return value;
}

char GetDecryptedChar(const char ch, unsigned char key)
{
	char value = ch;

	SwapBit(value, 0, 2);
	SwapBit(value, 1, 3);
	SwapBit(value, 2, 4);
	SwapBit(value, 3, 6);
	SwapBit(value, 4, 7);
	SwapBit(value, 5, 0);
	SwapBit(value, 6, 1);
	SwapBit(value, 7, 5);

	value ^= key;

	return value;
}

void Process(Args& args)
{
	auto& [mode, input, output, key] = args;

	char ch;
	while (input.get(ch))
	{
		if (mode == CryptMode::ENCRYPT)
		{
			output << GetEncryptedChar(ch, key);
		}
		else
		{
			output << GetDecryptedChar(ch, key);
		}
	}
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);

		Process(args);

		return EXIT_SUCCESS;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;

		return EXIT_FAILURE;
	}
}
