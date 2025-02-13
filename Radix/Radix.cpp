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

bool IsRadixOutOfRange(int radix, bool& wasInvalidArgumentError)
{
	if (radix < MIN_RADIX || radix > MAX_RADIX)
	{
		wasInvalidArgumentError = true;
		return true;
	}
	return false;
}

int CharToDigit(char ch, bool& wasInvalidArgumentError)
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
		wasInvalidArgumentError = true;
		return EXIT_FAILURE;
	}

	return digit;
}

int StringToInt(const std::string& str, int radix, bool& wasOverflowError, bool& wasInvalidArgumentError)
{
	if (IsRadixOutOfRange(radix, wasInvalidArgumentError))
	{
		return EXIT_FAILURE;
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
		int digit = CharToDigit(str[i], wasInvalidArgumentError);

		if (wasInvalidArgumentError)
		{
			return EXIT_FAILURE;
		}

		if (digit >= radix)
		{
			wasInvalidArgumentError = true;
			return EXIT_FAILURE;
		}

		if (result > (INT_MAX - digit) / radix)
		{
			wasOverflowError = true;
			return EXIT_FAILURE;
		}

		result = result * radix + digit;
	}

	return result * sign;
}

std::string IntToString(int n, int radix, bool& wasInvalidArgumentError)
{
	if (IsRadixOutOfRange(radix, wasInvalidArgumentError))
	{
		return "";
	}

	if (n == 0)
	{
		return "0";
	}

	std::string result;
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

	return EXIT_SUCCESS;
}
