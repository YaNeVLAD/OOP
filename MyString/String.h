#pragma once

#include <initializer_list>
#include <stdexcept>
#include <string>

#include "ContainerBase.hpp"
#include "Iteratable.hpp"

class String
	: public details::ContainerBase<char>
	, public details::Iteratable<String, char*, const char*>
{
	using Base = details::ContainerBase<char>;

public:
	String();

	String(const char* cString);

	String(const std::string& stlString);

	String(const char* cString, size_t len);

	String(const std::initializer_list<char>& list);

	char& operator[](size_t index);

	const char& operator[](size_t index) const;

	const char* Data() const;

	size_t Length() const;

	size_t Size() const;

	bool Empty() const;

private:
	void EmplaceAllWithTerminator(const char* cString, size_t len);
};
