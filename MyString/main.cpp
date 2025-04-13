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

	String s1 = "one";
	String s2 = "ONE";

	String s3 = "two";
	String s4 = "four";

	String s5 = "three";
	String s6 = "two";

	String is;

	std::cin >> is;
	std::cout << is << std::endl;
	std::cout << std::boolalpha << (s1 == s2) << std::endl;
	std::cout << std::boolalpha << (s3 > s4) << std::endl;
	std::cout << std::boolalpha << (s5 < s6) << std::endl;

	size_t len = std::strlen(str.Data());
	size_t len1 = std::strlen(str1.Data());
	size_t len2 = std::strlen(str2.Data());

	for (const char& ch : str)
	{
		std::cout << ch;
	}
	std::cout << std::endl;
}
