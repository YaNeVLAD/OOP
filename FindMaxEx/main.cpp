#include <iostream>

#include <string>

#include "FindMaxEx.hpp"

struct Sportsman
{
	Sportsman()
		: weight(0)
		, height(0)
	{
	}

	Sportsman(std::string name, unsigned weight, unsigned height)
		: name(std::move(name))
		, weight(weight)
		, height(height)
	{
	}

	std::string name;
	unsigned weight;
	unsigned height;
};

void Print(const Sportsman& sportsman)
{
	auto& [name, weight, height] = sportsman;
	std::cout << "Name: " << name << std::endl;
	std::cout << "Weight: " << weight << std::endl;
	std::cout << "Height: " << height << std::endl;
	std::cout << "------------" << std::endl;
}

int main()
{
	std::vector<Sportsman> vec = {
		{ "aboba", 120, 220 },
		{ "abiba", 180, 200 },
	};

	std::cout << "Max Height: " << std::endl;
	Sportsman maxHeight;
	FindMaxEx(vec, maxHeight, [](const Sportsman& a, const Sportsman& b) {
		return a.height < b.height;
	});

	Print(maxHeight);

	std::cout << "Max Weight: " << std::endl;
	Sportsman maxWeight;
	FindMaxEx(vec, maxWeight, [](const Sportsman& a, const Sportsman& b) {
		return a.weight < b.weight;
	});

	Print(maxWeight);

	return EXIT_SUCCESS;
}
