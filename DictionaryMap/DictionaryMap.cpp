#include "DictionaryMap.h"

#include <algorithm>

using namespace std::literals;

std::string DIVIDER = " -- ";

using Quote = std::pair<std::string, std::string>;

static std::string ToLower(const std::string& str)
{
	std::string result(str);
	std::transform(str.begin(), str.end(), result.begin(), [](auto& ch) {
		return static_cast<unsigned char>(std::tolower(ch));
	});

	return result;
}

Dictionary::DictionaryType Dictionary::CreateFromStream(std::istream& input)
{
	DictionaryType result;

	std::string line;
	while (std::getline(input, line))
	{
		size_t delimiterPos = line.find(DIVIDER);
		if (delimiterPos == std::string::npos)
		{
			continue;
		}

		std::string word = line.substr(0, delimiterPos);
		std::string translation = line.substr(delimiterPos + DIVIDER.size());

		AddToDictionary(result, word, translation);
	}

	return result;
}

void Dictionary::WriteToStream(std::ostream& output, const DictionaryType& dictionary)
{
	std::set<Quote> printedQuotes;

	for (const auto& [word, translations] : dictionary)
	{
		for (const auto& translation : translations)
		{
			Quote wordToTranslation = { word, translation };
			Quote translationToWord = { translation, word };

			if (printedQuotes.contains(wordToTranslation) || printedQuotes.contains(translationToWord))
			{
				continue;
			}

			printedQuotes.insert(wordToTranslation);
			output << word << DIVIDER << translation << std::endl;
		}
	}
}

void Dictionary::AddToDictionary(DictionaryType& dictionary, const std::string& word, const std::string& translation)
{
	dictionary[ToLower(word)].insert(translation);
}

std::set<std::string> Dictionary::FindTranslations(const DictionaryType& dictionary, const std::string& word)
{
	std::set<std::string> result;

	auto it = dictionary.find(ToLower(word));
	if (it != dictionary.end())
	{
		result.insert(it->second.begin(), it->second.end());
	}

	for (const auto& [key, translations] : dictionary)
	{
		for (const auto& translation : translations)
		{
			if (ToLower(translation) != ToLower(word))
			{
				continue;
			}
			result.insert(key);
		}
	}

	return result;
}

void Dictionary::PrintTranslations(std::ostream& output, const std::set<std::string>& translations)
{
	if (translations.empty())
	{
		return;
	}

	auto it = translations.begin();
	output << *it;

	for (++it; it != translations.end(); ++it)
	{
		output << ", " << *it;
	}
}
