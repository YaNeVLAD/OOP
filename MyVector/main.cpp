#include <algorithm>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <sstream>

#include "Vector.hpp"
#include <vector>
int main()
{
	Vector<double> numbers;
	Vector<std::string> others;

	std::cout << "Enter Text:" << std::endl;

	std::string line;
	std::string token;
	while (std::getline(std::cin, line))
	{
		std::istringstream iss(line);
		while (iss >> token)
		{
			try
			{
				numbers.PushBack(std::stod(token));
			}
			catch (const std::exception&)
			{
				others.PushBack(token);
			}
		}
	}

	std::cout << "Text contains " << numbers.Size() << " numbers" << std::endl;
	std::cout << "Text contains " << others.Size() << " not number elements" << std::endl;
	std::cout << "Total count " << numbers.Size() + others.Size() << " elements" << std::endl;

	std::cout << "Sorted numbers: " << std::endl;
	std::ranges::sort(numbers);

	std::cout << std::fixed << std::setprecision(2);
	for (const auto& num : numbers)
	{
		std::cout << num << " ";
	}
}
