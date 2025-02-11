#include <iostream>
#include <stdexcept>
#include <string>

const int DECIMAL_DIGITS_AMOUNT = 10;
const int DECIMAL_RADIX = 10;

const int MIN_RADIX = 2;
const int MAX_RADIX = 36;

bool WasError(bool wasOverflowError, bool wasInvalidArgumentError)
{
	if (wasOverflowError)
	{
		std::cout << "VALUE OVERFLOW\n";
	}
	if (wasInvalidArgumentError)
	{
		std::cout << "INVALID ARGUMEMENT\n";
	}

	return wasOverflowError || wasInvalidArgumentError;
}

bool IsOverflow(int value, int radix, int digit)
{
	return value > (INT_MAX - digit) / radix;
}

bool IsRadixOutOfRange(int radix)
{
	return radix < MIN_RADIX && radix > MAX_RADIX;
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
		throw std::out_of_range("Unknown digit: \'" + std::string(1, ch) + "\'. Digits must be in range from 0 to Z");
	}

	return digit;
}

int StringToInt(const std::string& str, int radix, bool& wasOverflowError, bool& wasInvalidArgumentError)
{
	if (IsRadixOutOfRange(radix))
	{
		wasInvalidArgumentError = true;
		return EXIT_FAILURE;
		throw std::invalid_argument("Radix must be in range from 2 to 36");
	}

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
			wasInvalidArgumentError = true;
			return EXIT_FAILURE;
			throw std::out_of_range("This digit is not allowed for this radix: " + std::string(1, str[i]));
		}

		if (IsOverflow(result, radix, digit))
		{
			wasOverflowError = true;
			return EXIT_FAILURE;
			throw std::overflow_error("Evaluated value is out of range");
		}

		result = result * radix + digit;
	}

	return result * sign;
}

std::string IntToString(int n, int radix, bool& wasInvalidArgumentError)
{
	if (IsRadixOutOfRange(radix))
	{
		wasInvalidArgumentError = true;
		return "";
		throw std::invalid_argument("Radix must be in range from 2 to 36");
	}

	std::string result;

	if (n == 0)
	{
		return "0";
	}

	int number = (n > 0) ? n : -n;

	while (number > 0)
	{
		int remain = number % radix;

		if (remain < DECIMAL_DIGITS_AMOUNT)
		{
			result += std::to_string(remain);
		}
		else
		{
			result += char(remain - DECIMAL_DIGITS_AMOUNT + 'A');
		}

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
		bool wasInvalidArgumentError = false;
		bool wasOverflowError = false;

		int source = StringToInt(argv[1], DECIMAL_RADIX, wasOverflowError, wasInvalidArgumentError);
		int destination = StringToInt(argv[2], DECIMAL_RADIX, wasOverflowError, wasInvalidArgumentError);

		int value = StringToInt(argv[3], source, wasOverflowError, wasInvalidArgumentError);
		std::string result = IntToString(value, destination, wasInvalidArgumentError);

		if (WasError(wasOverflowError, wasInvalidArgumentError))
		{
			return EXIT_FAILURE;
		}

		std::cout << result << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "ERROR\n";
		std::cout << e.what() << std::endl;

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
