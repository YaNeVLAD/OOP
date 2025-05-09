#include "catch2.h"

TEST_CASE("HttpUrl Constructors - Parsing Valid URLs", "[HttpUrl][Constructor][Parsing]")
{
	SECTION("HTTP with default port and no document")
	{
		HttpUrl url("http://example.com");
		REQUIRE(url.GetProtocol() == Protocol::HTTP);
		REQUIRE(url.GetDomain() == "example.com");
		REQUIRE(url.GetPort() == Port(80));
		REQUIRE(url.GetDocument() == "");
		REQUIRE(url.GetUrl() == "http://example.com/"); // Default document is "/"
	}

	SECTION("HTTPS with default port and no document")
	{
		HttpUrl url("https://example.com");
		REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		REQUIRE(url.GetDomain() == "example.com");
		REQUIRE(url.GetPort() == Port(443));
		REQUIRE(url.GetDocument() == "");
		REQUIRE(url.GetUrl() == "https://example.com/"); // Default document is "/"
	}

	SECTION("HTTP with custom port and document")
	{
		HttpUrl url("http://example.com:8080/path/to/doc");
		REQUIRE(url.GetProtocol() == Protocol::HTTP);
		REQUIRE(url.GetDomain() == "example.com");
		REQUIRE(url.GetPort() == Port(8080));
		REQUIRE(url.GetDocument() == "path/to/doc");
		REQUIRE(url.GetUrl() == "http://example.com:8080/path/to/doc");
	}

	SECTION("HTTPS with default port and document")
	{
		HttpUrl url("https://secure.com/index.html");
		REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		REQUIRE(url.GetDomain() == "secure.com");
		REQUIRE(url.GetPort() == Port(443));
		REQUIRE(url.GetDocument() == "index.html");
		REQUIRE(url.GetUrl() == "https://secure.com/index.html");
	}

	SECTION("HTTP with default port and document ending with slash")
	{
		HttpUrl url("http://localhost/api/");
		REQUIRE(url.GetProtocol() == Protocol::HTTP);
		REQUIRE(url.GetDomain() == "localhost");
		REQUIRE(url.GetPort() == Port(80));
		REQUIRE(url.GetDocument() == "api/");
		REQUIRE(url.GetUrl() == "http://localhost/api/");
	}

	SECTION("HTTPS with custom port and no document")
	{
		HttpUrl url("https://192.168.1.1:8443");
		REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		REQUIRE(url.GetDomain() == "192.168.1.1");
		REQUIRE(url.GetPort() == Port(8443));
		REQUIRE(url.GetDocument() == "");
		REQUIRE(url.GetUrl() == "https://192.168.1.1:8443/"); // Default document is "/"
	}

	SECTION("Parsing from C-string")
	{
		HttpUrl url("http://example.com");
		REQUIRE(url.GetProtocol() == Protocol::HTTP);
		REQUIRE(url.GetDomain() == "example.com");
		REQUIRE(url.GetPort() == Port(80));
		REQUIRE(url.GetDocument() == "");
		REQUIRE(url.GetUrl() == "http://example.com/");
	}
}

TEST_CASE("HttpUrl Constructors - Parsing Invalid URLs", "[HttpUrl][Constructor][Parsing][Error]")
{
	SECTION("Invalid format URL")
	{
		REQUIRE_THROWS_AS(HttpUrl("invalid-url"), UrlParsingError);
	}

	SECTION("URL with FTP protocol")
	{
		REQUIRE_THROWS_AS(HttpUrl("ftp://ftp.example.com/file"), UrlParsingError);
	}

	SECTION("Invalid port")
	{
		REQUIRE_THROWS_AS(HttpUrl("http://example.com:77777"), UrlParsingError);
		REQUIRE_THROWS_AS(HttpUrl("http://example.com:-1"), UrlParsingError);
		// Edge case
		REQUIRE_THROWS_AS(HttpUrl("http://example.com:65536"), UrlParsingError);
	}
}

