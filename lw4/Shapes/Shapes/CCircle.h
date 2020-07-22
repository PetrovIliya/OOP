#pragma once

#include "CPoint.h"
#include "ISolidShape.h"
#include "ICanvasDrawable.h"

class CCircle : public ISolidShape, public ICanvasDrawable
{
public:
	CCircle(const CPoint& center, const double radius, const uint32_t lineColor, const uint32_t fillColor);
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;

	double GetArea() const override;
	uint32_t GetFillColor() const override;

	CPoint GetCenter() const;
	double GetRadius() const;
	std::string GetType() const;
	void Draw(ICanvas* canvas) override;

private:
	void AppendProperties(std::ostream& strm) const;

	CPoint m_center;
	double m_radius;
	uint32_t m_lineColor;
	uint32_t m_fillColor;
};