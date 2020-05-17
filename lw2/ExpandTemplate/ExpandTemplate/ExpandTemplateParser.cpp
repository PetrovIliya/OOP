#include <iostream>       
#include <exception>
#include "ExpandTemplateParser.h"

using namespace std;

bool IsEven(int number)
{
	return number % 2 == 0;
}

map<string, string> GetPattern(int argc, char* argv[])
{
	map<string, string> pattern;
	int quantityOfArgsForPattern = argc - MIN_VALUE_OF_ARGS;

	if (quantityOfArgsForPattern == 0)
	{
		return pattern;
	}

	if (quantityOfArgsForPattern < 0 || !IsEven(quantityOfArgsForPattern))
	{
		throw invalid_argument("Wrong quantity of parameters!\nUsage: ExpandTemplate.exe <input-file> <output-file> [<param> <value> [<param> <value> …]]\n");
	}

	for (int i = MIN_VALUE_OF_ARGS; i < argc; i += 2)
	{
		if (argv[i] != "")
		{
			pattern[argv[i]] = argv[i + 1];
		}
	}

	return pattern;
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

	params.inputFileName = argv[1];
	params.outputFileName = argv[2];

	params.pattern = GetPattern(argc, argv);

	return params;
}
