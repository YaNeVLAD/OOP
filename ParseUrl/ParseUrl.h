#pragma once

#include <string>

namespace parse_url
{
enum class Protocol
{
	UNKNOWN = 0,
	HTTP,
	HTTPS,
	FTP,
};

struct UrlData
{
	Protocol protocol = Protocol::UNKNOWN;

	std::string host;

	int port = -1;

	std::string document;

	friend bool operator==(const UrlData&, const UrlData&) = default;
};

bool ParseURL(const std::string& url, UrlData& data);

} // namespace parse_url
