#pragma once

#include "CPoint.h"
#include <vector>
#include <string>

double GetSegmentLength(const CPoint& point1, const CPoint& point2);

std::vector<std::string> ExplodeString(const std::string& str, const std::string& separator);

std::string ConvertUint32ToHexColor(const uint32_t uint32);