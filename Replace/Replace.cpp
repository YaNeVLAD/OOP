#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int ExitWithUsageHint()
{
	std::cout << "Usage: replace.exe <inputFile> <outputFile> <search> <replace>\n";

	return EXIT_SUCCESS;
}

int ExitWithError(int exitCode = 1)
{
	std::cout << "ERROR\n";

	return exitCode;
}

int ExitWithFlag(const std::string& flag)
{
	if (flag == "-h" || flag == "--help")
	{
		return ExitWithUsageHint();
	}

	return ExitWithError();
}

std::string ReplaceString(
	const std::string& subject,
	const std::string& searchString,
	const std::string& replacementString)
{
	if (searchString.empty())
	{
		return subject;
	}

	size_t pos = 0;
	std::string result;
	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);
		if (foundPos != std::string::npos)
		{
			result.append(subject, pos, foundPos - pos);
			result.append(replacementString);
			pos = foundPos + searchString.length();
		}
		else
		{
			result.append(subject, pos);
			break;
		}
	}
	return result;
}

int CopyStreamWithReplacement(
	std::istream& input,
	std::ostream& output,
	const std::string& searchString,
	const std::string& replacementString)
{
	std::string line;
	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << std::endl;
	}

	output.flush();

	return EXIT_SUCCESS;
}

int CopyTextWithReplacement()
{
	std::string search, replace;
	if (!std::getline(std::cin, search) || !std::getline(std::cin, replace))
	{
		return ExitWithError(EXIT_SUCCESS);
	}

	std::vector<std::string> text;
	std::string line;
	while (std::getline(std::cin, line))
	{
		text.push_back(line);
	}

	if (text.empty())
	{
		return ExitWithError(EXIT_SUCCESS);
	}

	for (auto& textLine : text)
	{
		std::cout << ReplaceString(textLine, search, replace) << std::endl;
	}

	return EXIT_SUCCESS;
}

int CopyFileWithReplacement(
	const std::string& inputName,
	const std::string& outputName,
	const std::string& search,
	const std::string& replace)
{
	std::ifstream inputFile;
	inputFile.open(inputName);

	if (!inputFile.is_open())
	{
		return ExitWithError();
	}

	std::ofstream outputFile;
	outputFile.open(outputName);

	if (!outputFile.is_open())
	{
		return ExitWithError();
	}

	return CopyStreamWithReplacement(inputFile, outputFile, search, replace);
}

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		return CopyTextWithReplacement();
	}
	else if (argc == 2 && argv[1][0] == '-')
	{
		return ExitWithFlag(argv[1]);
	}
	else if (argc != 5)
	{
		return ExitWithError();
	}
	else
	{
		return CopyFileWithReplacement(argv[1], argv[2], argv[3], argv[4]);
	}
}
