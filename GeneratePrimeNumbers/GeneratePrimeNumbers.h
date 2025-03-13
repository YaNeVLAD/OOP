#pragma once

#include <set>

/**
 * \throws std::invalid_argument - when upperBound is greater than 100'000'000
 */
std::set<int> GeneratePrimeNumbersSet(int upperBound);
