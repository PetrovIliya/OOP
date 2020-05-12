#include <iostream>
#include <ctime>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../PrimeNumbersGenerator/PrimeNumbersGenerator.h"

using namespace std;


SCENARIO("generating prime numbers for 100000000 upperBound should take less then 12 seconds and result have to coantain 5761455 prime numbers")
{
	std::clock_t start = clock();
	double duration;

	set<int> primeNumbers = GeneratePrimeNumbersSet(100000000);

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	bool isOk = duration < 12 && primeNumbers.size() == 5761455;

	REQUIRE(isOk);
}

SCENARIO("after generating prime numbers for 2 upperBound we expect set of 2 as result")
{
	set<int> expectedResult = { 2 };

	set<int> primeNumbers = GeneratePrimeNumbersSet(2);


	REQUIRE(expectedResult == primeNumbers);
}


SCENARIO("after generating prime numbers for 10 upperBound we expect set of 2, 3, 5, 7 as result")
{
	set<int> expectedResult = {2, 3, 5, 7 };

	set<int> primeNumbers = GeneratePrimeNumbersSet(10);


	REQUIRE(expectedResult == primeNumbers);
}

SCENARIO("after generating prime numbers for 1 upperBound we expect empty set as result")
{
	set<int> expectedResult;

	set<int> primeNumbers = GeneratePrimeNumbersSet(1);


	REQUIRE(expectedResult == primeNumbers);
}

SCENARIO("after generating prime numbers for -1 upperBound we expect empty set as result")
{
	set<int> expectedResult;

	set<int> primeNumbers = GeneratePrimeNumbersSet(-1);


	REQUIRE(expectedResult == primeNumbers);
}