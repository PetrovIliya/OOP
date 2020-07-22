#pragma once

#include "ISolidShape.h"
#include "CPoint.h"
#include "ICanvasDrawable.h"

class CRectangle : public ISolidShape, public ICanvasDrawable
{
public:
	CRectangle(const CPoint& leftTop, const double width, const double height, const uint32_t lineColor, const uint32_t fillColor);
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;

	double GetArea() const override;
	uint32_t GetFillColor() const override;

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;
	std::string GetType() const;
	void Draw(ICanvas* canvas) override;

private:
	void AppendProperties(std::ostream& strm) const;

	CPoint m_leftTopVertex;
	double m_width;
	double m_height;
	uint32_t m_lineColor;
	uint32_t m_fillColor;
};

