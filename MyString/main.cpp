#include "String.h"
#include <iostream>

#include <string>

int main()
{
	std::string stlStr = "1\0 234";
	String str = { "12345" };
	String str1 = { "3210", 3 };
	String str2 = { '1', '\0', '2', '3' };
	String str3 = stlStr;

	size_t len = std::strlen(str.Data());
	size_t len1 = std::strlen(str1.Data());
	size_t len2 = std::strlen(str2.Data());

	for (const char& ch : str)
	{
		std::cout << ch;
	}
	std::cout << std::endl;
}
