#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../HtmlDecode/HtmlDecoder.cpp"

using namespace std;

SCENARIO("When supplying an empty string, we also expect an empty string as a result")
{
	string htmlForDecode;
	HtmlDecode(htmlForDecode);
	REQUIRE(htmlForDecode == "");
}

SCENARIO("When supplying some string with out html entities, we expect smae string as a result")
{
	string htmlForDecode = "someString";
	HtmlDecode(htmlForDecode);
	REQUIRE(htmlForDecode == "someString");
}

SCENARIO("When supplying some string with html entities, we expect decoded string as a result")
{
	string htmlForDecode = "&quot;textInQutes&quot;";
	HtmlDecode(htmlForDecode);
	REQUIRE(htmlForDecode == "\"textInQutes\"");
}

SCENARIO("When supplying all html entities, we expect decoded string as a result")
{
	string htmlForDecode = "&quot;&apos;&lt;&gt;&amp;";
	HtmlDecode(htmlForDecode);
	REQUIRE(htmlForDecode == "\"\'<>&");
}