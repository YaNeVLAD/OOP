#include "catch2.h"

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
		REQUIRE_NOTHROW(GeneratePrimeNumbersSet(100'000'000));
	}

	SECTION("Upper bound is greater than MAX_RANGE")
	{
		REQUIRE_THROWS_AS(GeneratePrimeNumbersSet(100'000'000 + 1), std::out_of_range);
	}
}

#ifndef DEBUG
TEST_CASE("Function finds all 5'761'455 primes in range of 100'000'000", "[GeneratePrimeNumbersSet]")
{
	auto set = GeneratePrimeNumbersSet(100'000'000);
	REQUIRE(set.size() == 5'761'455);
}

TEST_CASE("GeneratePrimeNumbersSet - Large upper bound", "[GeneratePrimeNumbersSet]")
{
	SECTION("Upper bound is 100")
	{
		std::set<int> expected = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
		REQUIRE(GeneratePrimeNumbersSet(100).size() == 25);
	}

	SECTION("Upper bound is 1000")
	{
		// Проверка количества простых чисел до 1000
		REQUIRE(GeneratePrimeNumbersSet(1000).size() == 168);
	}
}
#endif // DEBUG
