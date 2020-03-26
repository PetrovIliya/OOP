#include "vector.h"

using namespace std;

void MultiplyVectorByNumber(vector<float>& vector, float number)
{
	transform(vector.begin(), vector.end(), vector.begin(), [number](float& element) { return (element * number); });
}

void SortVector(vector<float>& vector)
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

bool MultiplyVectorByMinElement(vector<float>& vector)
{
	if (vector.empty())
	{
		return false;
	}

	float minElement = *min_element(vector.begin(), vector.end());
	if (minElement != 1)
	{
		MultiplyVectorByNumber(vector, minElement);
	}
	return true;
}