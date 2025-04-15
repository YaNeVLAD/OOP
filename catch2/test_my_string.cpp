#include "catch2.h"

#include <csignal>
#include <cstring>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

bool CheckData(const String& s, const char* expected)
{
	if (!s.Data() || !expected)
	{
		return false;
	}
	return strcmp(s.Data(), expected) == 0;
}

TEST_CASE("String Constructors", "[string][constructor]")
{

	SECTION("Default constructor")
	{
		String s;
		REQUIRE(s.Size() == 0);
		REQUIRE(s.Length() == 0);
		REQUIRE(s.Empty());
		REQUIRE(CheckData(s, ""));
	}

	SECTION("Constructor from C-string")
	{
		const char* cstr = "hello world";
		String s(cstr);
		REQUIRE(s.Size() == strlen(cstr));
		REQUIRE(s.Length() == strlen(cstr));
		REQUIRE_FALSE(s.Empty());
		REQUIRE(CheckData(s, cstr));

		String s_empty("");
		REQUIRE(s_empty.Size() == 0);
		REQUIRE(s_empty.Empty());
		REQUIRE(CheckData(s_empty, ""));
	}

	SECTION("Constructor from std::string")
	{
		std::string std_str = "hello std::string";
		String s(std_str);
		REQUIRE(s.Size() == std_str.size());
		REQUIRE_FALSE(s.Empty());
		REQUIRE(CheckData(s, std_str.c_str()));

		std::string std_empty = "";
		String s_empty(std_empty);
		REQUIRE(s_empty.Size() == 0);
		REQUIRE(s_empty.Empty());
		REQUIRE(CheckData(s_empty, ""));
	}

	SECTION("Constructor from initializer_list")
	{
		String s({ 't', 'e', 's', 't' });
		REQUIRE(s.Size() == 4);
		REQUIRE_FALSE(s.Empty());
		REQUIRE(CheckData(s, "test"));

		String s_empty({});
		REQUIRE(s_empty.Size() == 0);
		REQUIRE(s_empty.Empty());
		REQUIRE(CheckData(s_empty, ""));
	}

	SECTION("Constructor from C-string with length")
	{
		const char* data = "hello\0world";
		String s(data, 5);
		REQUIRE(s.Size() == 5);
		REQUIRE(memcmp(s.Data(), "hello", 5) == 0);
		REQUIRE(s.Data()[5] == '\0');
		REQUIRE(CheckData(s, "hello"));

		String s_part(data, 11);
		REQUIRE(s_part.Size() == 11);
		REQUIRE(memcmp(s_part.Data(), data, 11) == 0);
		REQUIRE(s_part.Data()[11] == '\0');

		String s_zero(data, 0);
		REQUIRE(s_zero.Size() == 0);
		REQUIRE(s_zero.Empty());
		REQUIRE(CheckData(s_zero, ""));
		// Добавить тесты на подачу длины большей, чем сама строка
	}

	SECTION("Copy constructor")
	{
		String s1("copy me");
		String s2 = s1;

		REQUIRE(s2.Size() == s1.Size());
		REQUIRE(CheckData(s2, "copy me"));
		REQUIRE(s1.Data() != s2.Data());

		s2[0] = 'X';
		REQUIRE(CheckData(s1, "copy me"));
		REQUIRE(CheckData(s2, "Xopy me"));
	}

	SECTION("Move constructor")
	{
		String s1("move me");
		const char* original_data_ptr = s1.Data();
		size_t original_size = s1.Size();

		String s2 = std::move(s1);

		REQUIRE(s2.Size() == original_size);
		REQUIRE(CheckData(s2, "move me"));
		REQUIRE(s1.Empty());
	}
}

