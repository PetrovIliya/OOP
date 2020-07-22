#include <iostream>
#include <sstream>
#include <iomanip>
#include "CRectangle.h"
#include "Util.h"

using namespace std;

CRectangle::CRectangle(const CPoint& leftTop, const double width, const double height, const uint32_t lineColor, const uint32_t fillColor)
	: m_leftTopVertex(leftTop)
	, m_width(width)
	, m_height(height)
	, m_lineColor(lineColor)
	, m_fillColor(fillColor)
{
}

void CRectangle::Draw(ICanvas* canvas)
{
	double rightX = m_leftTopVertex.GetX() + m_width;
	double BottomY = m_leftTopVertex.GetY() + m_height;

	CPoint rightTopVertex(rightX, m_leftTopVertex.GetY());
	CPoint leftBottomVertex(m_leftTopVertex.GetX(), BottomY);
	CPoint rightButtomVertex(rightX, BottomY);

	vector<CPoint> points = { m_leftTopVertex , rightTopVertex , rightButtomVertex ,  leftBottomVertex };
	canvas->DrawPolygon(points, m_lineColor, m_fillColor);
}

string CRectangle::ToString() const
{
	ostringstream s;
	s << GetType() << ":" << endl;
	AppendProperties(s);
	s << setprecision(4)
		<< "\tperimeter = " << GetPerimeter() << endl
		<< "\tarea = " << GetArea() << endl
		<< "\tline color = " << "#" << setfill('0') << setw(6) << ConvertUint32ToHexColor(m_lineColor) << endl
		<< "\tfill color = " << "#" << setfill('0') << setw(6) << ConvertUint32ToHexColor(m_fillColor) << endl;

	return s.str();
}

string CRectangle::GetType() const
{
	return "Rectangle";
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTopVertex;
}

CPoint CRectangle::GetRightBottom() const
{
	CPoint rigthBttom(m_leftTopVertex.GetX() + m_width, m_leftTopVertex.GetY() - m_height);
	return rigthBttom;
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

double CRectangle::GetPerimeter() const
{
	return GetWidth() * 2 + GetHeight() * 2;
}

double CRectangle::GetArea() const
{
	return GetWidth() * GetHeight();
}

uint32_t CRectangle::GetOutlineColor() const
{
	return m_lineColor;
}

uint32_t CRectangle::GetFillColor() const
{
	return m_fillColor;
}

void CRectangle::AppendProperties(ostream& s) const
{
	s << "\tleft top vertex = ( " << m_leftTopVertex.GetX() << " , " << m_leftTopVertex.GetY()
		<< " ), width = " << m_width << ", height = " << m_height << endl;
}