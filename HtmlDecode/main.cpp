#include "HtmlDecode.h"
#include <iostream>

int main()
{
	try
	{
		std::string line;
		while (std::getline(std::cin, line))
		{
			std::cout << HtmlDecode(line) << std::endl;
		}

		return EXIT_SUCCESS;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;

		return EXIT_FAILURE;
	}
}
