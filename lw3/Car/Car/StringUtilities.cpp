#include <algorithm>
#include "StringUtilities.h"

using namespace std;

void Trim(string& str)
{
	remove_if(str.begin(), str.end(), [](const char& ch) { return ch == ' '; });
}

void ToLower(string& str)
{
	transform(str.begin(), str.end(), str.begin(), tolower);

}