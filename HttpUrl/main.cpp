#include <iostream>

#include "HttpUrl.h"
#include <cstdint>
int main()
{
	std::string line;
	while (std::getline(std::cin, line))
	{
		try
		{
			HttpUrl url(line);

			std::cout << url << "\n";
			std::cout << "PROTOCOL: " << url.GetProtocol().ToString() << "\n";
			std::cout << "DOMAIN: " << url.GetDomain() << "\n";
			std::cout << "PORT: " << url.GetPort() << "\n";
			std::cout << "DOCUMENT: " << url.GetDocument() << "\n";
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}
}
