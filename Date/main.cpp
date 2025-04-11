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
	Date date(01, 01, 1970);
	Date date2(02, 01, 1970);
	// std::cout << std::boolalpha << (date <= date2) << std::endl;
	std::cout << date++ << std::endl;
	std::cout << date << std::endl;
	Date id;
	if (std::cin >> id)
	{
		std::cout << id << std::endl;
	}
	else
	{
		std::cout << "Wrong date" << std::endl;
	}

	std::cout << date.GetDay() << std::endl;
	std::cout << static_cast<int>(date.GetMonth()) << std::endl;
	std::cout << date.GetYear() << std::endl;
	std::cout << DayOfWeekToString(date.GetDayOfWeek()) << std::endl;
}
