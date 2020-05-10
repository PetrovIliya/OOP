#pragma once
#include <map>
#include <string>
#include <vector>

using Dictionary = std::map<std::string, std::string>;

const std::string TRANSLATE_DELIMITER = " - ";
const std::string EXIT_STRING = "...";

struct WordTranslate
{
	std::string word;
	std::string translate;
};

void StartDialog(Dictionary& dictionary, const std::string& fileName);
void StartSavingNewWordsDialog(Dictionary& dictionary, const std::vector<std::string>& newWords, const std::string& fileName);
void SaveNewWords(Dictionary& dictionary, const std::vector<std::string>& newWords, const std::string& fileName);
void AddNewWord(const std::string& word, Dictionary& dictionary, std::vector<std::string>& newWords);
Dictionary CreateDictionaryFromFile(const std::string& fileName);
WordTranslate CreateWordTranslateFromFileLine(const std::string& line);
std::string GetTranslateFromDictionary(const std::string& word, const Dictionary& dictionary);