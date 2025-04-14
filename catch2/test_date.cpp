#include "catch2.h"

TEST_CASE("Constructors")
{
	SECTION("Default constructor")
	{
		Date date;
		REQUIRE(date.GetDay() == 1);
		REQUIRE(date.GetMonth() == Month::January);
		REQUIRE(date.GetYear() == 1970);
	}

	SECTION("From epoch days")
	{
		Date date(10);
		REQUIRE(date.GetDay() == 11);
		REQUIRE(date.GetMonth() == Month::January);
		REQUIRE(date.GetYear() == 1970);
	}

	SECTION("From day, month, year")
	{
		Date date(15, Month::June, 2023);
		REQUIRE(date.GetDay() == 15);
		REQUIRE(date.GetMonth() == Month::June);
		REQUIRE(date.GetYear() == 2023);
	}

	SECTION("From numeric month")
	{
		Date date(31, 12, 2023);
		REQUIRE(date.GetDay() == 31);
		REQUIRE(date.GetMonth() == Month::December);
		REQUIRE(date.GetYear() == 2023);
	}

	SECTION("Invalid dates throw exceptions")
	{
		REQUIRE_THROWS_AS(Date(29, 2, 2023), std::out_of_range);
		REQUIRE_THROWS_AS(Date(32, 1, 2023), std::out_of_range);
		REQUIRE_THROWS_AS(Date(0, 1, 2023), std::out_of_range);
		REQUIRE_THROWS_AS(Date(1, 13, 2023), std::out_of_range);
		REQUIRE_THROWS_AS(Date(1, 0, 2023), std::out_of_range);
		REQUIRE_THROWS_AS(Date(1, 1, 1969), std::out_of_range);
		REQUIRE_THROWS_AS(Date(1, 1, 10000), std::out_of_range);
	}
}

TEST_CASE("Properties")
{
	Date date(14, Month::April, 2025);

	SECTION("Day of week")
	{
		REQUIRE(date.GetDayOfWeek() == DayOfWeek::Monday);
	}

	SECTION("Day of month")
	{
		REQUIRE(date.GetDay() == 14);
	}

	SECTION("Month")
	{
		REQUIRE(date.GetMonth() == Month::April);
	}

	SECTION("Year")
	{
		REQUIRE(date.GetYear() == 2025);
	}
}

TEST_CASE("Operator overloads")
{
	SECTION("Increment operators")
	{
		Date date1(15, Month::June, 2023);

		Date prev = date1;
		Date post = date1++;
		REQUIRE(post == prev);
		REQUIRE(date1 == Date(16, Month::June, 2023));

		Date& ref = ++date1;
		REQUIRE(ref == Date(17, Month::June, 2023));
		REQUIRE(date1 == Date(17, Month::June, 2023));
	}

	SECTION("Decrement operators")
	{
		Date date2(20, Month::June, 2023);

		Date prev = date2;
		Date post = date2--;
		REQUIRE(post == prev);
		REQUIRE(date2 == Date(19, Month::June, 2023));

		Date& ref = --date2;
		REQUIRE(ref == Date(18, Month::June, 2023));
		REQUIRE(date2 == Date(18, Month::June, 2023));
	}

	SECTION("Addition and subtraction")
	{
		Date date1(15, Month::June, 2023);
		Date date2(20, Month::June, 2023);

		Date newDate = date1 + 5;
		REQUIRE(newDate == Date(20, Month::June, 2023));

		newDate = date2 - 5;
		REQUIRE(newDate == Date(15, Month::June, 2023));

		int diff = date2 - date1;
		REQUIRE(diff == 5);

		date1 += 5;
		REQUIRE(date1 == date2);

		date2 -= 5;
		REQUIRE(date2 == Date(15, Month::June, 2023));
	}

	SECTION("Comparison operators")
	{
		Date date1(15, Month::June, 2023);
		Date date2(20, Month::June, 2023);

		REQUIRE(date1 < date2);
		REQUIRE(date1 <= date2);
		REQUIRE(date2 > date1);
		REQUIRE(date2 >= date1);
		REQUIRE(date1 != date2);
		REQUIRE(date1 == Date(15, Month::June, 2023));
	}
}

TEST_CASE("I/O operators overloads")
{
	SECTION("Output operator")
	{
		Date date(15, Month::June, 2023);
		std::ostringstream oss;
		oss << date;
		REQUIRE(oss.str() == "15.06.2023");
	}

	SECTION("Input operator - valid date")
	{
		std::istringstream iss("15.06.2023");
		Date date;
		iss >> date;
		REQUIRE(date == Date(15, Month::June, 2023));
	}

	SECTION("Input operator - invalid format")
	{
		std::istringstream iss("15-06-2023");
		Date date;
		iss >> date;
		REQUIRE(iss.fail());
	}

	SECTION("Input operator - invalid date")
	{
		std::istringstream iss("32.06.2023");
		Date date;
		iss >> date;
		REQUIRE(iss.fail());
	}
}

TEST_CASE("Edge cases")
{
	SECTION("Min and Max dates")
	{
		Date min = Date::Min();
		Date max = Date::Max();

		REQUIRE(min == Date(1, Month::January, 1970));
		REQUIRE(max == Date(31, Month::December, 9999));

		REQUIRE_THROWS_AS(min - 1, std::out_of_range);
		REQUIRE_THROWS_AS(max + 1, std::out_of_range);
	}

	SECTION("Month boundaries")
	{
		Date jan31(31, Month::January, 2023);
		REQUIRE((jan31 + 1) == Date(1, Month::February, 2023));

		Date feb28(28, Month::February, 2020);
		REQUIRE((feb28 + 1) == Date(29, Month::February, 2020));

		Date feb28n(28, Month::February, 2021);
		REQUIRE((feb28n + 1) == Date(1, Month::March, 2021));

		Date dec31(31, Month::December, 2023);
		REQUIRE((dec31 + 1) == Date(1, Month::January, 2024));
	}

	SECTION("Year boundaries")
	{
		Date dec31_2023(31, Month::December, 2023);
		REQUIRE((dec31_2023 + 1) == Date(1, Month::January, 2024));

		Date jan1_2024(1, Month::January, 2024);
		REQUIRE((jan1_2024 - 1) == dec31_2023);
	}
}
