#pragma once

#include <initializer_list>
#include <stdexcept>
#include <string>

#include "../MyVector/ContainerBase.hpp"
#include "../MyVector/Iteratable.hpp"

class String
	: public details::ContainerBase<char>
	, public details::Iteratable<String, char*, const char*>
{
	using Base = details::ContainerBase<char>;

public:
	String();

	String(const char* cString);

	String(const std::string& stlString);

	String(const std::initializer_list<char>& list);

	String(const char* cString, size_t len);

	char& operator[](size_t index);

	const char& operator[](size_t index) const;

	const char* Data() const;

	size_t Length() const;

	size_t Size() const;

	bool Empty() const;

	char& EmplaceBack(char&& ch);

	String& Append(const String& other);
	String& Append(const char* const cString, size_t len);
	String& Append(const char* const cString);

	String operator+(const String& other) const;
	String operator+(const std::string& stlString) const;
	String operator+(const char* const cString) const;

	friend String operator+(const std::string& stlString, const String& other);
	friend String operator+(const char* const cString, const String& other);

	String& operator+=(const String& other);
	String& operator+=(const char* const cString);

	bool operator==(const String& other) const;
	bool operator!=(const String& other) const;

	std::strong_ordering operator<=>(const String& other) const;

	friend std::ostream& operator<<(std::ostream& os, const String& str);
	friend std::istream& operator>>(std::istream& is, String& str);

private:
	String& EmplaceAllWithTerminator(const char* cString, size_t len);
};
