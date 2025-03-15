#include "catch2.h"

TEST_CASE("Function doesnt modify data when failed to parse url")
{
	parse_url::UrlData data;
	parse_url::UrlData original = data;
	CHECK_FALSE(parse_url::ParseURL("http://example.com:66666/path", data));
	CHECK(data == original);
}

TEST_CASE("Function extracts data from given url")
{
	parse_url::UrlData data;
	CHECK(parse_url::ParseURL("http://example.com:8080/path", data));
	CHECK(data == parse_url::UrlData{ parse_url::Protocol::HTTP, "example.com", 8080, "path" });
}

TEST_CASE("Function returns base port of http, https, ftp")
{
	parse_url::UrlData data;
	CHECK(parse_url::ParseURL("http://example.com", data));
	CHECK(data.port == 80);
	CHECK(parse_url::ParseURL("https://example.com", data));
	CHECK(data.port == 443);
	CHECK(parse_url::ParseURL("ftp://example.com", data));
	CHECK(data.port == 21);
}

TEST_CASE("Function correctly finds port that is equal to other protocol default port")
{
	parse_url::UrlData data;
	CHECK(parse_url::ParseURL("http://example.com:443", data));
	CHECK(data.port == 443);
	CHECK(parse_url::ParseURL("http://example.com:21", data));
	CHECK(data.port == 21);
	CHECK(parse_url::ParseURL("https://example.com:80", data));
	CHECK(data.port == 80);
	CHECK(parse_url::ParseURL("http://example.com:21", data));
	CHECK(data.port == 21);
	CHECK(parse_url::ParseURL("ftp://example.com:80", data));
	CHECK(data.port == 80);
	CHECK(parse_url::ParseURL("ftp://example.com:443", data));
	CHECK(data.port == 443);
}

TEST_CASE("Function fails to parse port greater than 65535")
{
	parse_url::UrlData data;
	CHECK_FALSE(parse_url::ParseURL("http://example.com:70000", data));
}

TEST_CASE("Function finds protocol written in any case")
{
	parse_url::UrlData data;
	CHECK(parse_url::ParseURL("HtTp://example.com", data));
	CHECK(data.protocol == parse_url::Protocol::HTTP);
	CHECK(parse_url::ParseURL("hTTps://example.com", data));
	CHECK(data.protocol == parse_url::Protocol::HTTPS);
	CHECK(parse_url::ParseURL("FtP://example.com", data));
	CHECK(data.protocol == parse_url::Protocol::FTP);
}

TEST_CASE("Function finds document with GET params")
{
	parse_url::UrlData data;
	CHECK(parse_url::ParseURL("http://example.com/path?param1=1?param2=2", data));
	CHECK(data == parse_url::UrlData{ parse_url::Protocol::HTTP, "example.com", 80, "path?param1=1?param2=2" });
}
