#pragma once
#include <string>

/**
 * @throws std::runtime_error - when given wrong html encoded sequence
 */
std::string HtmlDecode(std::string const& html);
