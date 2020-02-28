#include <iostream>
#include <fstream>
#include <string>
#include <exception>

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	size_t pos = 0;
	std::string result;
	if (searchString.length() == 0)
	{
		return subject;
	}

	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);
		result.append(subject, pos, foundPos - pos);
		if (foundPos == std::string::npos)
		{
			break;
		}
		result.append(replacementString);
		pos = foundPos + searchString.length();
	}
	return result;
}

void CheckFiles(std::ifstream &inputFile, std::ofstream &outputFile)
{
	if (!inputFile.is_open())
	{
		throw std::exception("Not able to open input file.");
	}
	if (!outputFile.is_open())
	{
		throw std::exception("Not able to open output file");
	}
}

void CopyFileWithReplace(std::string& inputFileName, std::string& outputFileName,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;
	std::ifstream inputFile;
	std::ofstream outputFile;

	inputFile.open(inputFileName);
	outputFile.open(outputFileName);
	CheckFiles(inputFile, outputFile);

	while (std::getline(inputFile, line))
	{
		outputFile << ReplaceString(line, searchString, replacementString) << "\n";
	}

	if (!outputFile.flush())
	{
		throw std::exception("Failed to save data on disk\n");
	}
}

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return 1;
	}

	std::string inputFileName = argv[1];
	std::string outputFileName = argv[2];

	std::string search = argv[3];
	std::string replace = argv[4];

	try
	{
		CopyFileWithReplace(inputFileName, outputFileName, search, replace);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}

	return 0;
}