
#include "catch2.h"

TEST_CASE("Empty string remains empty after decoding", "[HtmlDecode]")
{
	std::string empty;

	REQUIRE(HtmlDecode(empty) == empty);
}

TEST_CASE("Function throws an exception when invalid encoded sequence is given", "[HtmlDecode]")
{
	std::string testStr = "&aboba;";

	CHECK_THROWS_AS(HtmlDecode(testStr), std::runtime_error);
}

TEST_CASE("Given string is correctly decoded", "[HtmlDecode]")
{
	std::string testStr = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
	std::string resStr = R"(Cat <says> "Meow". M&M's)";

	REQUIRE(HtmlDecode(testStr) == resStr);
}

TEST_CASE("Function correctly decodes all defined encoded sequences", "[HtmlDecode]")
{
	std::string testStr = "&quot;&apos;&lt;&gt;&amp;";
	std::string resStr = R"("'<>&)";

	REQUIRE(HtmlDecode(testStr) == resStr);
}

TEST_CASE("Function correctly parse non-finished sequence as ordinary string", "[HtmlDecode]")
{
	std::string testStr = "&unfinished_sequence";

	REQUIRE(HtmlDecode(testStr) == testStr);
}
