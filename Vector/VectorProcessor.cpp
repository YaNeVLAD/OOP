#include "VectorProcessor.h"

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>

std::vector<double> ReadNumbers(std::istream& input)
{
	std::vector<double> result;

	std::string line;
	std::string token;

	try
	{
		while (std::getline(input, line))
		{
			std::istringstream iss(line);
			while (iss >> token)
			{
				double number = std::stod(token);

				result.push_back(number);
			}
		}
	}
	catch (const std::exception&)
	{
		throw std::invalid_argument("Invalid number: " + token);
	}

	return result;
}

void ProcessNumbers(std::vector<double>& vector)
{
	auto it = std::min_element(vector.begin(), vector.end());
	if (it == vector.end())
	{
		return;
	}
	double min = *it;
	std::transform(vector.begin(), vector.end(), vector.begin(), [min](double number) {
		return number * min;
	});
}

void PrintSortedNumbers(std::ostream& output, const std::vector<double>& vector)
{
	if (vector.empty())
	{
		return;
	}

	auto sorted(vector);
	std::sort(sorted.begin(), sorted.end());

	for (const auto& number : sorted)
	{
		output << std::fixed << std::setprecision(3) << number << " ";
	}
	output << std::endl;
}
