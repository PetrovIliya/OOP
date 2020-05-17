#include <iterator>
#include <fstream>
#include "FileUtil.h"

using namespace std;

string GetFileContent(const string& fileName)
{
	ifstream file(fileName);

	if (!file.is_open())
	{
		throw runtime_error("Cant open input file");
	}

	string content;
	copy(istreambuf_iterator<char>(file), istreambuf_iterator<char>(), back_inserter(content));
	file.close();

	return content;
}

void WriteContentIntoFile(const string& fileName, const string& content)
{
	ofstream file(fileName);

	if (!file.is_open())
	{
		throw runtime_error("Cant open output file");
	}

	copy(content.begin(), content.end(), ostream_iterator<char>(file));

	if (!file.flush())
	{
		throw std::runtime_error("Failed to save data on disk\n");
	}
	file.close();
}