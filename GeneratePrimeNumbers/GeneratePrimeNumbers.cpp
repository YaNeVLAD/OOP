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

	std::vector<bool> primes(upperBound + 1, true);

	for (size_t p = MIN_PRIME; p <= sqrt(upperBound); ++p)
	{
		if (!primes[p])
		{
			continue;
		}
		for (size_t i = p * p; i <= upperBound; i += p)
		{
			primes[i] = false;
		}
	}

	std::set<int> result;
	for (size_t i = MIN_PRIME; i < primes.size(); ++i)
	{
		if (primes[i])
		{
			result.insert(static_cast<int>(i));
		}
	}

	return result;
}
