#include <iostream>
#include "CMyString.h"

using namespace std;

int main()
{
	string a = "a";

	CMyString myString("abc");
	CMyString myString2(a);
	CMyString::iterator it = myString.begin();
	CMyString::iterator it2 = myString.begin();
	string test;
	copy(myString.begin(), myString.end(), back_inserter(test));


	string t;
}