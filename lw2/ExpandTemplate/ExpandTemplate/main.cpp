#include <iostream>
#include <map>
#include <string>
#include <exception>
#include <fstream>
#include <algorithm>
#include <iterator>
#include "ExpandTemplate.h"

using namespace std;

const int MIN_VALUE_OF_ARGS = 3;

struct Params
{
	ifstream inputFile;
	ofstream outputFile;
	map <string, string> templateVariables;
};

bool IsEven(int number)
{
	return number % 2 == 0;
}

map<string, string> GetTemplateVariables(int argc, char* argv[])
{
	map<string, string> templateVariables;
	int quantityOfArgsForTemplateVariables = argc - MIN_VALUE_OF_ARGS;
	if (quantityOfArgsForTemplateVariables == 0)
	{
		return templateVariables;
	}

	if (quantityOfArgsForTemplateVariables < 0 || !IsEven(quantityOfArgsForTemplateVariables))
	{
		throw invalid_argument("Wrong quantity of parameters!\nUsage: ExpandTemplate.exe <input-file> <output-file> [<param> <value> [<param> <value> …]]\n");
	}

	for (int i = MIN_VALUE_OF_ARGS; i < argc; i+=2)
	{
		templateVariables[argv[i]] = argv[i + 1];
	}

	return templateVariables;
}

Params ParseParams(int argc, char* argv[])
{
	if (argc < MIN_VALUE_OF_ARGS)
	{
		throw invalid_argument("Wrong quantity of parameters!\nUsage: ExpandTemplate.exe <input-file> <output-file> [<param> <value> [<param> <value> …]]\n");
	}

	if (argv[1] == "" || argv[2] == "")
	{
		throw invalid_argument("File names can't be empty");
	}

	Params params;

	params.inputFile.open(argv[1], ios::in);

	if (!params.inputFile.is_open())
	{
		throw runtime_error("Cant open input file");
	}

	params.outputFile.open(argv[2], ios::out);

	if (!params.outputFile.is_open())
	{
		throw runtime_error("Cant open output file");
	}

	params.templateVariables = GetTemplateVariables(argc, argv);

	return params;
}

string GetTemplateFromFile(ifstream& file)
{
	string tmpl;
	copy(istreambuf_iterator<char>(file), istreambuf_iterator<char>(), back_inserter(tmpl));

	return tmpl;
}

int main(int argc, char* argv[])
{
	try
	{
		Params params = ParseParams(argc, argv);
		string tmpl = GetTemplateFromFile(params.inputFile);
		string expandTemplate = ExpandTemplate(tmpl, params.templateVariables);
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
    return 0;
}