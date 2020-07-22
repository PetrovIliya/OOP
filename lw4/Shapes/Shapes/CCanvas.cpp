#include <exception>
#include <string>
#include <sstream>

#include <iostream>
#include "CCanvas.h"

using namespace sf;
using namespace std;

CCanvas::CCanvas(const unsigned int width, const unsigned int height, const std::string& title) : m_window(VideoMode(width, height), title)
{}

void CCanvas::DrawLine(const CPoint& from, const CPoint& to, const uint32_t fillColor)
{
    VertexArray lines(LinesStrip, 2);
    lines[0].position = Vector2f((float)from.GetX(), (float)from.GetY());
    lines[0].color = Color(fillColor);
    lines[1].position = Vector2f((float)to.GetX(), (float)to.GetY());
    lines[1].color = Color(fillColor);

    m_window.draw(lines);
}

void CCanvas::DrawPolygon(const vector<CPoint>& points, const uint32_t lineColor, const uint32_t fillColor)
{
    size_t quantityOfPoints = points.size();
    if (quantityOfPoints < 2)
    {
        throw new invalid_argument("Too litle poiints for polygon");
    }

    ConvexShape polygon;
    polygon.setPointCount(quantityOfPoints);

    for (size_t i = 0; i < quantityOfPoints; i++)
    {
        polygon.setPoint(i, Vector2f((float)points[i].GetX(), (float)points[i].GetY()));
    }

    if (fillColor)
    {
        polygon.setFillColor(Color(fillColor));
    }

    if (lineColor)
    {
        polygon.setOutlineColor(Color(lineColor));
        polygon.setOutlineThickness(2.f);
    }

    m_window.draw(polygon);
}

void CCanvas::DrawCircle(const CPoint& center, const double radius, const uint32_t lineColor, const uint32_t fillColor)
{
    if (radius <= 0)
    {
        throw invalid_argument("Wrong radius");
    }

    CircleShape circle((float)radius);
    circle.setPointCount(200);
    circle.setPosition(Vector2f((float)center.GetX(), (float)center.GetY()));

    if (fillColor)
    {
        circle.setFillColor(Color(fillColor));
    }

    if (lineColor)
    {
        circle.setOutlineColor(Color(lineColor));
        circle.setOutlineThickness(2.f);
    }

    m_window.draw(circle);
}

void CCanvas::Clear(const uint32_t screenColor)
{
    m_window.clear(Color(screenColor));
}

void CCanvas::Close()
{
    m_window.close();
}

void CCanvas::Display()
{
    m_window.display();
    while (m_window.isOpen())
    {
        ExecutePollEvents();
    }
}

void CCanvas::ExecutePollEvents()
{
    Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            Close();
        }
    }
}