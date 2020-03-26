#include "vectorUtilities.h"

using namespace std;

int main()
{
	try
	{
		vector<float> vector = ReadVector(cin);
		if (!MultiplyVectorByMinElement(vector))
		{
			return 0;
		}
		SortVector(vector);
		PrintVector(vector);
	}
	catch (const std::exception & e)
	{
		cout << e.what() << '\n';
	}

	return 0;
}