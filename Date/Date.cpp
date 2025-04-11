#include "Date.h"

#include <format>
#include <stdexcept>

#include "DateConstants.hpp"

Date::Date()
	: m_timestamp(0)
{
}

Date::Date(unsigned timestamp)
	: m_timestamp(timestamp)
{
	AssertIsTimestampInRange();
}

Date::Date(unsigned day, unsigned month, unsigned year)
	: Date(day, static_cast<Month>(month), year)
{
}

Date::Date(unsigned day, Month month, unsigned year)
	: m_timestamp(DateToTimestamp(day, month, year))
{
	AssertIsDateInRange(day, month, year);
}

unsigned Date::GetDay() const
{
	return std::get<0>(TimestampToDate());
}

Month Date::GetMonth() const
{
	return std::get<1>(TimestampToDate());
}

DayOfWeek Date::GetDayOfWeek() const
{
	return static_cast<DayOfWeek>((m_timestamp + 4) % 7);
}

unsigned Date::GetYear() const
{
	return std::get<2>(TimestampToDate());
}

Date& Date::operator++()
{
	AssertIsTimestampInRange(m_timestamp + 1);
	++m_timestamp;
	return *this;
}

Date Date::operator++(int)
{
	Date temp = *this;
	AssertIsTimestampInRange(m_timestamp + 1);
	++(*this);
	return temp;
}

Date& Date::operator--()
{
	AssertIsTimestampInRange(m_timestamp - 1);
	--m_timestamp;
	return *this;
}

Date Date::operator--(int)
{
	Date temp = *this;
	AssertIsTimestampInRange(m_timestamp - 1);
	--(*this);
	return temp;
}

Date Date::operator+(unsigned days)
{
	AssertIsTimestampInRange(m_timestamp + days);
	return Date(m_timestamp + days);
}

Date Date::operator-(unsigned days)
{
	AssertIsTimestampInRange(m_timestamp - days);
	return Date(m_timestamp - days);
}

int Date::operator-(const Date& other)
{
	return m_timestamp - other.m_timestamp;
}

Date& Date::operator+=(unsigned days)
{
	AssertIsTimestampInRange(m_timestamp + days);
	m_timestamp += days;
	return *this;
}

Date& Date::operator-=(unsigned days)
{
	AssertIsTimestampInRange(m_timestamp - days);
	m_timestamp -= days;
	return *this;
}

bool Date::operator==(const Date& other)
{
	return m_timestamp == other.m_timestamp;
}

bool Date::operator!=(const Date& other)
{
	return !(this->operator==(other));
}

bool Date::operator>(const Date& other)
{
	return m_timestamp > other.m_timestamp;
}

bool Date::operator<(const Date& other)
{
	return m_timestamp < other.m_timestamp;
}

bool Date::operator>=(const Date& other)
{
	return !(this->operator<(other));
}

bool Date::operator<=(const Date& other)
{
	return !(this->operator>(other));
}

void Date::AssertIsTimestampInRange(std::optional<unsigned> timestamp) const
{
	unsigned value = timestamp.has_value() ? timestamp.value() : m_timestamp;
	if (value > s_maxTimestamp)
	{
		throw std::logic_error("Date must be in range from 01:01:1970 to 31:12:9999");
	}
}

void Date::AssertIsDateInRange(unsigned day, Month month, unsigned year) const
{
	if (day > 31)
	{
		throw std::logic_error("Day must be in range from 1 to 31");
	}
	if (month > Month::December || month < Month::January)
	{
		throw std::logic_error("Month must be in range from 1 to 12");
	}
	if (year < 1970 || year > 9999)
	{
		throw std::runtime_error("Year must be in range from 1970 to 9999");
	}
	AssertIsTimestampInRange(DateToTimestamp(day, month, year));
}

std::tuple<unsigned, Month, unsigned> Date::TimestampToDate() const
{
	using namespace date_constants;

	unsigned days = m_timestamp + 719468;
	unsigned era = days / 146097;
	days -= era * 146097;
	unsigned yoe = (days - days / 1460 + days / 36524 - days / 146096) / 365;
	unsigned year = era * 400 + yoe;
	unsigned doy = days - (yoe * 365 + yoe / 4 - yoe / 100);

	if (doy >= 367)
	{
		year += 1;
		doy -= 366;
	}

	unsigned mp = (5 * doy + 2) / 153;
	unsigned day = doy - (153 * mp + 2) / 5 + 1;
	Month month = static_cast<Month>(mp + (mp < 10 ? 3 : -9));

	return { day, month, year + (mp >= 10 ? 1 : 0) };
}

unsigned Date::DateToTimestamp(unsigned day, Month month, unsigned year) const
{
	unsigned m = static_cast<unsigned>(month);
	unsigned y = year - (m < 3 ? 1 : 0);

	unsigned era = y / 400;
	unsigned yoe = y % 400;
	unsigned doy = (153 * (m > 2 ? m - 3 : m + 9) + 2) / 5 + day - 1;
	unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;

	return era * 146097 + doe - 719468;
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
	os << std::format("{:02}.{:02}.{:04}",
		date.GetDay(), static_cast<int>(date.GetMonth()), date.GetYear());

	return os;
}

std::istream& operator>>(std::istream& is, Date& date)
{
	unsigned day = 0, month = 0, year = 0;
	char dot1 = 0, dot2 = 0;

	if (is >> day >> dot1 >> month >> dot2 >> year)
	{
		if (dot1 == '.' && dot2 == '.')
		{
			try
			{
				date = Date(day, static_cast<Month>(month), year);
			}
			catch (const std::exception&)
			{
				is.setstate(std::ios::failbit);
			}
		}
	}
	else
	{
		if (!is.fail())
		{
			is.setstate(std::ios::failbit);
		}
	}

	return is;
}
