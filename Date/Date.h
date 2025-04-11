#pragma once
#include <chrono>
#include <istream>
#include <ostream>

enum class Month
{
	January = 1,
	February,
	March,
	April,
	May,
	June,
	July,
	August,
	September,
	October,
	November,
	December
};

enum class DayOfWeek
{
	Sunday = 0,
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday
};

class Date
{
public:
	Date();

	explicit Date(unsigned daysSinceEpoch);

	Date(unsigned day, unsigned month, unsigned year);
	Date(unsigned day, Month month, unsigned year);

	unsigned GetDay() const;

	Month GetMonth() const;

	DayOfWeek GetDayOfWeek() const;

	unsigned GetYear() const;

	Date& operator++();
	Date operator++(int);

	Date& operator--();
	Date operator--(int);

	Date operator+(int days) const;

	Date operator-(int days) const;
	int operator-(const Date& other) const;

	Date& operator+=(int days);
	Date& operator-=(int days);

	bool operator==(const Date& other) const = default;
	bool operator!=(const Date& other) const = default;

	bool operator>(const Date& other) const = default;
	bool operator<(const Date& other) const = default;

	bool operator>=(const Date& other) const = default;
	bool operator<=(const Date& other) const = default;

	friend std::ostream& operator<<(std::ostream& out, const Date& date);
	friend std::istream& operator>>(std::istream& in, Date& date);

private:
	explicit Date(const std::chrono::sys_days& timePoint);

	std::chrono::sys_days m_timepoint;
};
