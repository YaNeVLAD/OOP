#include "Date.h"

#include <format>
#include <stdexcept>

using namespace std::chrono_literals;

namespace
{

using InnerYear = std::chrono::year;
using InnerMonth = std::chrono::month;
using InnerDay = std::chrono::day;
using InnerEpochDays = std::chrono::sys_days;
using InnerDate = std::chrono::year_month_day;
using InnerDays = std::chrono::days;
using InnerDayOfWeek = std::chrono::weekday;

constexpr unsigned MAX_YEAR = 9999;
constexpr unsigned MIN_YEAR = 1970;
constexpr unsigned MIN_MONTH = 1;
constexpr unsigned MAX_MONTH = 12;

constexpr InnerEpochDays MIN_DATE = InnerDate{ 1970y / std::chrono::January / 1d };
constexpr InnerEpochDays MAX_DATE = InnerDate{ 9999y / std::chrono::December / 31d };

std::string DateToString(const InnerDate& date)
{
	return std::format("{:02}.{:02}.{:04}",
		static_cast<unsigned>(date.day()),
		static_cast<unsigned>(date.month()),
		static_cast<int>(date.year()));
}

void AssertIsTimePointInRange(const InnerEpochDays& timePoint)
{
	if (timePoint < MIN_DATE || timePoint > MAX_DATE)
	{
		auto date = InnerDate{ timePoint };

		throw std::out_of_range(
			std::format("Date {} is outside the valid range [{}, {}]",
				DateToString(date),
				DateToString(MIN_DATE),
				DateToString(MAX_DATE)));
	}
}

InnerDate ValidateDate(unsigned day, unsigned month, unsigned year)
{
	if (year < MIN_YEAR || year > MAX_YEAR)
	{
		throw std::out_of_range(std::format("Year must be in range from {} ot {}",
			MIN_YEAR, MAX_YEAR));
	}
	if (month < MIN_MONTH || month > MAX_MONTH)
	{
		throw std::out_of_range(std::format("Month must be in range from {} ot {}",
			MIN_MONTH, MAX_MONTH));
	}

	InnerDate date = InnerYear(year) / InnerMonth{ month } / InnerDay{ day };

	if (!date.ok())
	{
		throw std::invalid_argument("Invalid date components (e.g., day out of range for month)");
	}

	return date;
}

} // namespace

Date::Date()
	: m_timepoint(MIN_DATE)
{
}

Date::Date(unsigned daysSinceEpoch)
	: m_timepoint(MIN_DATE + InnerDays{ daysSinceEpoch })
{
	AssertIsTimePointInRange(m_timepoint);
}

Date::Date(unsigned day, unsigned month, unsigned year)
{
	auto date = ValidateDate(day, month, year);

	m_timepoint = InnerEpochDays{ date };

	AssertIsTimePointInRange(m_timepoint);
}

Date::Date(unsigned day, Month month, unsigned year)
	: Date(day, static_cast<unsigned>(month), year)
{
}

unsigned Date::GetDay() const
{
	return static_cast<unsigned>(InnerDate{ m_timepoint }.day());
}

Month Date::GetMonth() const
{
	return static_cast<Month>(static_cast<unsigned>(InnerDate{ m_timepoint }.month()));
}

DayOfWeek Date::GetDayOfWeek() const
{
	auto wd = InnerDayOfWeek{ m_timepoint };
	return static_cast<DayOfWeek>(wd.c_encoding());
}

unsigned Date::GetYear() const
{
	return static_cast<unsigned>(static_cast<int>(InnerDate{ m_timepoint }.year()));
}

Date& Date::operator++()
{
	auto next = m_timepoint + InnerDays{ 1 };
	AssertIsTimePointInRange(next);
	m_timepoint = next;

	return *this;
}

Date Date::operator++(int)
{
	Date temp = *this;
	++(*this);

	return temp;
}

Date& Date::operator--()
{
	auto prev = m_timepoint - InnerDays{ 1 };
	AssertIsTimePointInRange(prev);
	m_timepoint = prev;

	return *this;
}

Date Date::operator--(int)
{
	Date temp = *this;
	--(*this);

	return temp;
}

Date Date::operator+(int days) const
{
	auto newTimePoint = m_timepoint + InnerDays{ days };
	AssertIsTimePointInRange(newTimePoint);

	return Date(newTimePoint);
}

Date Date::operator-(int days) const
{
	auto newTimePoint = m_timepoint + InnerDays{ days };
	AssertIsTimePointInRange(newTimePoint);

	return Date(newTimePoint);
}

int Date::operator-(const Date& other) const
{
	return static_cast<int>((m_timepoint - other.m_timepoint).count());
}

Date& Date::operator+=(int days)
{
	auto newTimePoint = m_timepoint + InnerDays{ days };
	AssertIsTimePointInRange(newTimePoint);
	m_timepoint = newTimePoint;

	return *this;
}

Date& Date::operator-=(int days)
{
	auto newTimePoint = m_timepoint - InnerDays{ days };
	AssertIsTimePointInRange(newTimePoint);
	m_timepoint = newTimePoint;

	return *this;
}

Date::Date(const std::chrono::sys_days& timePoint)
	: m_timepoint(timePoint)
{
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
	os << DateToString(date.m_timepoint);

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
