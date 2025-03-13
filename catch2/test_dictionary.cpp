#include "catch2.h"
#include <sstream>

using namespace dictionary;

TEST_CASE("CreateFromStream creates dictionary from input stream", "[CreateFromStream]")
{
	std::istringstream input("hello -- ������\n\n\nworld -- ���\n");
	auto dictionary = CreateFromStream(input);

	REQUIRE(dictionary.size() == 4);
	REQUIRE(dictionary["hello"].contains("������"));
	REQUIRE(dictionary["world"].contains("���"));
}

TEST_CASE("WriteToStream writes dictionary to output stream", "[WriteToStream]")
{
	DictionaryType dictionary = {
		{ "hello", { "������" } },
		{ "world", { "���" } }
	};

	std::ostringstream output;
	WriteToStream(output, dictionary);

	std::string expectedOutput = "hello -- ������\nworld -- ���\n";
	REQUIRE(output.str() == expectedOutput);
}

TEST_CASE("AddToDictionary adds word and translation to dictionary", "[AddToDictionary]")
{
	DictionaryType dictionary;
	AddToDictionary(dictionary, { "hello", "������" });

	REQUIRE(dictionary.size() == 2);
	REQUIRE(dictionary["hello"].contains("������"));
}

TEST_CASE("FindTranslations finds translations for a word", "[FindTranslations]")
{
	DictionaryType dictionary;

	AddToDictionary(dictionary, { "hello", "������" });
	AddToDictionary(dictionary, { "world", "���" });

	auto translations = FindTranslations(dictionary, "hello");
	REQUIRE(translations.contains("������"));

	translations = FindTranslations(dictionary, "������");
	REQUIRE(translations.contains("hello"));

	translations = FindTranslations(dictionary, "���");
	REQUIRE(translations.contains("world"));
}

TEST_CASE("PrintTranslations prints translations in lexico order to output stream", "[PrintTranslations]")
{
	std::set<std::string> translations = { "������������", "��" };

	std::ostringstream output;
	PrintTranslations(output, translations);

	std::string expectedOutput = "��, ������������";
	REQUIRE(output.str() == expectedOutput);
}

TEST_CASE("PrintTranslations does not print anything for empty translations", "[PrintTranslations]")
{
	std::set<std::string> translations;

	std::ostringstream output;
	PrintTranslations(output, translations);

	REQUIRE(output.str().empty());
}
