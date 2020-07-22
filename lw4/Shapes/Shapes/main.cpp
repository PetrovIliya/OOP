#include "CCommandHandler.h"
#include "IShape.h"
#include "CCanvas.h"

using namespace std;

int main(int argc, char argv[])
{
	try
	{
		CCommandHandler commandHandler(cin, cout);

		cout << "Hey! Type Circle, Trinagle, Rectangle or LineSegment with parameters, Draw to draw all shapes or exit to exit" << endl;

		while (!cin.eof() && !cin.fail())
		{
			cout << "> ";

			if (!commandHandler.HandleCommand())
			{
				break;
			}
		}
	}
	catch (const exception& e)
	{
		cerr << e.what() << endl;
		return 1;
	}

	return 0;
}

