#pragma once
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <functional>
#include <memory>
#include "IShape.h"
#include "ICanvas.h"
#include "ICanvasDrawable.h"

using ActionMap = std::map < std::string, std::function<void(std::istream& args) > >;
const uint32_t WHITE_COLOR = 4294967295;

struct ArgumentWithName
{
	std::string name;
	std::string value;
};

class CCommandHandler
{
public:
	CCommandHandler(std::istream& input, std::ostream& output);
	bool HandleCommand();
	void PrintShapeWithMinPerimetr();
	void PrintShapeWithMaxArea();
	void Draw(std::istream& args);

private:
	void CreateLineSegment(std::istream& args);
	void CreateTriangle(std::istream& args);
	void CreateRectangle(std::istream& args);
	void CreateCircle(std::istream& args);
	uint32_t ParseColor(const std::string& color);
	ArgumentWithName ParseArgumentWithName(const std::string& argument);
	void ParseLineAndFillColor(uint32_t& lineColor, uint32_t& fillColor, const std::string& argument);

	std::istream& m_input;
	std::ostream& m_output;
	const ActionMap m_actionMap;
	std::vector<std::unique_ptr<IShape>> m_shapeList;
	std::vector<ICanvasDrawable*> m_drawableShapeList;
};

