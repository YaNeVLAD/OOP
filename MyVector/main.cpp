#include <iostream>

#include "Vector.hpp"
#include <algorithm>
#include <ranges>
#include <string>
#include <vector>

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
	std::vector<int> v{ 1, 2, 3 };
	Vector<int> vec{ 1, 2, 3 };

	for (auto& val : vec)
	{
		val = 444;
	}

	{
		Vector<int> vec1{ 5, 4, 3, 2, 1 };
		std::ranges::sort(vec1);

		for (auto& val : vec1)
		{
			std::cout << val << std::endl;
		}
	}

	vec.Reserve(10);
	vec.EmplaceBack();
	vec.EmplaceBack();
	vec.EmplaceBack();
	vec.EmplaceBack();
	vec.Resize(3);
	vec.EmplaceBack();

	vec.PopBack();
	vec.PopBack();
	vec.EmplaceBack();

	std::cout << "Program end" << std::endl;
}
