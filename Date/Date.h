#pragma once

#include <istream>
#include <ostream>
#include <tuple>

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
	static Date Min();
	static Date Max();
	static Date Now();

	Date() = default;

	explicit Date(unsigned daysSinceEpoch);

	Date(unsigned day, unsigned month, unsigned year);
	Date(unsigned day, Month month, unsigned year);

	unsigned GetDay() const noexcept;

	Month GetMonth() const noexcept;

	DayOfWeek GetDayOfWeek() const noexcept;

	unsigned GetYear() const noexcept;

	Date& operator++();
	Date operator++(int);

	Date& operator--();
	Date operator--(int);

	Date operator+(int days) const;

	Date operator-(int days) const;
	int operator-(const Date& other) const;

	Date& operator+=(int days);
	Date& operator-=(int days);

	auto operator<=>(const Date& other) const noexcept = default;

	friend std::ostream& operator<<(std::ostream& out, const Date& date);
	friend std::istream& operator>>(std::istream& in, Date& date);

	std::string ToString() const noexcept;

private:
	constexpr unsigned FromDate(unsigned day, unsigned month, unsigned year) const noexcept;

	constexpr std::tuple<unsigned, unsigned, unsigned> ToDate() const noexcept;

	unsigned m_epochDays = 0;
};
