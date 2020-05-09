#include <string>
#include <iostream>
#include "HtmlDecoder.h"

using namespace std;

int main()
{
	string html;

	while (cin >> html)
	{
		HtmlDecode(html);
		cout << html << endl;
	}

	return 0;
}