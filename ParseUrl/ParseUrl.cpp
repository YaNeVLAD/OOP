#include "ParseUrl.h"
#include "algorithm"
#include "regex"
#include "stdexcept"
#include "unordered_map"

using namespace parse_url;

const std::string HTTP_STR = "http";
const std::string HTTPS_STR = "https";
const std::string FTP_STR = "ftp";

const int MIN_PORT = 0;
const int MAX_PORT = 65535;

const std::unordered_map<std::string, Protocol> PROTOCOL_MAP = {
	{ "http", Protocol::HTTP },
	{ "https", Protocol::HTTPS },
	{ "ftp", Protocol::FTP }
};

const std::unordered_map<Protocol, int> PROTOCOL_DEFAULT_PORT = {
	{ Protocol::HTTP, 80 },
	{ Protocol::HTTPS, 443 },
	{ Protocol::FTP, 21 }
};

void AssertPortInRange(int port)
{
	if (port < MIN_PORT || port > MAX_PORT)
	{
		throw std::runtime_error("Wrong port. Must be in range from "
			+ std::to_string(MIN_PORT)
			+ " to "
			+ std::to_string(MAX_PORT));
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

Protocol ParseProtocol(const std::string& protocolStr)
{
	auto lower = ToLower(protocolStr);

	auto it = PROTOCOL_MAP.find(lower);
	if (it == PROTOCOL_MAP.end())
	{
		throw std::runtime_error("Unknown protocol: " + protocolStr);
	}
	return it->second;
}

int ParsePort(const std::string& portStr, Protocol protocol)
{
	if (portStr.empty())
	{
		auto it = PROTOCOL_DEFAULT_PORT.find(protocol);
		if (it == PROTOCOL_DEFAULT_PORT.end())
		{
			throw std::runtime_error("Failed to find default port for given protocol.");
		}
		return it->second;
	}

	int port = std::stoi(portStr);

	AssertPortInRange(port);

	return port;
}

bool parse_url::ParseURL(const std::string& url, UrlData& data)
{
	UrlData temp = data;
	auto& [protocol, host, port, document] = temp;
	try
	{
		std::regex urlRegex(R"(^([^/:]+)://([^/:]+)(?::(\d+))?(?:/(.*))?$)", std::regex::icase);
		std::smatch match;
		if (!std::regex_match(url, match, urlRegex))
		{
			throw std::runtime_error("Regex failed");
		}

		protocol = ParseProtocol(match[1]);

		host = match[2];

		port = ParsePort(match[3], protocol);

		document = match[4].matched ? match[4].str() : "";

		data = temp;

		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
}
