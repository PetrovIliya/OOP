#pragma once
#include <vector>
#include "Cpoint.h"

class ICanvas
{
public:
	virtual void DrawLine(const CPoint& from, const CPoint& to, const uint32_t lineColor) = 0;
	virtual void DrawPolygon(const std::vector<CPoint>& points, const uint32_t lineColor, const uint32_t fillColor) = 0;
	virtual void DrawCircle(const CPoint& center, const double radius, const uint32_t lineColor, const uint32_t fillColor) = 0;
	virtual ~ICanvas() = default;
};