#include <iostream>
#include <string>
#include <exception>
#include <fstream>
#include <map>
#include <algorithm>
#include <Windows.h>
#include <vector>

using namespace std;
using Dictionary = map<string, string>;

const string TRANSLATE_DELIMITER = " - ";
const string EXIT_STRING = "...";

struct WordTranslate
{
	string word;
	string translate;
};

void Trim(string& str)
{
	remove_if(str.begin(), str.end(), [](const char& ch) { return ch == ' '; });
}

void ToLower(string& str)
{
	transform(str.begin(), str.end(), str.begin(), tolower);

}

string GetFileName(int argc, char* argv[])
{
	if (argc < 2 || argv[1] == "")
	{
		throw new invalid_argument("No file name");
	}

	return argv[1];
}

string GetTranslateFromDictionary(const string& word, const Dictionary& dictionary)
{
	string translate;
	if (dictionary.find(word) != dictionary.end())
	{
		translate = dictionary.find(word)->second;
	}

	return translate;
}

WordTranslate CreateWordTranslateFromFileLine(const string& line)
{
	WordTranslate wordTranslate;
	if (!line.empty())
	{
		auto wordEnd = line.find(TRANSLATE_DELIMITER);
		wordTranslate.word = line.substr(0, wordEnd);

		auto translateStart = wordEnd + TRANSLATE_DELIMITER.length();
		wordTranslate.translate = line.substr(translateStart);
	}
	
	return wordTranslate;
}

Dictionary CreateDictionaryFromFile(const string& fileName)
{
	ifstream file(fileName);
	Dictionary dictionary;
	if (!file.is_open() || file.eof())
	{
		return dictionary;
	}

	string line;
	while (getline(file, line))
	{
		WordTranslate wordTranslate = CreateWordTranslateFromFileLine(line);
		dictionary[wordTranslate.word] = wordTranslate.translate;
	}

	file.close();
	return dictionary;
}

void AddNewWord(const string& word, Dictionary& dictionary, vector<string>& newWords)
{
	string userInput;
	getline(cin, userInput);
	if (!userInput.empty())
	{
		dictionary[word] = userInput;
		newWords.push_back(word);
		cout << "Translate of word \"" << word << "\" saved as \"" << userInput << "\"" << endl;;
	}
	else
	{
		cout << "Word \"" << word << "\" was ignored" << endl;
	}
}

void SaveNewWords(Dictionary& dictionary, const vector<string>& newWords, const string& fileName)
{
	cout << "Changes have been discovered. Type \"y\" to save them or anything else otherwise" << endl;
	string userInput;
	cin >> userInput;
	ToLower(userInput);
	if (userInput == "y")
	{
		ofstream file(fileName, ios::app);

		if (!file.is_open())
		{
			throw new runtime_error("Can't open file for saving");
		}

		for (string newWord : newWords)
		{
			file << newWord << TRANSLATE_DELIMITER <<  dictionary[newWord] << endl;
		}

		file.close();
		cout << "Changes have been saved" << endl;
	}
}

void StartDialog(Dictionary& dictionary, const string& fileName)
{
	vector<string> newWords;
	string word;

	while (getline(cin, word))
	{
		ToLower(word);
		Trim(word);
		string translate = GetTranslateFromDictionary(word, dictionary);

		if (word == EXIT_STRING)
		{
			break;
		}

		if (translate.empty())
		{
			cout << "Unknown word \"" << word << "\" Type translation or empty string to skip it" << endl;
			AddNewWord(word, dictionary, newWords);
			continue;
		}

		cout << translate << endl;
	}

	if (!newWords.empty())
	{
		SaveNewWords(dictionary, newWords, fileName);
	}
}

void SetRuLnaguage()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}

int main(int argc, char* argv[])
{
	SetRuLnaguage();

	try
	{
		string fileName = GetFileName(argc, argv);
		Dictionary dictionary = CreateDictionaryFromFile(fileName);
		StartDialog(dictionary, fileName);
	}
	catch (const exception& e)
	{
		cout << e.what() << '\n';
		return 1;
	}

	return 0;
}