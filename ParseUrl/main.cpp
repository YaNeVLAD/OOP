#include "ParseUrl.h"

#include <iostream>

int main()
{
	std::string url;
	parse_url::UrlData data;
	while (std::getline(std::cin, url))
	{
		if (!parse_url::ParseURL(url, data))
		{
			std::cout << "ERROR\n";
			return EXIT_FAILURE;
		}

		auto& [protocol, host, port, document] = data;

		std::cout << url << "\n";
		std::cout << "HOST: " << host << "\n";
		std::cout << "PORT: " << port << "\n";
		std::cout << "DOC: " << document << "\n";
	}

	return EXIT_SUCCESS;
}
