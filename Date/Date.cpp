#include "Date.h"

#include <chrono>
#include <format>
#include <stdexcept>

namespace
{
constexpr unsigned DAYS_EPOCH = 719'468;
constexpr unsigned MAX_EPOCH_DAYS = 2'932'896;

bool IsLeap(unsigned y) noexcept
{
	return y % 4 == 0 && (y % 100 != 0 || y % 400 == 0);
}

unsigned LastDayOfMonthCommonYear(unsigned m) noexcept
{
	constexpr unsigned char a[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	return a[m - 1];
}

// courtesy of Howard Hinnant
// https://howardhinnant.github.io/date_algorithms.html#last_day_of_month
unsigned LastDayOfMonth(unsigned m, unsigned y) noexcept
{
	return m != 2 || !IsLeap(y) ? LastDayOfMonthCommonYear(m) : 29u;
}

void AssertIsEpochInRange(unsigned epochDays)
{
	if (epochDays > MAX_EPOCH_DAYS)
	{
		throw std::out_of_range(std::format("Date is out of range [{} - {}]",
			Date::Min().ToString(), Date::Max().ToString()));
	}
}

void AssertIsDateValid(unsigned day, unsigned month, unsigned year)
{
	constexpr unsigned MAX_YEAR = 9999;
	constexpr unsigned MIN_YEAR = 1970;
	constexpr unsigned MAX_MONTH = 12;
	constexpr unsigned MIN_MONTH = 1;

	if (year < MIN_YEAR || year > MAX_YEAR)
	{
		throw std::out_of_range("Year must be in range from 1970 to 9999");
	}
	if (month < MIN_MONTH || month > MAX_MONTH)
	{
		throw std::out_of_range("Month must be in range from 1 to 12");
	}
	if (day > LastDayOfMonth(month, year) || day == 0)
	{
		throw std::out_of_range("Day is out of range of given month");
	}
}
} // namespace

Date Date::Min()
{
	return Date{};
}

Date Date::Max()
{
	return Date{ MAX_EPOCH_DAYS };
}

Date Date::Now()
{
	using namespace std::chrono;
	auto now = system_clock::now();
	auto epochDays = duration_cast<days>(now.time_since_epoch());

	return Date(epochDays.count());
}

Date::Date(unsigned daysSinceEpoch)
	: m_epochDays(daysSinceEpoch)
{
	AssertIsEpochInRange(m_epochDays);
}

Date::Date(unsigned day, unsigned month, unsigned year)
	: Date(FromDate(day, month, year))
{
	AssertIsDateValid(day, month, year);
}

Date::Date(unsigned day, Month month, unsigned year)
	: Date(day, static_cast<unsigned>(month), year)
{
}

unsigned Date::GetDay() const noexcept
{
	return std::get<0>(ToDate());
}

Month Date::GetMonth() const noexcept
{
	return static_cast<Month>(std::get<1>(ToDate()));
}

DayOfWeek Date::GetDayOfWeek() const noexcept
{
	return static_cast<DayOfWeek>((m_epochDays + 4) % 7);
}

unsigned Date::GetYear() const noexcept
{
	return std::get<2>(ToDate());
}

Date& Date::operator++()
{
	auto next = m_epochDays + 1;
	AssertIsEpochInRange(next);
	m_epochDays = next;

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
	auto prev = m_epochDays - 1;
	AssertIsEpochInRange(prev);
	m_epochDays = prev;

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
	auto newEpoch = m_epochDays + days;
	AssertIsEpochInRange(newEpoch);

	return Date(newEpoch);
}

Date Date::operator-(int days) const
{
	auto newEpoch = m_epochDays - days;
	AssertIsEpochInRange(newEpoch);

	return Date(newEpoch);
}

int Date::operator-(const Date& other) const
{
	return static_cast<int>(m_epochDays - other.m_epochDays);
}

Date& Date::operator+=(int days)
{
	Date temp = *this + days;
	*this = temp;

	return *this;
}

Date& Date::operator-=(int days)
{
	Date temp = *this - days;
	*this = temp;

	return *this;
}

std::string Date::ToString() const noexcept
{
	return std::format("{:02}.{:02}.{:04}",
		GetDay(),
		static_cast<unsigned>(GetMonth()),
		GetYear());
}

// courtesy of Howard Hinnant
// https://howardhinnant.github.io/date_algorithms.html#days_from_civil
unsigned Date::FromDate(unsigned day, unsigned month, unsigned year) const noexcept
{
	year -= month <= 2;
	const unsigned era = (year >= 0 ? year : year - 399) / 400;
	const unsigned yoe = year - era * 400;
	const unsigned doy = (153 * (month > 2 ? month - 3 : month + 9) + 2) / 5 + day - 1;
	const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
	return era * 146097 + doe - 719468;
}

// courtesy of Howard Hinnant
// https://howardhinnant.github.io/date_algorithms.html#civil_from_days
std::tuple<unsigned, unsigned, unsigned> Date::ToDate() const noexcept
{
	const unsigned z = m_epochDays + DAYS_EPOCH;

	const unsigned era = (z >= 0 ? z : z - 146096) / 146097;
	const unsigned doe = z - era * 146097;
	const unsigned yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;
	const unsigned y = yoe + era * 400;
	const unsigned doy = doe - (365 * yoe + yoe / 4 - yoe / 100);
	const unsigned mp = (5 * doy + 2) / 153;
	const unsigned d = doy - (153 * mp + 2) / 5 + 1;
	const unsigned m = mp < 10 ? mp + 3 : mp - 9;

	return std::tuple<unsigned, unsigned, unsigned>(d, m, y + (m <= 2));
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
	return os << date.ToString();
}

std::istream& operator>>(std::istream& is, Date& date)
{
	unsigned day, month, year;
	char dot1, dot2;

	if (!(is >> day >> dot1 >> month >> dot2 >> year))
	{
		is.setstate(std::ios::failbit);
		return is;
	}

	if (dot1 != '.' || dot2 != '.')
	{
		is.setstate(std::ios::failbit);
		return is;
	}

	try
	{
		date = Date(day, static_cast<Month>(month), year);
		is.setstate(std::ios::goodbit);
	}
	catch (const std::exception&)
	{
		is.setstate(std::ios::failbit);
	}

	return is;
}
