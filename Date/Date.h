#pragma once
#include <istream>
#include <optional>
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
	Sunday,
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

	explicit Date(unsigned timestamp);

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

	Date operator+(unsigned days);

	Date operator-(unsigned days);
	int operator-(const Date& other);

	Date& operator+=(unsigned days);
	Date& operator-=(unsigned days);

	bool operator==(const Date& other);
	bool operator!=(const Date& other);

	bool operator>(const Date& other);
	bool operator<(const Date& other);

	bool operator>=(const Date& other);
	bool operator<=(const Date& other);

	friend std::ostream& operator<<(std::ostream& out, const Date& date);
	friend std::istream& operator>>(std::istream& in, Date& date);

private:
	void AssertIsTimestampInRange(std::optional<unsigned> timestamp = std::nullopt) const;
	void AssertIsDateInRange(unsigned day, Month month, unsigned year) const;

	std::tuple<unsigned, Month, unsigned> TimestampToDate() const;

	unsigned DateToTimestamp(unsigned day, Month month, unsigned year) const;

	unsigned m_timestamp;

	static constexpr unsigned s_maxTimestamp = 2932896;
};
