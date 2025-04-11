#include <iostream>

#include "Date.h"

std::string DayOfWeekToString(DayOfWeek weekDay)
{
	switch (weekDay)
	{
	case DayOfWeek::Sunday:
		return "Sunday";
	case DayOfWeek::Monday:
		return "Monday";
	case DayOfWeek::Tuesday:
		return "Tuesday";
	case DayOfWeek::Wednesday:
		return "Wednesday";
	case DayOfWeek::Thursday:
		return "Thursday";
	case DayOfWeek::Friday:
		return "Friday";
	case DayOfWeek::Saturday:
		return "Saturday";
	default:
		return "Unknown day of week";
	}
}

int main()
{
	try
	{
		Date date;
		if (std::cin >> date)
		{
			std::cout << date << std::endl;
		}
		else
		{
			std::cout << "WRONG DATE" << std::endl;
		}

		std::cout << date.GetDay() << std::endl;
		std::cout << static_cast<int>(date.GetMonth()) << std::endl;
		std::cout << date.GetYear() << std::endl;
		std::cout << DayOfWeekToString(date.GetDayOfWeek()) << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}
