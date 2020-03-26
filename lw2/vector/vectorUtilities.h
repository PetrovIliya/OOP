#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <exception>
#include <optional>

void MultiplyVectorByNumber(std::vector<float>& vector, float number);

void SortVector(std::vector<float>& vector);

void PrintVector(std::vector<float>& vector);

std::vector<float> ReadVector(std::istream& inputStream);

bool MultiplyVectorByMinElement(std::vector<float>& vector);