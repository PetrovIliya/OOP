#include <cmath>
#include "Util.h"

using namespace std;

double GetSegmentLength(const CPoint& point1, const CPoint& point2)
{
	return sqrt(pow(point1.GetX() - point2.GetX(), 2) + pow(point1.GetY() - point2.GetY(), 2));
}

vector<string> ExplodeString(const string& str, const string& separator)
{
	vector<string> vec;
	for (size_t p = 0, q = 0; p != str.npos; p = q)
	{
		vec.push_back(str.substr(p + (p != 0), (q = str.find(separator, p + 1)) - p - (p != 0)));
	}

	return vec;
}

std::string ConvertUint32ToHexColor(const uint32_t uint32)
{
	if (uint32 > 0xffffffff)
	{
		throw invalid_argument("wrong color format");
	}

	string hexColor;
	char buff[9];
	sprintf_s(buff, "%x", uint32);
	hexColor = buff;

	return hexColor.substr(0, 6);
}