#include <iostream>

#include "Vector.hpp"
#include <algorithm>
#include <iomanip>
#include <sstream>

struct Spy
{
	Spy()
	{
		std::cout << "Spy Constructed\n";
	}

	Spy(Spy&& other) noexcept
		: data(other.data)
	{
		std::cout << "Spy Moved\n";
	}

	Spy(const Spy& other)
		: data(other.data)
	{
		std::cout << "Spy Copied\n";
	}

	~Spy()
	{
		std::cout << "Spy Destroyed\n";
		delete[] dataArr;
	}

	Spy& operator=(const Spy& other)
	{
		return *this;
	}

	double data = 666;
	int* dataArr = new int[10];
};

void PrintSpy(const Vector<Spy>& vec)
{
	std::cout << "-----Reversed iterator for-----" << std::endl;
	for (Vector<Spy>::TConstReverseIterator it = vec.rbegin(); it != vec.rend(); ++it)
	{
		std::cout << "Spy " << it->data << std::endl;
	}
	std::cout << "-----Range-based for-----------" << std::endl;
	for (auto& spy : vec)
	{
		std::cout << "Spy " << spy.data << std::endl;
	}
	std::cout << "-----Index for-----------------" << std::endl;
	for (size_t i = 0; i < vec.Size(); ++i)
	{
		std::cout << "Spy " << vec[i].data << std::endl;
	}
	std::cout << "-------------------------------" << std::endl;
}

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
	std::cout << "Total count " << numbers.Size() + others.Size() << " elements";

	std::cout << "Sorted numbers: " << std::endl;
	std::sort(numbers.begin(), numbers.end());

	for (const auto& num : numbers)
	{
		std::cout << std::fixed << std::setprecision(2) << num << " ";
	}
}
