#include <iostream>
#include <math.h> 
#include <iterator>
#include <vector>
#include "PrimeNumbersGenerator.h"

using namespace std;

int GetNextPrimeNumber(const vector<bool>& sieve, int currentPrimeNumber)
{
	for (int i = currentPrimeNumber + 1; i < sieve.size(); i++)
	{
		if (sieve[i])
		{
			return i;
		}
	}

	throw runtime_error("Can't find next prime number to continue algorithm");
}

void MarkNotPrimeNumbers(vector<bool>& sieve, int upperBound)
{
	int prime = FIRST_PRIME_NUMBER;
	bool isPrimeFound = true;

	while (isPrimeFound)
	{
		isPrimeFound = false;
		for (int i = prime * prime; i <= upperBound; i += prime)
		{
			sieve[i] = false;
			isPrimeFound = true;
		}
		prime = GetNextPrimeNumber(sieve, prime);
	}
}

set<int> GeneratePrimeNumbersSet(int upperBound)
{
	set<int> primeNumbers;

	if (upperBound < FIRST_PRIME_NUMBER)
	{
		return primeNumbers;
	}

	if (upperBound == FIRST_PRIME_NUMBER)
	{
		return { FIRST_PRIME_NUMBER };
	}

	vector<bool> sieve(upperBound);
	fill_n(sieve.begin(), upperBound, true);

	MarkNotPrimeNumbers(sieve, upperBound);

	for (int i = FIRST_PRIME_NUMBER; i < sieve.size(); i++)
	{
		if (sieve[i])
		{
			primeNumbers.insert(i);
		}
	}

	return primeNumbers;
}