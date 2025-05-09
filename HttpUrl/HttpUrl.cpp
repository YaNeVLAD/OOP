#include "HttpUrl.h"

#include <format>
#include <unordered_map>

#include "../ParseUrl/ParseUrl.h"

namespace
{
constexpr const char* DEFAULT_PORT_FORMAT = "{}://{}/{}";
constexpr const char* CUSTOM_PORT_FORMAT = "{}://{}:{}/{}";

std::unordered_map<Protocol::Enum, Port> PROTOCOL_TO_DEFAULT_PORT = {
	{ Protocol::HTTP, Port(80) },
	{ Protocol::HTTPS, Port(443) }
};

bool IsPortDefault(Protocol protocol, Port port)
{
	if (auto it = PROTOCOL_TO_DEFAULT_PORT.find(protocol); it != PROTOCOL_TO_DEFAULT_PORT.end())
	{
		return port == it->second;
	}
	return false;
}
} // namespace

HttpUrl::HttpUrl(const char* cString)
	: HttpUrl(std::string{ cString })
{
}

HttpUrl::HttpUrl(const std::string& url)
{
	parse_url::UrlData data;
	if (!parse_url::ParseURL(url, data) || data.protocol == parse_url::Protocol::FTP)
	{
		throw UrlParsingError("Failed to parse url");
	}

	m_protocol = data.protocol == parse_url::Protocol::HTTP ? Protocol::HTTP : Protocol::HTTPS;
	m_domain = data.host;
	m_document = data.document;
	m_port = static_cast<Port>(data.port);
}

HttpUrl::HttpUrl(std::string domain, std::string document, Protocol protocol)
	: HttpUrl(std::move(domain), std::move(document), protocol, PROTOCOL_TO_DEFAULT_PORT.at(protocol))
{
}

HttpUrl::HttpUrl(std::string domain, std::string document, Protocol protocol, Port port)
	: m_domain(std::move(domain))
	, m_document(std::move(document))
	, m_protocol(protocol)
	, m_port(port)
{
}

std::string HttpUrl::GetUrl() const
{
	if (IsPortDefault(m_protocol, m_port))
	{
		return std::format(DEFAULT_PORT_FORMAT, m_protocol.ToString(), m_domain, m_document);
	}

	return std::format(CUSTOM_PORT_FORMAT, m_protocol.ToString(), m_domain, m_port, m_document);
}

std::string HttpUrl::GetDomain() const
{
	return m_domain;
}

std::string HttpUrl::GetDocument() const
{
	return m_document;
}

Protocol HttpUrl::GetProtocol() const
{
	return m_protocol;
}

Port HttpUrl::GetPort() const
{
	return m_port;
}

std::ostream& operator<<(std::ostream& out, const HttpUrl& url)
{
	return out << url.GetUrl();
}
