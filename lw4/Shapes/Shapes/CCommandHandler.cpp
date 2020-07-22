#include <algorithm>
#include <sstream>
#include <iterator>
#include "CCommandHandler.h"
#include "CCommandHandler.h"
#include "CCircle.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CCanvas.h"
#include "Util.h"
#include <fstream>

using namespace std;

CCommandHandler::CCommandHandler(istream& input, ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({ 
		{ "LineSegment", bind(&CCommandHandler::CreateLineSegment, this, placeholders::_1) },
		{ "Triangle", bind(&CCommandHandler::CreateTriangle, this, placeholders::_1) },
		{ "Rectangle", bind(&CCommandHandler::CreateRectangle, this, placeholders::_1) },
		{ "Circle", bind(&CCommandHandler::CreateCircle, this, placeholders::_1) },
		{ "Draw", bind(&CCommandHandler::Draw, this, placeholders::_1) } 
	})
{
}

bool CCommandHandler::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	if (action.empty())
	{
		return true;
	}

	if (action == "exit" || action == "\n")
	{
		PrintShapeWithMinPerimetr();
		PrintShapeWithMaxArea();
		return false;
	}

	auto it = m_actionMap.find(action);

	if (it == m_actionMap.end())
	{
		cout << "Unknown command!\nUsage: Circle, Trinagle, Rectangle or LineSegment with parameters\n";
		return true;
	}

	it->second(strm);
	return true;
}

void CCommandHandler::Draw(istream& args)
{
	CCanvas* canvas = new CCanvas(800, 800, "Canvas");
	canvas->Clear(WHITE_COLOR);
	for_each(m_drawableShapeList.begin(), m_drawableShapeList.end(), [&](auto shape) { shape->Draw(canvas); });
	canvas->Display();
	delete canvas;
}

void CCommandHandler::CreateLineSegment(istream& args)
{
	vector<string> shapeDescription;
	string description;
	getline(args, description);

	if (description.empty())
	{
		throw invalid_argument("No arguments!\nUsage: LineSegment point1.x point1.y point2.x point2.y [LineColor=#xxxxxx]\n");
	}

	istringstream descriptionStream(description);
	copy(istream_iterator<string>(descriptionStream), istream_iterator<string>(), back_inserter(shapeDescription));
	size_t argumentQuantity = shapeDescription.size();

	if (argumentQuantity < 4)
	{
		throw invalid_argument("Incorrect count of arguments!\nUsage: LineSegment point1.x point1.y point2.x point2.y [LineColor=#xxxxxx]\n");
	}

	CPoint point1 = { stod(shapeDescription[0]), stod(shapeDescription[1]) };
	CPoint point2 = { stod(shapeDescription[2]), stod(shapeDescription[3]) };
	uint32_t lineColor = -1;

	if (argumentQuantity > 4)
	{
		ArgumentWithName argumentWithName = ParseArgumentWithName(shapeDescription[4]);
		if (argumentWithName.name == "LineColor")
		{
			lineColor = ParseColor(argumentWithName.value);
		}
		else
		{
			throw invalid_argument("Argument " + argumentWithName.name + " not supported");
		}
	}

	auto lineSegment = make_unique<CLineSegment>(point1, point2, lineColor);
	m_drawableShapeList.push_back(lineSegment.get());
	m_shapeList.push_back(move(lineSegment));
	m_output << "Line segment is created\n";
}

void CCommandHandler::CreateTriangle(istream& args)
{
	vector<string> shapeDescription;
	string description;
	getline(args, description);

	if (description.empty())
	{
		throw invalid_argument("No arguments!\nUsage: Triangle vertex1.x vertex1.y vertex2.x vertex2.y vertex3.x vertex3.y [LineColor=#xxxxxx] [FillColor=#xxxxxx]\n");
	}

	istringstream descriptionStream(description);
	copy(istream_iterator<string>(descriptionStream), istream_iterator<string>(), back_inserter(shapeDescription));
	size_t quantityOfArgs = shapeDescription.size();

	if (quantityOfArgs < 6)
	{
		throw invalid_argument("Incorrect quantity of arguments!\nUsage: Triangle vertex1.x vertex1.y vertex2.x vertex2.y vertex3.x vertex3.y [LineColor=#xxxxxx] [FillColor=#xxxxxx]r\n");
	}

	CPoint vertex1 = { stod(shapeDescription[0]), stod(shapeDescription[1]) };
	CPoint vertex2 = { stod(shapeDescription[2]), stod(shapeDescription[3]) };
	CPoint vertex3 = { stod(shapeDescription[4]), stod(shapeDescription[5]) };
	uint32_t lineColor = 0;
	uint32_t fillColor = 0;

	if (quantityOfArgs > 6)
	{
		ParseLineAndFillColor(lineColor, fillColor, shapeDescription[6]);
	}

	if (quantityOfArgs > 7)
	{
		ParseLineAndFillColor(lineColor, fillColor, shapeDescription[7]);
	}

	auto triangle = make_unique<CTriangle>(vertex1, vertex2, vertex3, lineColor, fillColor);
	
	m_drawableShapeList.push_back(triangle.get());
	m_shapeList.push_back(move(triangle));
	m_output << "Triangle is created\n";
}

