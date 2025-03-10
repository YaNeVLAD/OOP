#include <Windows.h>
#include <fstream>
#include <iostream>

#include "DictionaryMap.h"

const char YES_ANSWER = 'y';
const const char* RUSSIAN = "Russian";

const std::string EXIT_QUOTE = "...";
const std::string DEFAULT_OUTPUT_FILE_NAME = "dictionary.txt";

enum class Phrase
{
	CHANGES_SAVED,
	CHANGES_MADE,
	FAILED_TO_OPEN,
	UNKNOWN_WORD,
	WORD_IGNORED,
	WORD_ADDED,
};

void Print(Phrase phrase, const std::string& arg1 = "", const std::string& arg2 = "")
{
	switch (phrase)
	{
	case Phrase::CHANGES_SAVED:
		std::cout << "Изменения сохранены. До свидания." << std::endl;
		break;
	case Phrase::CHANGES_MADE:
		std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом." << std::endl;
		break;
	case Phrase::FAILED_TO_OPEN:
		std::cout << "Не удалось открыть выходной файл " << arg1 << std::endl;
		break;
	case Phrase::UNKNOWN_WORD:
		std::cout << "Неизвестное слово \"" << arg1 << "\". Введите перевод или пустую строку для отказа." << std::endl;
		break;
	case Phrase::WORD_IGNORED:
		std::cout << "Слово \"" << arg1 << "\" проигнорировано." << std::endl;
		break;
	case Phrase::WORD_ADDED:
		std::cout << "Слово \"" << arg1 << "\" сохранено в словаре как \"" << arg2 << "\"." << std::endl;
		break;
	default:
		std::cout << "Неизвестная фраза" << std::endl;
		break;
	}
}

void HandleExit(const Dictionary::DictionaryType& dict, const std::string& fileName, bool hasChanged)
{
	if (!hasChanged)
	{
		return;
	}

	Print(Phrase::CHANGES_MADE);

	char answer;
	if (std::cin >> answer; std::tolower(answer) == YES_ANSWER)
	{
		std::ofstream output(fileName);
		if (!output.is_open())
		{
			Print(Phrase::FAILED_TO_OPEN, fileName);
			return;
		}

		Dictionary::WriteToStream(output, dict);
		Print(Phrase::CHANGES_SAVED);
	}
}

void HandleNewWord(const std::string& word, Dictionary::DictionaryType& dict, bool& hasChanged)
{
	Print(Phrase::UNKNOWN_WORD, word);

	std::string translation;
	if (std::getline(std::cin, translation) && !translation.empty())
	{
		hasChanged = true;
		Dictionary::AddToDictionary(dict, word, translation);
		Print(Phrase::WORD_ADDED, word, translation);
	}
	else
	{
		hasChanged = false;
		Print(Phrase::WORD_IGNORED);
	}
}

void HandleUserInput(Dictionary::DictionaryType& dict, const std::string& fileName)
{
	std::string word;
	bool hasChanged = false;
	while (std::getline(std::cin, word))
	{
		if (word.empty())
		{
			continue;
		}

		if (word == EXIT_QUOTE)
		{
			return HandleExit(dict, fileName, hasChanged);
		}

		auto translations = Dictionary::FindTranslations(dict, word);
		if (!translations.empty())
		{
			Dictionary::PrintTranslations(std::cout, translations);

			std::cout << std::endl;
		}
		else
		{
			HandleNewWord(word, dict, hasChanged);
		}
	}
}

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, RUSSIAN);

	Dictionary::DictionaryType dict;
	std::string outputName = DEFAULT_OUTPUT_FILE_NAME;

	if (argc == 2)
	{
		std::ifstream input(argv[1]);
		if (!input.is_open())
		{
			Print(Phrase::FAILED_TO_OPEN, argv[1]);
		}
		else
		{
			dict = Dictionary::CreateFromStream(input);
			outputName = argv[1];
		}
	}

	HandleUserInput(dict, outputName);

	return EXIT_SUCCESS;
}
