#include "ParseUrl.h"
#include "algorithm"
#include "regex"
#include "stdexcept"

const std::string HTTP_STR = "http";
const std::string HTTPS_STR = "https";
const std::string FTP_STR = "ftp";

const int MIN_PORT = 0;
const int MAX_PORT = 65535;

void AssertPortInRange(int port)
{
	if (port < MIN_PORT || port > MAX_PORT)
	{
		throw std::runtime_error("Wrong port. Must be in range from "
			+ std::to_string(0)
			+ " to "
			+ std::to_string(65535));
	}
}

std::string ToLower(const std::string& str)
{
	std::string result(str);
	std::transform(str.begin(), str.end(), result.begin(), [](const char& ch) {
		return static_cast<char>(std::tolower(ch));
	});

	return result;
}

parse_url::Protocol ParseProtocol(const std::string& protocolStr)
{
	auto lower = ToLower(protocolStr);

	if (lower == HTTP_STR)
	{
		return parse_url::Protocol::HTTP;
	}
	else if (lower == HTTPS_STR)
	{
		return parse_url::Protocol::HTTPS;
	}
	else if (lower == FTP_STR)
	{
		return parse_url::Protocol::FTP;
	}
	else
	{
		throw std::runtime_error("Unknown protocol: " + protocolStr);
	}
}

int ParsePort(const std::string& portStr, parse_url::Protocol protocol)
{
	if (portStr.empty())
	{
		switch (protocol)
		{
		case parse_url::Protocol::HTTP:
			return 80;
		case parse_url::Protocol::HTTPS:
			return 443;
		case parse_url::Protocol::FTP:
			return 21;
		default:
			throw std::runtime_error("Unknown protocol.");
		}
	}

	int port = std::stoi(portStr);

	AssertPortInRange(port);

	return port;
}

bool parse_url::ParseURL(const std::string& url, UrlData& data)
{
	auto& [protocol, host, port, document] = data;
	try
	{
		std::regex urlRegex(R"(^(https?|ftp)://([^/:]+)(?::(\d+))?(?:/(.*))?$)", std::regex::icase);
		std::smatch match;
		if (!std::regex_match(url, match, urlRegex))
		{
			throw std::runtime_error("Regex failed");
		}

		protocol = ParseProtocol(match[1]);

		host = match[2];

		port = ParsePort(match[3], protocol);

		document = match[4].matched ? match[4].str() : "";

		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
}
