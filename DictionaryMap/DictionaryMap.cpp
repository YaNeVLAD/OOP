#include "DictionaryMap.h"

#include <algorithm>

const std::string DIVIDER = " -- ";

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
	std::set<Entry> entries;

	for (const auto& [word, translations] : dictionary)
	{
		for (const auto& translation : translations)
		{
			Entry wordToTranslation = { word, translation };
			Entry translationToWord = { translation, word };

			if (entries.contains(wordToTranslation) || entries.contains(translationToWord))
			{
				continue;
			}

			entries.insert(wordToTranslation);
			output << word << DIVIDER << translation << std::endl;
		}
	}
}

void Dictionary::AddToDictionary(DictionaryType& dictionary, const std::string& word, const std::string& translation)
{
	dictionary[word].insert(translation);
	dictionary[translation].insert(word);
}

std::set<std::string> Dictionary::FindTranslations(const DictionaryType& dictionary, const std::string& word)
{
	std::set<std::string> result;

	std::string lowerWord = ToLower(word);

	for (const auto& [key, translations] : dictionary)
	{
		if (ToLower(key) == lowerWord)
		{
			result.insert(translations.begin(), translations.end());
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
