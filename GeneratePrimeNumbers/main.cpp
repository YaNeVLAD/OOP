#include "GeneratePrimeNumbers.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 2)
		{
			throw std::invalid_argument("Invalid argument count. Usage: generate_prime_numbers_set.exe <upper_bound>");
		}

		int upperBound = std::stoi(argv[1]);

		for (const int prime : GeneratePrimeNumbersSet(upperBound))
		{
			std::cout << prime << " ";
		}
		std::cout << std::endl;

		return EXIT_SUCCESS;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;

		return EXIT_FAILURE;
	}
}
