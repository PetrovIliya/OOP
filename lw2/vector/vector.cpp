#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>

using namespace std;

void MultiplyVectorByNumber(vector<float>& vector, float number)
{
	transform(vector.begin(), vector.end(), vector.begin(), [number](float &element) { return (element * number); });
}

void SortVector(vector<float> &vector)
{
	sort(vector.begin(), vector.end());
}

void PrintVector(vector<float>& vector)
{
	copy(vector.begin(), vector.end(), ostream_iterator<float>(cout, " "));
}

vector<float> ReadVector(istream& inputStream)
{
	string line;
	vector<float> vector;
	if (getline(inputStream, line))
	{
		stringstream stringIterator(line);
		copy(istream_iterator<float>(stringIterator), istream_iterator<float>(), inserter(vector, vector.end()));
	}

	return vector;
}

int main()
{
	try
	{
		vector<float> vector = ReadVector(cin);
		if (vector.empty())
		{
			return 0;
		}

		float minElement = *min_element(vector.begin(), vector.end());
		if (minElement != 1)
		{
			MultiplyVectorByNumber(vector, minElement);
		}
		SortVector(vector);
		PrintVector(vector);
	}
	catch (const std::exception& e)
	{
		cout << e.what() << '\n';
	}
	
    return 0;
}
