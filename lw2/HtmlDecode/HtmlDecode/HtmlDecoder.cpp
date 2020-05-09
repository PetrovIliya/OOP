#include <map>
#include <string>
#include<iostream>
#include "HtmlDecoder.h"

using namespace std;

const string htmlEntityList[] = { "&quot;", "&apos;", "&lt;", "&gt;", "&amp;" };
map<string, string> replacement{ { "&quot;", "\"" }, { "&apos;", "'" }, { "&lt;", "<" }, { "&gt;", ">" }, { "&amp;", "&" } };

void replaceHtmlEntity(string& html, const string& htmlEntity)
{
	size_t pos;

	while ((pos = html.find(htmlEntity, 0)) != string::npos)
	{
		html.replace(pos, htmlEntity.length(), replacement[htmlEntity]);
	}
}

void HtmlDecode(string& html)
{
	for (string htmlEntity : htmlEntityList)
	{
		replaceHtmlEntity(html, htmlEntity);
	}
}

