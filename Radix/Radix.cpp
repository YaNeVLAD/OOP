#include <iostream>
#include <stdexcept>
#include <string>

const int DECIMAL_DIGITS_AMOUNT = 10;
const int DECIMAL_RADIX = 10;

const int MIN_RADIX = 2;
const int MAX_RADIX = 36;

void AssertIfRadixOutOfRange(int radix)
{
	if (radix < MIN_RADIX || radix > MAX_RADIX)
	{
		throw std::invalid_argument("Radix must be in range from " + std::to_string(MIN_RADIX) + " to " + std::to_string(MAX_RADIX));
	}
}

int CharToDigit(char ch)
{
	int digit = 0;
	char lower = std::tolower(ch);
	if (lower >= '0' && lower <= '9')
	{
		digit = lower - '0';
	}
	else if (lower >= 'a' && lower <= 'z')
	{
		digit = lower - 'a' + DECIMAL_DIGITS_AMOUNT;
	}
	else
	{
		throw std::out_of_range("Unknown digit: \'" + std::string{ ch } + "\'. Digits must be in range from 0 to Z");
	}

	return digit;
}

char DigitToChar(int digit)
{
	return (digit < DECIMAL_DIGITS_AMOUNT)
		? char(digit + '0')
		: char(digit - DECIMAL_DIGITS_AMOUNT + 'A');
}

int StringToInt(const std::string& str, int radix)
{
	AssertIfRadixOutOfRange(radix);

	int sign = 1;
	size_t start = 0;
	if (str[0] == '-')
	{
		sign = -1;
		start = 1;
	}

	int result = 0;
	for (size_t i = start; i < str.length(); ++i)
	{
		int digit = CharToDigit(str[i]);

		if (digit >= radix)
		{
			throw std::out_of_range("This digit is not allowed for this radix: " + std::string{ str[i] });
		}

		if (result > (INT_MAX - digit) / radix)
		{
			throw std::overflow_error("Evaluated value is out of range");
		}

		result = result * radix + digit;
	}

	return result * sign;
}

std::string IntToString(int n, int radix)
{
	AssertIfRadixOutOfRange(radix);

	if (n == 0)
	{
		return "0";
	}

	std::string result;
	int number = (n > 0) ? n : -n;
	while (number > 0)
	{
		int remain = number % radix;

		result += DigitToChar(remain);

		number /= radix;
	}

	if (n < 0)
	{
		result += '-';
	}

	std::reverse(result.begin(), result.end());

	return result;
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Usage: radix.exe <source notation> <destination notation> <value>\n";

		return EXIT_FAILURE;
	}

	try
	{
		int source = StringToInt(argv[1], DECIMAL_RADIX);
		int destination = StringToInt(argv[2], DECIMAL_RADIX);
		int value = StringToInt(argv[3], source);

		std::string result = IntToString(value, destination);

		std::cout << result << std::endl;

		return EXIT_SUCCESS;
	}
	catch (const std::exception& ex)
	{
		std::cout << "ERROR\n";
		std::cout << ex.what() << std::endl;

		return EXIT_FAILURE;
	}
}
