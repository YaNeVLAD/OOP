#pragma once
#include <string>

/**
 * \throws std::runtime_error - when given unknown html encoded sequence
 */
std::string HtmlDecode(std::string const& html);
