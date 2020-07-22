#pragma once
#include "CPoint.h"
#include "IShape.h"
#include "ICanvasDrawable.h"

class CLineSegment final : public IShape, public ICanvasDrawable
{
public:
	CLineSegment(const CPoint& point1, const CPoint& point2, const uint32_t color);

	double GetPerimeter() const override;
	double GetArea() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;

	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
	std::string GetType() const;
	void Draw(ICanvas* canvas) override;

private:
	void AppendProperties(std::ostream& strm) const;

	CPoint m_startPoint;
	CPoint m_endPoint;
	uint32_t m_color;
};
