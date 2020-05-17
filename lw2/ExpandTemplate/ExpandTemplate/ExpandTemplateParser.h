#pragma once

#include <map>
#include <string>

const int MIN_VALUE_OF_ARGS = 3;

struct Params
{
	std::string inputFileName;
	std::string outputFileName;
	std::map <std::string, std::string> pattern;
};

Params ParseParams(int argc, char* argv[]);