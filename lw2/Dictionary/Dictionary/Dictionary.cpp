#include <iostream>
#include <string>
#include <exception>
#include <fstream>
#include <map>

using namespace std;
using Dictionary = map<string, string>;

const string TMP_FILE_NAME = "tmp.txt";
const string TRANSLATE_DELIMITER = " - ";
const string EXIT_STRING = "...";

struct WordTranslate
{
	string word;
	string translate;
};

string GetUserOrTmpFileName(int argc, char* argv[])
{
	if (argc < 2 || argv[1] == "")
	{
		return TMP_FILE_NAME;
	}

	return argv[1];
}

WordTranslate CreateWordTranslateFromLine(const string& line)
{
	WordTranslate wordTranslate;
	auto wordEnd = line.find(TRANSLATE_DELIMITER);
	wordTranslate.word = line.substr(0, wordEnd);

	auto translateStart = wordEnd + TRANSLATE_DELIMITER.length();
	wordTranslate.translate = line.substr(translateStart);
	
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
		WordTranslate wordTranslate = CreateWordTranslateFromLine(line);
		dictionary[wordTranslate.word] = wordTranslate.translate;
	}

	return dictionary;
}

void StartDialog(Dictionary dictionary)
{
	Dictionary newWords;
	string wordForTranslate;

	while (cin >> wordForTranslate)
	{
		cout << wordForTranslate << endl;

		if (wordForTranslate == EXIT_STRING)
		{
			break;
		}


	}
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");
	try
	{
		string fileName = GetUserOrTmpFileName(argc, argv);
		Dictionary dictionary = CreateDictionaryFromFile(fileName);
		StartDialog(dictionary);
	}
	catch (const exception& e)
	{
		cout << e.what() << '\n';
		return 1;
	}

	return 0;
}
