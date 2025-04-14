#include "String.h"

#include <istream>
#include <memory>
#include <ostream>

namespace
{
String AppendUnwrapped(
	const char* const lhsData, size_t lhsSize, const char* const rhsData, size_t rhsSize)
{
	String result;

	if (lhsData && lhsSize > 0)
	{
		result.Append(lhsData, lhsSize);
	}
	if (rhsData && rhsSize > 0)
	{
		result.Append(rhsData, rhsSize);
	}

	return result;
}
} // namespace

constexpr const char* EMPTY_STRING = "";
constexpr char TERMINATOR = '\0';

String::String()
	: String(EMPTY_STRING, 0)
{
}

String::String(const char* cString)
	: String(cString, std::strlen(cString))
{
}

String::String(const std::string& stlString)
	: String(stlString.data(), stlString.size())
{
}

String::String(const std::initializer_list<char>& list)
	: String(list.begin(), list.size())
{
}

String::String(const char* cString, size_t len)
	: Base()
{
	EmplaceAllWithTerminator(cString, len);
}

char& String::operator[](size_t index)
{
	if (index >= Size())
	{
		throw std::out_of_range("String index is out of range");
	}

	return *(Base::Begin() + index);
}

const char& String::operator[](size_t index) const
{
	return const_cast<String&>(*this)[index];
}

const char* String::Data() const
{
	return Base::Begin();
}

size_t String::Length() const
{
	return Size();
}

size_t String::Size() const
{
	return Base::Size() == 0 ? 0 : Base::Size() - 1;
}

bool String::Empty() const
{
	return Size() == 0;
}

char& String::EmplaceBack(char&& ch)
{
	PopBack();
	char& temp = Base::EmplaceBack(ch);
	Base::EmplaceBack(TERMINATOR);

	return temp;
}

String& String::Append(const String& other)
{
	return EmplaceAllWithTerminator(other.Data(), other.Size());
}

String& String::Append(const char* const cString, size_t len)
{
	return EmplaceAllWithTerminator(cString, len);
}

String& String::Append(const char* const cString)
{
	return EmplaceAllWithTerminator(cString, std::strlen(cString));
}

String String::operator+(const String& other) const
{
	return AppendUnwrapped(Data(), Size(), other.Data(), other.Size());
}

String String::operator+(const std::string& stlString) const
{
	return AppendUnwrapped(Data(), Size(), stlString.data(), stlString.size());
}

String String::operator+(const char* const cString) const
{
	return AppendUnwrapped(Data(), Size(), cString, std::strlen(cString));
}

String& String::operator+=(const String& other)
{
	return Append(other);
}

String& String::operator+=(const char* const cString)
{
	return Append(cString);
}

bool String::operator==(const String& other) const
{
	if (Size() != other.Size())
	{
		return false;
	}

	for (size_t i = 0; i < Size(); ++i)
	{
		if ((*this)[i] != other[i])
		{
			return false;
		}
	}

	return true;
}

bool String::operator!=(const String& other) const
{
	return !(*this == other);
}

std::strong_ordering String::operator<=>(const String& other) const
{
	return std::lexicographical_compare_three_way(begin(), end(), other.begin(), other.end());
}

String& String::EmplaceAllWithTerminator(const char* cString, size_t len)
{
	Base::PopBack();

	Base::EmplaceAllBack(cString, len);

	Base::EmplaceBack(TERMINATOR);

	return *this;
}

String operator+(const std::string& stlString, const String& other)
{
	return AppendUnwrapped(stlString.data(), stlString.size(), other.Data(), other.Size());
}

String operator+(const char* const cString, const String& other)
{
	return AppendUnwrapped(cString, std::strlen(cString), other.Data(), other.Size());
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
	return os.write(str.Data(), str.Size());
}

std::istream& operator>>(std::istream& is, String& str)
{
	std::string line;
	if (!(is >> line))
	{
		is.setstate(std::ios::failbit);
		return is;
	}

	str = line;
	is.setstate(std::ios::goodbit);

	return is;
}
