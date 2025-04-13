#include "String.h"

#include <istream>
#include <ostream>

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

void String::EmplaceAllWithTerminator(const char* cString, size_t len)
{
	Base::Reserve(len + 1);

	for (size_t i = 0; i < len; ++i)
	{
		Base::EmplaceBack(cString[i]);
	}
	Base::EmplaceBack(TERMINATOR);
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
	os << str.Data();

	return os;
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
