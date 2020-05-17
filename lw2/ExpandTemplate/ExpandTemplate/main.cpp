#include <iostream>
#include "ExpandTemplate.h"
#include "WindowsUtilities.h"
#include "FileUtil.h"
#include "ExpandTemplateParser.h"

using namespace std;

int main(int argc, char* argv[])
{
	SetRuLanguage();
	try
	{
		Params params = ParseParams(argc, argv);
		string tmpl = GetFileContent(params.inputFileName);
		string expandedTemplate;

		if (!params.pattern.empty() && !tmpl.empty())
		{
			expandedTemplate = ExpandTemplate(tmpl, params.pattern);
			WriteContentIntoFile(params.outputFileName, expandedTemplate);
		}
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
    return 0;
}