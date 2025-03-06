#include "VectorProcessor.h"
#include <iostream>

int main()
{
	try
	{
		std::vector<double> vec = ReadNumbers(std::cin);

		ProcessNumbers(vec);

		PrintSortedNumbers(std::cout, vec);

		return EXIT_SUCCESS;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;

		return EXIT_FAILURE;
	}
}
