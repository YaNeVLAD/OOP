#include "catch2.h"
#include <sstream>
#include <stdexcept>
#include <string>

TEST_CASE("Empty vector must remain empty after processing", "[ProcessNumber]")
{
	std::vector<double> empty;
	ProcessNumbers(empty);

	REQUIRE(empty.empty());
}

TEST_CASE("Function reads empty string as empty vector", "[ReadNumbers]")
{
	std::istringstream str;
	auto result = ReadNumbers(str);
	REQUIRE(result.empty());
}

TEST_CASE("Function prints empty vector as empty string", "[PrintSortedNumbers]")
{
	std::vector<double> vector;
	std::ostringstream ossExpected;
	PrintSortedNumbers(ossExpected, vector);
	REQUIRE(ossExpected.str().empty());
}

TEST_CASE("Every element of the passed vector is multiplied by min element of this vector", "[ProcessNumber]")
{
	std::vector<double> numbers = { 3, 2, 4, 1 };
	ProcessNumbers(numbers);

	std::vector<double> expected = { 3, 2, 4, 1 };
	REQUIRE(numbers == expected);

	std::vector<double> numbers2 = { 5, 10, 15 };
	ProcessNumbers(numbers2);

	std::vector<double> expected2 = { 25, 50, 75 };
	REQUIRE(numbers2 == expected2);
}

TEST_CASE("Vector is successfully created from istream", "[ReadNumbers]")
{
	std::istringstream iss("1	2    3 \n \n \n            4");

	std::vector<double> res = { 1, 2, 3, 4 };
	REQUIRE(ReadNumbers(iss) == res);
}

TEST_CASE("Printed vector is sorted", "[PrintSortedNumbers]")
{
	std::vector<double> numbers = { 3, 1, 4, 2 };
	std::ostringstream oss;
	PrintSortedNumbers(oss, numbers);

	std::vector<double> sortedNumbers = { 1, 2, 3, 4 };
	std::ostringstream ossExpected;
	PrintSortedNumbers(ossExpected, sortedNumbers);

	REQUIRE(oss.str() == ossExpected.str());
}

TEST_CASE("Function must throw an exception on invalid number passed", "[ReadNumbers]")
{
	std::istringstream iss("1 2 abc 4");
	REQUIRE_THROWS_AS(ReadNumbers(iss), std::invalid_argument);
}