void CCommandHandler::CreateRectangle(istream& args)
{
	vector<string> shapeDescription;
	string description;
	getline(args, description);

	if (description.empty())
	{
		throw invalid_argument("No arguments!\nUsage: Rectangle leftTopVertex.x leftTopVertex.y width height [LineColor=#xxxxxx] [FillColor=#xxxxxx]\n");
	}

	istringstream descriptionStream(description);
	copy(istream_iterator<string>(descriptionStream), istream_iterator<string>(), back_inserter(shapeDescription));
	size_t quantityOfArgs = shapeDescription.size();

	if (quantityOfArgs < 4)
	{
		throw invalid_argument("Incorrect count of arguments!\nUsage: Rectangle leftTopVertex.x leftTopVertex.y width height [LineColor=#xxxxxx] [FillColor=#xxxxxx]\n");
	}

	CPoint leftTopVertex = { stod(shapeDescription[0]), stod(shapeDescription[1]) };
	double width = stod(shapeDescription[2]);
	double height = stod(shapeDescription[3]);
	uint32_t lineColor = 0;
	uint32_t fillColor = 0;

	if (quantityOfArgs > 4)
	{
		ParseLineAndFillColor(lineColor, fillColor, shapeDescription[4]);
	}

	if (quantityOfArgs > 5)
	{
		ParseLineAndFillColor(lineColor, fillColor, shapeDescription[5]);
	}

	auto rectangle = make_unique<CRectangle>(leftTopVertex, width, height, lineColor, fillColor);
	m_drawableShapeList.push_back(rectangle.get());
	m_shapeList.push_back(move(rectangle));
	m_output << "Rectangle is created\n";
}

void CCommandHandler::CreateCircle(istream& args)
{
	vector<string> shapeDescription;
	string description;
	getline(args, description);

	if (description.empty())
	{
		throw invalid_argument("No arguments!\nUsage: Circle center.x center.y radius [LineColor=#xxxxxx] [FillColor=#xxxxxx]\n");
	}

	istringstream descriptionStream(description);
	copy(istream_iterator<string>(descriptionStream), istream_iterator<string>(), back_inserter(shapeDescription));
	size_t quantityOfArgs = shapeDescription.size();

	if (shapeDescription.size() < 3)
	{
		throw invalid_argument("Incorrect count of arguments!\nUsage: Circle center.x center.y radius [LineColor=#xxxxxx] [FillColor=#xxxxxx]\n");
	}

	CPoint center = { stod(shapeDescription[0]), stod(shapeDescription[1]) };
	double radius = stod(shapeDescription[2]);
	uint32_t lineColor = 0;
	uint32_t fillColor = 0;

	if (quantityOfArgs > 3)
	{
		ParseLineAndFillColor(lineColor, fillColor, shapeDescription[3]);
	}

	if (quantityOfArgs > 4)
	{
		ParseLineAndFillColor(lineColor, fillColor, shapeDescription[4]);
	}

	auto circle = make_unique<CCircle>(center, radius, lineColor, fillColor);
	m_drawableShapeList.push_back(circle.get());
	m_shapeList.push_back(move(circle));
	m_output << "Circle is created\n";
}

void CCommandHandler::PrintShapeWithMinPerimetr()
{
	if (!m_shapeList.empty())
	{
		auto shapeMinPerimeter = min_element(m_shapeList.cbegin(), m_shapeList.cend(), [](const auto& arg1, const auto& arg2) {
			return arg1->GetPerimeter() < arg2->GetPerimeter();
			});

		m_output << "Min perimeter shape: " << (*shapeMinPerimeter)->ToString() << endl;
	}
}

void CCommandHandler::PrintShapeWithMaxArea()
{
	if (!m_shapeList.empty())
	{
		auto shapeMaxArea = max_element(m_shapeList.begin(), m_shapeList.end(), [](const auto& arg1, const auto& arg2) {
			return arg1->GetArea() < arg2->GetArea();
			});


		m_output << "Max area shape: " << (*shapeMaxArea)->ToString() << endl;
	}
}

uint32_t CCommandHandler::ParseColor(const string& color)
{
	if (color.size() < 2)
	{
		throw invalid_argument("Wrong color format!\n");
	}
	try
	{
		string preparedForConvertColor = color.substr(1, color.size() - 1) + "ff";
		return strtoul(preparedForConvertColor.c_str(), NULL, 16);
	}
	catch (const exception)
	{
		throw invalid_argument("Wrong color format!\n");
	}
}

ArgumentWithName CCommandHandler::ParseArgumentWithName(const string& argument)
{
	if (argument.empty())
	{
		throw invalid_argument("Wrong argument format\nUsage: argName=argValue");
	}

	vector<string> explodedArgument = ExplodeString(argument, "=");

	if (explodedArgument.size() < 2)
	{
		throw invalid_argument("Wrong argument format\nUsage: argName=argValue");
	}

	ArgumentWithName argumentWithName;
	argumentWithName.name = explodedArgument[0];
	argumentWithName.value = explodedArgument[1];

	return argumentWithName;
}

void CCommandHandler::ParseLineAndFillColor(uint32_t& lineColor, uint32_t& fillColor, const string& argument)
{
	if (argument.empty())
	{
		throw invalid_argument("Wrong argument format");
	}

	ArgumentWithName argumentWithName = ParseArgumentWithName(argument);
	if (argumentWithName.name == "LineColor")
	{
		lineColor = ParseColor(argumentWithName.value);
	}
	else if (argumentWithName.name == "FillColor")
	{
		fillColor = ParseColor(argumentWithName.value);
	}
	else
	{
		throw invalid_argument("Argument " + argumentWithName.name + " not supported");
	}
}