TEST_CASE("String Assignment Operators", "[string][assignment]")
{

	SECTION("Copy assignment operator")
	{
		String s1("original");
		String s2("temporary");
		const char* s2_old_data = s2.Data();

		s2 = s1;

		REQUIRE(s2.Size() == s1.Size());
		REQUIRE(CheckData(s2, "original"));
		REQUIRE(s1.Data() != s2.Data());

		s1 = s1;
		REQUIRE(s1.Size() == 8);
		REQUIRE(CheckData(s1, "original"));

		String s3("not empty");
		s3 = String("");
		REQUIRE(s3.Empty());
		REQUIRE(CheckData(s3, ""));

		String s4;
		s4 = String("assign to empty");
		REQUIRE(s4.Size() == 15);
		REQUIRE(CheckData(s4, "assign to empty"));
	}

	SECTION("Move assignment operator")
	{
		String s1("move assign source");
		String s2("destination");
		const char* s1_original_data = s1.Data();
		size_t s1_original_size = s1.Size();

		s2 = std::move(s1);

		REQUIRE(s2.Size() == s1_original_size);
		REQUIRE(CheckData(s2, "move assign source"));
		REQUIRE(s2.Data() == s1_original_data);

		REQUIRE(s1.Empty());

		String s3("self move test");
		s3 = std::move(s3);
		REQUIRE(s3.Size() == 14);
		REQUIRE(CheckData(s3, "self move test"));
	}

	SECTION("Operator += (String)")
	{
		String s1("abc");
		String s2("def");
		s1 += s2;
		REQUIRE(s1.Size() == 6);
		REQUIRE(CheckData(s1, "abcdef"));
		REQUIRE(CheckData(s2, "def"));

		String s_empty;
		s1 += s_empty;
		REQUIRE(s1.Size() == 6);
		REQUIRE(CheckData(s1, "abcdef"));

		s_empty += s1;
		REQUIRE(s_empty.Size() == 6);
		REQUIRE(CheckData(s_empty, "abcdef"));
	}

	SECTION("Operator += (C-string)")
	{
		String s1("abc");
		s1 += "def";
		REQUIRE(s1.Size() == 6);
		REQUIRE(CheckData(s1, "abcdef"));

		s1 += "";
		REQUIRE(s1.Size() == 6);
		REQUIRE(CheckData(s1, "abcdef"));

		String s_empty;
		s_empty += "xyz";
		REQUIRE(s_empty.Size() == 3);
		REQUIRE(CheckData(s_empty, "xyz"));
	}
}

TEST_CASE("String Element Access", "[string][access]")
{
	SECTION("const operator[]")
	{
		const String s("test");
		REQUIRE(s[0] == 't');
		REQUIRE(s[1] == 'e');
		REQUIRE(s[2] == 's');
		REQUIRE(s[3] == 't');
	}

	SECTION("non-const operator[]")
	{
		String s("test");
		REQUIRE(s[0] == 't');
		s[1] = 'X';
		REQUIRE(s[1] == 'X');
		REQUIRE(CheckData(s, "tXst"));
	}
}

TEST_CASE("String Capacity/Size Info", "[string][capacity]")
{
	String s("content");
	const String cs("const content");
	String empty_s;

	SECTION("Size/Length")
	{
		REQUIRE(s.Size() == 7);
		REQUIRE(s.Length() == 7);
		REQUIRE(cs.Size() == 13);
		REQUIRE(cs.Length() == 13);
		REQUIRE(empty_s.Size() == 0);
		REQUIRE(empty_s.Length() == 0);
	}

	SECTION("Empty")
	{
		REQUIRE_FALSE(s.Empty());
		REQUIRE_FALSE(cs.Empty());
		REQUIRE(empty_s.Empty());
	}

	SECTION("Data")
	{
		REQUIRE(s.Data() != nullptr);
		REQUIRE(strcmp(s.Data(), "content") == 0);
		REQUIRE(cs.Data() != nullptr);
		REQUIRE(strcmp(cs.Data(), "const content") == 0);
		REQUIRE(empty_s.Data() != nullptr);
		REQUIRE(strcmp(empty_s.Data(), "") == 0);
	}
}

