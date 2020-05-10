#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Dictionary/Dictionary.h"
#include "../Dictionary/StringUtilities.h"
#include "../Dictionary/WindowsUtilities.h"

using namespace std;

SCENARIO("Expect translate of word cat as кошка")
{
	SetRuLanguage();
	string fileName = "test.txt";
	ofstream file(fileName);
	file << "cat" << TRANSLATE_DELIMITER << "кошка" << endl;
	file.close();
	Dictionary dictionary = CreateDictionaryFromFile(fileName);
	string result = GetTranslateFromDictionary("cat", dictionary);
	REQUIRE(result == "кошка");
}