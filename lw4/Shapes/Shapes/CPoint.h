#pragma once

class CPoint
{
public:
	CPoint(const double x, const double y);
	double GetX() const;
	double GetY() const;
	friend bool operator == (const CPoint& point1, const CPoint point2);


private:
	double m_x, m_y;
};