#include "String.h"

#include <cassert>

String::String()
	: Base()
{
	Base::EmplaceBack('\0');
}

String::String(const char* cString)
	: Base()
{
	size_t len = std::strlen(cString);
	EmplaceAllWithTerminator(cString, len);
}

String::String(const std::string& stlString)
	: Base()
{
	EmplaceAllWithTerminator(stlString.data(), stlString.size());
}

String::String(const char* cString, size_t len)
	: Base()
{
	EmplaceAllWithTerminator(cString, len);
}

String::String(const std::initializer_list<char>& list)
	: Base()
{
	EmplaceAllWithTerminator(list.begin(), list.size());
}

char& String::operator[](size_t index)
{
	if (index >= Base::Size())
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

void String::EmplaceAllWithTerminator(const char* cString, size_t len)
{
	Base::Reserve(len + 1);

	for (size_t i = 0; i < len; ++i)
	{
		Base::EmplaceBack(cString[i]);
	}
	Base::EmplaceBack('\0');
}
