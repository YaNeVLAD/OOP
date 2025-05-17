#include "catch2.h"

#include <stdexcept>

TEST_CASE("FindMaxEx with custom less - Empty vector")
{
	std::vector<int> vec;
	int maxValue = 0;
	REQUIRE(!FindMaxEx(vec, maxValue, std::less<int>()));
	REQUIRE(maxValue == 0);
}

TEST_CASE("FindMaxEx with custom less - Single element vector")
{
	std::vector<int> vec = { 42 };
	int maxValue = 0;
	REQUIRE(FindMaxEx(vec, maxValue, std::less<int>()));
	REQUIRE(maxValue == 42);
}

TEST_CASE("FindMaxEx with custom less - Multiple elements, standard less")
{
	std::vector<int> vec = { 10, 5, 20, 15, 30, 25 };
	int maxValue = 0;
	REQUIRE(FindMaxEx(vec, maxValue, std::less<int>()));
	REQUIRE(maxValue == 30);
}

TEST_CASE("FindMaxEx with custom less - Multiple elements, custom greater (find minimum)")
{
	std::vector<int> vec = { 10, 5, 20, 15, 30, 25 };
	int minValue = 0;
	REQUIRE(FindMaxEx(vec, minValue, std::greater<int>()));
	REQUIRE(minValue == 5);
}

TEST_CASE("FindMaxEx with custom less - Multiple elements with duplicates")
{
	std::vector<int> vec = { 10, 30, 20, 30, 15 };
	int maxValue = 0;
	REQUIRE(FindMaxEx(vec, maxValue, std::less<int>()));
	REQUIRE(maxValue == 30);
}

TEST_CASE("FindMaxEx with custom less - Different data types (double)")
{
	std::vector<double> vec = { 1.1, 3.3, 2.2, 3.3, 0.9 };
	double maxValue = 0.0;
	REQUIRE(FindMaxEx(vec, maxValue, std::less<double>()));
	REQUIRE(maxValue == 3.3);
}

TEST_CASE("FindMaxEx with custom less - Different data types (string)")
{
	std::vector<std::string> vec = { "apple", "orange", "banana", "pear" };
	std::string maxValue = "";
	REQUIRE(FindMaxEx(vec, maxValue, std::less<std::string>()));
	REQUIRE(maxValue == "pear");

	std::string shortestString = "";
	auto compareByLength = [](const std::string& a, const std::string& b) {
		return a.length() > b.length();
	};
	REQUIRE(FindMaxEx(vec, shortestString, compareByLength));
	REQUIRE(shortestString == "pear");
}

TEST_CASE("FindMaxEx default less - Empty vector")
{
	std::vector<int> vec;
	int maxValue = 0;
	REQUIRE(!FindMaxEx(vec, maxValue));
	REQUIRE(maxValue == 0);
}

TEST_CASE("FindMaxEx default less - Single element vector")
{
	std::vector<int> vec = { 99 };
	int maxValue = 0;
	REQUIRE(FindMaxEx(vec, maxValue));
	REQUIRE(maxValue == 99);
}

TEST_CASE("FindMaxEx default less - Multiple elements")
{
	std::vector<int> vec = { -10, -5, -20, -15, -30, -25 };
	int maxValue = 0;
	REQUIRE(FindMaxEx(vec, maxValue));
	REQUIRE(maxValue == -5);
}

TEST_CASE("FindMaxEx default less - Multiple elements with duplicates")
{
	std::vector<int> vec = { 5, 10, 5, 10, 3 };
	int maxValue = 0;
	REQUIRE(FindMaxEx(vec, maxValue));
	REQUIRE(maxValue == 10);
}

TEST_CASE("FindMaxEx default less - Different data types (double)")
{
	std::vector<double> vec = { -1.1, -3.3, -2.2, -3.3, -0.9 };
	double maxValue = 0.0;
	REQUIRE(FindMaxEx(vec, maxValue));
	REQUIRE(maxValue == -0.9);
}

TEST_CASE("FindMaxEx default less - Different data types (string)")
{
	std::vector<std::string> vec = { "zebra", "cat", "dog", "elephant" };
	std::string maxValue;
	REQUIRE(FindMaxEx(vec, maxValue));
	REQUIRE(maxValue == "zebra");
}

TEST_CASE("FindMaxEx dont modify maxValue when less throws an exception")
{
	unsigned n = 0;
	int max = 42;
	std::vector<int> vec = { 1, 2, 3, 5, 8, 13 };
	auto throwingLess = [&n](const int&, const int&) {
		if (n == 2)
		{
			throw std::runtime_error("Exception occurred");
		}
		n++;
		return true;
	};

	try
	{
		FindMaxEx(vec, max, throwingLess);
	}
	catch (const std::exception& ex)
	{
		using namespace std::literals;
		REQUIRE(ex.what() == "Exception occurred"s);
		REQUIRE(max == 42);
	}
}
