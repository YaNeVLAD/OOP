#include "GeneratePrimeNumbers.h"

#include <iostream>
#include <math.h>
#include <stdexcept>
#include <string>
#include <vector>

const int MAX_RANGE = 100'000'000;
const int MIN_PRIME = 2;

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound > MAX_RANGE)
	{
		throw std::out_of_range("Upper bound is out of range. Max range: " + std::to_string(MAX_RANGE));
	}
	if (upperBound < MIN_PRIME)
	{
		return {};
	}

	int maxFactor = static_cast<int>(sqrt(upperBound));
	std::vector<bool> primes((upperBound / 2) + 1, true);

	for (size_t p = 3; p <= maxFactor; p += 2)
	{
		if (primes[p / 2])
		{
			for (size_t i = p * p; i < upperBound; i += 2 * p)
			{
				primes[i / 2] = false;
			}
		}
	}

	std::set<int> result;
	result.insert(2);

	for (size_t i = 1; i < primes.size(); ++i)
	{
		int number = static_cast<int>(2 * i + 1);
		if (number <= upperBound && primes[i])
		{
			result.insert(number);
		}
	}

	return result;
}
