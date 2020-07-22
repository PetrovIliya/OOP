#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "ICanvas.h"

class CCanvas : public ICanvas
{
public:
	CCanvas(const unsigned int width, const unsigned int height, const std::string& title);
	void DrawLine(const CPoint& from, const CPoint& to, const uint32_t lineColor) override;
	void DrawPolygon(const std::vector<CPoint>& points, const uint32_t lineColor, const uint32_t fillColor) override;
	void DrawCircle(const CPoint& center, const double radius, const uint32_t lineColor, const uint32_t fillColor) override;
	void Display();
	void Close();
	void Clear(const uint32_t screenColor);
private:
	sf::RenderWindow m_window;

	void ExecutePollEvents();
};

