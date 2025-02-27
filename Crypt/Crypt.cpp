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

void ProcessEncrypt(Args& args)
{
	auto& [mode, input, output, key] = args;

	char ch;
	while (input.get(ch))
	{
		ch ^= key;

		SwapBit(ch, 7, 5);
		SwapBit(ch, 6, 1);
		SwapBit(ch, 5, 0);
		SwapBit(ch, 4, 7);
		SwapBit(ch, 3, 6);
		SwapBit(ch, 2, 4);
		SwapBit(ch, 1, 3);
		SwapBit(ch, 0, 2);

		output << ch;
	}
}

void ProcessDecrypt(Args& args)
{
	auto& [mode, input, output, key] = args;

	char ch;
	while (input >> ch)
	{
		SwapBit(ch, 0, 2);
		SwapBit(ch, 1, 3);
		SwapBit(ch, 2, 4);
		SwapBit(ch, 3, 6);
		SwapBit(ch, 4, 7);
		SwapBit(ch, 5, 0);
		SwapBit(ch, 6, 1);
		SwapBit(ch, 7, 5);

		ch ^= key;

		output << ch;
	}
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
