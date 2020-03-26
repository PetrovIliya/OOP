#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include"../vector/vectorUtilities.h"
#include "../vector/vectorUtilities.cpp"

using namespace std;

SCENARIO("When supplying an empty vector, we also expect an empty vector as a result")
{
	vector<float> emptyVector = {};
	vector<float> vector = {};
	MultiplyVectorByMinElement(vector);
	REQUIRE(vector == emptyVector);
}

SCENARIO("When sorting an empty vector, we also expect an empty vector as a result")
{
	vector<float> emptyVector = {};
	vector<float> vector = {};
	SortVector(vector);
	REQUIRE(vector == emptyVector);
}

SCENARIO("When we multiply a vector by a minimal element, we expect to get a correct result")
{
	std::vector <float> vector = {2, 2, 3};
	std::vector <float> expectedVector = {4, 4, 6};
	MultiplyVectorByMinElement(vector);
	REQUIRE(vector == expectedVector);
}

SCENARIO("When we multiply a vector by a minimal element and vector have 1, we expect to get a same vector as result")
{
	std::vector <float> vector = { 1, 2, 3 };
	std::vector <float> expectedVector = { 1, 2, 3 };
	MultiplyVectorByMinElement(vector);
	REQUIRE(vector == expectedVector);
}