TEST_CASE("HttpUrl Constructors - Manual Construction", "[HttpUrl][Constructor][Manual]")
{
	SECTION("Constructor with default port")
	{
		HttpUrl url("example.org", "path/to/resource", Protocol::HTTP);
		REQUIRE(url.GetProtocol() == Protocol::HTTP);
		REQUIRE(url.GetDomain() == "example.org");
		REQUIRE(url.GetPort() == Port(80));
		REQUIRE(url.GetDocument() == "path/to/resource");
		REQUIRE(url.GetUrl() == "http://example.org/path/to/resource");
	}

	SECTION("Constructor with default port - HTTPS")
	{
		HttpUrl url("secure.org", "login", Protocol::HTTPS);
		REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		REQUIRE(url.GetDomain() == "secure.org");
		REQUIRE(url.GetPort() == Port(443));
		REQUIRE(url.GetDocument() == "login");
		REQUIRE(url.GetUrl() == "https://secure.org/login");
	}

	SECTION("Constructor with custom port")
	{
		HttpUrl url("api.svc", "v1/data", Protocol::HTTP, Port(8081));
		REQUIRE(url.GetProtocol() == Protocol::HTTP);
		REQUIRE(url.GetDomain() == "api.svc");
		REQUIRE(url.GetPort() == Port(8081));
		REQUIRE(url.GetDocument() == "v1/data");
		REQUIRE(url.GetUrl() == "http://api.svc:8081/v1/data");
	}

	SECTION("Constructor with custom port - HTTPS")
	{
		HttpUrl url("backup.net", "files", Protocol::HTTPS, Port(8443));
		REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		REQUIRE(url.GetDomain() == "backup.net");
		REQUIRE(url.GetPort() == Port(8443));
		REQUIRE(url.GetDocument() == "files");
		REQUIRE(url.GetUrl() == "https://backup.net:8443/files");
	}

	SECTION("Constructor with empty document")
	{
		HttpUrl url("empty.doc", "", Protocol::HTTP);
		REQUIRE(url.GetProtocol() == Protocol::HTTP);
		REQUIRE(url.GetDomain() == "empty.doc");
		REQUIRE(url.GetPort() == Port(80));
		REQUIRE(url.GetDocument() == "");
		REQUIRE(url.GetUrl() == "http://empty.doc/"); // Default document is "/"
	}

	SECTION("Constructor with document ending with slash")
	{
		HttpUrl url("trailing.slash", "path/", Protocol::HTTP);
		REQUIRE(url.GetProtocol() == Protocol::HTTP);
		REQUIRE(url.GetDomain() == "trailing.slash");
		REQUIRE(url.GetPort() == Port(80));
		REQUIRE(url.GetDocument() == "path/");
		REQUIRE(url.GetUrl() == "http://trailing.slash/path/");
	}
}

TEST_CASE("HttpUrl Member Functions", "[HttpUrl][MemberFunctions]")
{
	HttpUrl url("http://test.com:9090/document/test.html");

	SECTION("GetProtocol returns correct protocol")
	{
		REQUIRE(url.GetProtocol() == Protocol::HTTP);
	}

	SECTION("GetDomain returns correct domain")
	{
		REQUIRE(url.GetDomain() == "test.com");
	}

	SECTION("GetPort returns correct port")
	{
		REQUIRE(url.GetPort() == Port(9090));
	}

	SECTION("GetDocument returns correct document")
	{
		REQUIRE(url.GetDocument() == "document/test.html");
	}

	SECTION("GetUrl returns correct URL string with custom port")
	{
		REQUIRE(url.GetUrl() == "http://test.com:9090/document/test.html");
	}

	SECTION("GetUrl returns correct URL string with default port - HTTP")
	{
		HttpUrl defaultPortUrl("http://default.com/page");
		REQUIRE(defaultPortUrl.GetUrl() == "http://default.com/page");
	}

	SECTION("GetUrl returns correct URL string with default port - HTTPS")
	{
		HttpUrl defaultPortUrl("https://secure.com/securepage");
		REQUIRE(defaultPortUrl.GetUrl() == "https://secure.com/securepage");
	}

	SECTION("GetUrl returns correct URL string for root document")
	{
		HttpUrl rootUrl("http://root.com");
		REQUIRE(rootUrl.GetDocument() == "");
		REQUIRE(rootUrl.GetUrl() == "http://root.com/");
	}
}

TEST_CASE("HttpUrl Output Operator", "[HttpUrl][Operator][Stream]")
{
	SECTION("Output stream for URL with custom port")
	{
		HttpUrl url("http://stream.test:1234/output");
		std::ostringstream oss;
		oss << url;
		REQUIRE(oss.str() == "http://stream.test:1234/output");
	}

	SECTION("Output stream for URL with default port")
	{
		HttpUrl url("https://stream.secure/index");
		std::ostringstream oss;
		oss << url;
		REQUIRE(oss.str() == "https://stream.secure/index");
	}

	SECTION("Output stream for URL with root document")
	{
		HttpUrl url("http://stream.root");
		std::ostringstream oss;
		oss << url;
		REQUIRE(oss.str() == "http://stream.root/");
	}
}
