#pragma once

#include <set>

namespace GeneratePrimes
{
const int MAX_RANGE = 100'000'000;

/**
 * @throws std::invalid_argument - when upperBound is greater than 100'000'000
 */
std::set<int> GeneratePrimeNumbersSet(int upperBound);

} // namespace GeneratePrimes
