#pragma once

#include <stdexcept>

struct UrlParsingError : std::invalid_argument
{
	UrlParsingError(std::string message)
		: std::invalid_argument(std::move(message))
	{
	}
};
