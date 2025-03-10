#include "GeneratePrimeNumbersSet.h"

#include <stdexcept>
#include <string>
#include <vector>

std::set<int> GeneratePrimes::GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound > MAX_RANGE)
	{
		throw std::out_of_range("Upper bound is out of range. Max range: " + std::to_string(MAX_RANGE));
	}
	if (upperBound < 2)
	{
		return {};
	}

	std::vector<bool> primes(upperBound + 1, true);

	for (size_t p = 2; p * p <= upperBound; ++p)
	{
		if (primes[p])
		{
			for (size_t i = p * p; i <= upperBound; i += p)
			{
				primes[i] = false;
			}
		}
	}

	std::set<int> result;
	for (size_t i = 2; i < primes.size(); ++i)
	{
		if (primes[i])
		{
			result.insert(static_cast<int>(i));
		}
	}

	return result;
}
