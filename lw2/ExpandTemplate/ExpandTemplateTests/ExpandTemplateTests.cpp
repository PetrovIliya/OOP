#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../ExpandTemplate/ExpandTemplate.h"
#include "../ExpandTemplate/WindowsUtilities.h"
#include "../ExpandTemplate/FileUtil.h"
#include "../ExpandTemplate/ExpandTemplateParser.h"

using namespace std;

SCENARIO("when we try to read nonexisting file, we expect an exception")
{
	bool wasException = false;
	try
	{
		GetFileContent("nonexisting.txt");
	}
	catch (const exception)
	{
		wasException = true;
	}

	REQUIRE(wasException);
}

SCENARIO("when we run the program without parameters, we expect an exception")
{
	char argv0[] = "ExpandTemplateTests.exe";
	char* argv[] = { argv0 };
	bool wasException = false;
	try
	{
		ParseParams(1, argv);
	}
	catch (const exception)
	{
		wasException = true;
	}
	
	REQUIRE(wasException);
}

SCENARIO("when we run the program with not even quantity of pattern params, we expect an exception")
{
	char argv0[] = "ExpandTemplateTests.exe";
	char argv1[] = "input.txt";
	char argv2[] = "output.txt";
	char argv3[] = "abc";
	char* argv[] = { argv0, argv1, argv2};
	bool wasException = false;
	try
	{
		ParseParams(4, argv);
	}
	catch (const exception&)
	{
		wasException = true;
	}

	REQUIRE(wasException);
}

SCENARIO("When supplying an empty template, we also expect an empty template as a result")
{
	map <string, string> params = { {"a", {"b"}} };
	string expandedTemplate = ExpandTemplate("", params);
	REQUIRE(expandedTemplate == "");
}

SCENARIO("When supplying an empty params, we expect unchanged template")
{
	string tpl = "test";
	map <string, string> params;
	string expandedTemplate = ExpandTemplate(tpl, params);
	REQUIRE(expandedTemplate == tpl);
}

SCENARIO("When supplying correct params and template, we expect correct replacement")
{
	string tpl = "dog eat meat";
	map <string, string> params = { {"meat", "cat"} };
	string expandedTemplate = ExpandTemplate(tpl, params);
	REQUIRE(expandedTemplate == "dog eat cat");
}

SCENARIO("If there are several possible substitution options, the parameter with the longest length should be selected.")
{
	string tpl = "abb";
	map <string, string> params = { {"ab", "z"}, {"abb", "z"} };
	string expandedTemplate = ExpandTemplate(tpl, params);
	REQUIRE(expandedTemplate == "z");
}