TEST_CASE("String Modifiers", "[string][modifiers]")
{

	SECTION("EmplaceBack")
	{
		String s("ab");
		char c = 'c';
		s.EmplaceBack(std::move(c));
		REQUIRE(s.Size() == 3);
		REQUIRE(s[2] == 'c');
		REQUIRE(CheckData(s, "abc"));

		s.EmplaceBack('d');
		REQUIRE(s.Size() == 4);
		REQUIRE(s[3] == 'd');
		REQUIRE(CheckData(s, "abcd"));

		String empty_s;
		empty_s.EmplaceBack('X');
		REQUIRE(empty_s.Size() == 1);
		REQUIRE(empty_s[0] == 'X');
		REQUIRE(CheckData(empty_s, "X"));
	}

	SECTION("Append (String)")
	{
		String s1("start-");
		String s2("end");
		s1.Append(s2);
		REQUIRE(s1.Size() == 9);
		REQUIRE(CheckData(s1, "start-end"));
		REQUIRE(CheckData(s2, "end"));

		String empty;
		s1.Append(empty);
		REQUIRE(s1.Size() == 9);
		REQUIRE(CheckData(s1, "start-end"));

		empty.Append(s1);
		REQUIRE(empty.Size() == 9);
		REQUIRE(CheckData(empty, "start-end"));
	}

	SECTION("Append (C-string, length)")
	{
		String s1("start-");
		const char* data = "end\0tail";
		s1.Append(data, 3);
		REQUIRE(s1.Size() == 9);
		REQUIRE(CheckData(s1, "start-end"));

		s1.Append(data, 0);
		REQUIRE(s1.Size() == 9);
		REQUIRE(CheckData(s1, "start-end"));

		String empty_s;
		empty_s.Append(data, 3);
		REQUIRE(empty_s.Size() == 3);
		REQUIRE(CheckData(empty_s, "end"));
	}

	SECTION("Append (C-string)")
	{
		String s1("start-");
		s1.Append("end");
		REQUIRE(s1.Size() == 9);
		REQUIRE(CheckData(s1, "start-end"));

		s1.Append("");
		REQUIRE(s1.Size() == 9);
		REQUIRE(CheckData(s1, "start-end"));

		String empty_s;
		empty_s.Append("tail");
		REQUIRE(empty_s.Size() == 4);
		REQUIRE(CheckData(empty_s, "tail"));
	}
}

TEST_CASE("String Concatenation Operators", "[string][concat]")
{
	String s1("Hello ");
	String s2("World");
	std::string std_s = "Guys";
	const char* c_str = "!";

	SECTION("String + String")
	{
		String result = s1 + s2;
		REQUIRE(result.Size() == 11);
		REQUIRE(CheckData(result, "Hello World"));
		REQUIRE(CheckData(s1, "Hello "));
		REQUIRE(CheckData(s2, "World"));
	}

	SECTION("String + std::string")
	{
		String result = s1 + std_s;
		REQUIRE(result.Size() == 10);
		REQUIRE(CheckData(result, "Hello Guys"));
	}

	SECTION("String + C-string")
	{
		String result = s1 + c_str;
		REQUIRE(result.Size() == 7);
		REQUIRE(CheckData(result, "Hello !"));
	}

	SECTION("std::string + String")
	{
		String result = std_s + s2;
		REQUIRE(result.Size() == 9);
		REQUIRE(CheckData(result, "GuysWorld"));
	}

	SECTION("C-string + String")
	{
		String result = "Hey " + s2;
		REQUIRE(result.Size() == 9);
		REQUIRE(CheckData(result, "Hey World"));
	}

	SECTION("Concatenation with empty")
	{
		String empty_s;
		REQUIRE((s1 + empty_s) == s1);
		REQUIRE((empty_s + s1) == s1);
		REQUIRE((s1 + "") == s1);
		REQUIRE(("" + s1) == s1);
		REQUIRE((std::string("") + s1) == s1);
		REQUIRE((s1 + std::string("")) == s1);
	}
}

TEST_CASE("String Comparison Operators", "[string][comparison]")
{
	String s1("apple");
	String s2("apple");
	String s3("Apple");
	String s4("apples");
	String s5("apricot");
	String empty_s;

	SECTION("operator==")
	{
		REQUIRE(s1 == s2);
		REQUIRE_FALSE(s1 == s3);
		REQUIRE_FALSE(s1 == s4);
		REQUIRE_FALSE(s1 == empty_s);
		REQUIRE(empty_s == String(""));
	}

	SECTION("operator!=")
	{
		REQUIRE_FALSE(s1 != s2);
		REQUIRE(s1 != s3);
		REQUIRE(s1 != s4);
		REQUIRE(s1 != empty_s);
		REQUIRE_FALSE(empty_s != String(""));
	}

	SECTION("operator<=> (three-way comparison)")
	{
		REQUIRE((s1 <=> s2) == std::strong_ordering::equal);

		REQUIRE((s1 <=> s3) == std::strong_ordering::greater);
		REQUIRE((s3 <=> s1) == std::strong_ordering::less);

		REQUIRE((s1 <=> s4) == std::strong_ordering::less);
		REQUIRE((s4 <=> s1) == std::strong_ordering::greater);

		REQUIRE((s1 <=> s5) == std::strong_ordering::less);
		REQUIRE((s5 <=> s1) == std::strong_ordering::greater);

		REQUIRE((s1 <=> empty_s) == std::strong_ordering::greater);
		REQUIRE((empty_s <=> s1) == std::strong_ordering::less);
		REQUIRE((empty_s <=> String("")) == std::strong_ordering::equal);
	}
}

