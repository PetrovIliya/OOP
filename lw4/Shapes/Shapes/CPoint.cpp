#include "CPoint.h"

CPoint::CPoint(const double x, const double y)
	: m_x(x)
	, m_y(y)
{
}

double CPoint::GetX() const
{
	return m_x;
}

double CPoint::GetY() const
{
	return m_y;
}

bool operator == (const CPoint& point1, const CPoint point2)
{
	return point1.GetX() == point2.GetX() && point1.GetY() == point2.GetY();
}