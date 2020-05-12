#include <iostream>
#include <exception>
#include <string>
#include <iterator>
#include "PrimeNumbersGenerator.h"

using namespace std;

int GetUpperBound(int argc, char* argv[])
{
	if (argc < 2 || argv[1] == "")
	{
		throw new invalid_argument("Upper bound is requered");
	}

	int upperBound = stoi(argv[1]);

	if (upperBound > MAX_UPPER_BOUND)
	{
		throw new invalid_argument("Upper bound should be less then " + MAX_UPPER_BOUND);
	}

	return upperBound;
}

int main(int argc, char* argv[])
{
	try
	{
		int upperBound = GetUpperBound(argc, argv);
		if (upperBound < FIRST_PRIME_NUMBER)
		{
			cout << "No prime numbers";
		}
		set<int> primeNumbers = GeneratePrimeNumbersSet(upperBound);
		copy(primeNumbers.begin(), primeNumbers.end(), ostream_iterator<int>(std::cout, " "));
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}
	catch (const invalid_argument& ia)
	{
		cout << "tut";
		cout << ia.what() << endl;
		return 1;
	};

	return 0;
}