#include "catch2.h"
#include <sstream>

using namespace Dictionary;

TEST_CASE("CreateFromStream creates dictionary from input stream", "[CreateFromStream]")
{
	std::istringstream input("hello -- привет\nworld -- мир\n");
	auto dictionary = CreateFromStream(input);

	REQUIRE(dictionary.size() == 4);
	REQUIRE(dictionary["hello"].contains("привет"));
	REQUIRE(dictionary["world"].contains("мир"));
}

TEST_CASE("WriteToStream writes dictionary to output stream", "[WriteToStream]")
{
	DictionaryType dictionary = {
		{ "hello", { "привет" } },
		{ "world", { "мир" } }
	};

	std::ostringstream output;
	WriteToStream(output, dictionary);

	std::string expectedOutput = "hello -- привет\nworld -- мир\n";
	REQUIRE(output.str() == expectedOutput);
}

TEST_CASE("AddToDictionary adds word and translation to dictionary", "[AddToDictionary]")
{
	DictionaryType dictionary;
	AddToDictionary(dictionary, { "hello", "привет" });

	REQUIRE(dictionary.size() == 2);
	REQUIRE(dictionary["hello"].contains("привет"));
}

TEST_CASE("FindTranslations finds translations for a word", "[FindTranslations]")
{
	DictionaryType dictionary = {
		{ "hello", { "привет" } },
		{ "привет", { "hello" } },
		{ "world", { "мир" } },
		{ "мир", { "world" } },
	};

	auto translations = FindTranslations(dictionary, "hello");
	REQUIRE(translations.contains("привет"));

	translations = FindTranslations(dictionary, "привет");
	REQUIRE(translations.contains("hello"));

	translations = FindTranslations(dictionary, "мир");
	REQUIRE(translations.contains("world"));
}

TEST_CASE("PrintTranslations prints translations in lexico order to output stream", "[PrintTranslations]")
{
	std::set<std::string> translations = { "привет", "здравствуйте" };

	std::ostringstream output;
	PrintTranslations(output, translations);

	std::string expectedOutput = "здравствуйте, привет";
	REQUIRE(output.str() == expectedOutput);
}

TEST_CASE("PrintTranslations does not print anything for empty translations", "[PrintTranslations]")
{
	std::set<std::string> translations;

	std::ostringstream output;
	PrintTranslations(output, translations);

	REQUIRE(output.str().empty());
}
