#include <string>
#include <iostream>
#include "Dictionary.h"
#include "WindowsUtilities.h"

using namespace std;

string GetFileName(int argc, char* argv[])
{
	string fileName;
	if (argc < 2 || argv[1] == "")
	{
		cout << "Enter the name of the file in which you want to use as dictionary: " << endl;
		getline(cin, fileName);
	}
	else
	{
		fileName = argv[1];
	}

	return fileName;
}

int main(int argc, char* argv[])
{
	SetRuLanguage();

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