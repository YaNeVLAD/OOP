#pragma once

#include <istream>
#include <ostream>
#include <vector>

/**
 * @throws std::invalid_argument - when stream contains NaN element
 */
std::vector<double> ReadNumbers(std::istream& input);

void ProcessNumbers(std::vector<double>& vector);

void PrintSortedNumbers(std::ostream& output, const std::vector<double>& vector);
