#include <Windows.h>
#include <fstream>
#include <iostream>

#include "DictionaryMap.h"

const std::string EXIT_QUOTE = "...";
const std::string DEFAULT_OUTPUT_FILE_NAME = "dictionary.txt";

void HandleNewWord(const std::string& word, Dictionary::DictionaryType& dict, bool& hasChanged)
{
	std::cout << "����������� ����� \"" << word << "\". ������� ������� ��� ������ ������ ��� ������.\n";
	if (std::string translation; std::getline(std::cin, translation) && !translation.empty())
	{
		hasChanged = true;
		Dictionary::AddToDictionary(dict, word, translation);
		std::cout << "����� \"" << word << " ��������� � ������� ��� \"" << translation << "\".\n";
	}
	else
	{
		hasChanged = false;
		std::cout << "����� \"" << word << " ���������������.\n";
	}
}

void HandleUserInput(Dictionary::DictionaryType& dict, const std::string& name)
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
			if (!hasChanged)
			{
				return;
			}

			std::cout << "� ������� ���� ������� ���������. ������� Y ��� y ��� ���������� ����� �������.\n";
			std::cin >> word;

			if (word == "Y" || word == "y")
			{
				std::ofstream output(name);
				Dictionary::WriteToStream(output, dict);
				std::cout << "��������� ���������. �� ��������.\n";
			}

			return;
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
	setlocale(LC_ALL, "Russian");

	Dictionary::DictionaryType dict;
	std::string fileName = DEFAULT_OUTPUT_FILE_NAME;

	if (argc == 2)
	{
		std::ifstream input(argv[1]);
		if (!input.is_open())
		{
			std::cout << "Failed to open file " << argv[1] << std::endl;
		}
		else
		{
			dict = Dictionary::CreateFromStream(input);
			fileName = argv[1];
		}
	}

	HandleUserInput(dict, fileName);

	return EXIT_SUCCESS;
}
