#include <iostream>
#include <string>
#include <exception>
#include <fstream>

using namespace std;

string GetFileName(int argc, char* argv[])
{
	if (argc < 2)
	{
		throw new invalid_argument("No file name");
	}

	return argv[1];
}

fstream GetExistingOrCreateNewFile()
{

}

int main(int argc, char* argv[])
{
	try
	{
		string fileName = GetFileName(argc, argv);
	}
	catch (const exception& e)
	{
		cout << e.what() << '\n';
		return 1;
	}

	return 0;

}
