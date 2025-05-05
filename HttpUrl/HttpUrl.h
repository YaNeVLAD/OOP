#pragma once

#include <ostream>
#include <string>

#include "Protocol.h"
#include "UrlParsingError.hpp"

using Port = unsigned short;

class HttpUrl
{
public:
	HttpUrl(const char* cString);
	HttpUrl(const std::string& url);

	HttpUrl(
		std::string domain,
		std::string document,
		Protocol protocol = Protocol::HTTP);

	HttpUrl(
		std::string domain,
		std::string document,
		Protocol protocol,
		Port port);

	std::string GetUrl() const;

	std::string GetDomain() const;

	std::string GetDocument() const;

	Protocol GetProtocol() const;

	Port GetPort() const;

	friend std::ostream& operator<<(std::ostream& out, const HttpUrl& url);

private:
	Protocol m_protocol;
	std::string m_domain;
	std::string m_document;
	Port m_port;
};
