#include "catch2.h"

using namespace GeneratePrimes;

TEST_CASE("GeneratePrimeNumbersSet - Basic functionality", "[GeneratePrimeNumbersSet]")
{
	SECTION("Upper bound is 10")
	{
		std::set<int> expected = { 2, 3, 5, 7 };
		REQUIRE(GeneratePrimeNumbersSet(10) == expected);
	}

	SECTION("Upper bound is 20")
	{
		std::set<int> expected = { 2, 3, 5, 7, 11, 13, 17, 19 };
		REQUIRE(GeneratePrimeNumbersSet(20) == expected);
	}

	SECTION("Upper bound is 1")
	{
		std::set<int> expected = {};
		REQUIRE(GeneratePrimeNumbersSet(1) == expected);
	}

	SECTION("Upper bound is 2")
	{
		std::set<int> expected = { 2 };
		REQUIRE(GeneratePrimeNumbersSet(2) == expected);
	}
}

TEST_CASE("GeneratePrimeNumbersSet - Edge cases", "[GeneratePrimeNumbersSet]")
{
	SECTION("Upper bound is 0")
	{
		std::set<int> expected = {};
		REQUIRE(GeneratePrimeNumbersSet(0) == expected);
	}

	SECTION("Upper bound is negative")
	{
		std::set<int> expected = {};
		REQUIRE(GeneratePrimeNumbersSet(-10) == expected);
	}

	SECTION("Upper bound is MAX_RANGE")
	{
		REQUIRE_NOTHROW(GeneratePrimeNumbersSet(MAX_RANGE));
	}

	SECTION("Upper bound is greater than MAX_RANGE")
	{
		REQUIRE_THROWS_AS(GeneratePrimeNumbersSet(MAX_RANGE + 1), std::out_of_range);
	}
}

TEST_CASE("GeneratePrimeNumbersSet - Large upper bound", "[GeneratePrimeNumbersSet]")
{
	SECTION("Upper bound is 100")
	{
		std::set<int> expected = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
		REQUIRE(GeneratePrimeNumbersSet(100) == expected);
	}

	SECTION("Upper bound is 1000")
	{
		// Проверка количества простых чисел до 1000
		REQUIRE(GeneratePrimeNumbersSet(1000).size() == 168);
	}
}