TEST_CASE("String Stream Operators", "[string][stream]")
{
	SECTION("Output operator <<")
	{
		String s("stream test");
		std::stringstream ss;
		ss << s;
		REQUIRE(ss.str() == "stream test");

		String empty_s;
		ss.str("");
		ss << empty_s;
		REQUIRE(ss.str() == "");
	}

	SECTION("Input operator >>")
	{
		String s1, s2;
		std::stringstream ss("first second");

		ss >> s1;
		REQUIRE(s1 == String("first"));
		REQUIRE(ss.good());

		ss >> s2;
		REQUIRE(s2 == String("second"));
		REQUIRE(ss.eof());

		s1 = "overwrite";
		ss.clear();
		ss.str("new");
		ss >> s1;
		REQUIRE(s1 == String("new"));

		String s3;
		ss.clear();
		ss.str("");
		ss >> s3;
		REQUIRE(ss.fail());
		REQUIRE(s3.Empty());

		String s4;
		ss.clear();
		ss.str("word");
		ss >> s4;
		REQUIRE(s4 == "word");
		ss >> s4;
		REQUIRE(ss.fail());
	}
}

std::ostringstream g_oss;

void signal_handler(int signal)
{
	if (signal == SIGABRT)
		g_oss << "SIGABRT received\n";
	else
		g_oss << "Unexpected signal " << signal << " received\n";

	std::_Exit(EXIT_FAILURE);
}

TEST_CASE("String Iterators")
{
	SECTION("operator+(int) for iterator")
	{
		std::ostringstream oss;
		String str = "12345";

		auto begin = str.begin();

		REQUIRE(*(begin + 0) == '1');
		REQUIRE(*(begin + 1) == '2');
		REQUIRE(*(begin + 2) == '3');
		REQUIRE(*(begin + 3) == '4');
		REQUIRE(*(begin + 4) == '5');
		REQUIRE(*(begin + 5) == '\0');

		REQUIRE(*(0 + begin) == '1');
		REQUIRE(*(1 + begin) == '2');
		REQUIRE(*(2 + begin) == '3');
		REQUIRE(*(3 + begin) == '4');
		REQUIRE(*(4 + begin) == '5');
		REQUIRE(*(5 + begin) == '\0');

		int diff = str.end() - str.begin();
		REQUIRE(diff == 5);
		int negativeDiff = str.begin() - str.end();
		REQUIRE(negativeDiff == -5);
	}

	SECTION("operator[] calls std::abort in Debug")
	{
		auto prev_handler = std::signal(SIGABRT, signal_handler);
		if (prev_handler == SIG_ERR)
		{
			std::cerr << "Setup failed\n";
			REQUIRE(0);
		}
	}

	SECTION("begin, end, Forward iteration on non-const String")
	{
		std::ostringstream oss;
		String str = "12345";
		String expected = "12345";
		for (auto it = str.begin(); it != str.end(); ++it)
		{
			oss << *it;
		}

		REQUIRE(str == expected);
	}

	SECTION("rbegin, rend, Reverse iteration on non-const String")
	{
		std::ostringstream oss;
		String str = "12345";
		String expected = "54321";
		for (auto it = str.rbegin(); it != str.rend(); ++it)
		{
			oss << *it;
		}

		REQUIRE(CheckData(expected, oss.str().data()));
	}

	SECTION("Const Range-based for loop")
	{
		std::ostringstream oss;
		String str = "12345";
		String expected = "12345";
		for (const char& ch : str)
		{
			oss << ch;
		}

		REQUIRE(CheckData(expected, oss.str().data()));
	}

	SECTION("Range-based for loop")
	{
		std::ostringstream oss;
		String str = "12345";
		String expected = "11111";
		for (char& ch : str)
		{
			ch = '1';
		}

		REQUIRE(CheckData(expected, str.Data()));
	}
}
