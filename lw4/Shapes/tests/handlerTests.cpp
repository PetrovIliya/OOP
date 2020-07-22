#include <iostream>
#define CATCH_CONFIG_MAIN
#define _USE_MATH_DEFINES

#include "../Shapes/CCommandHandler.h"
#include "../Shapes/Util.h"

#include "../../../catch2/catch.hpp"

using namespace std;

TEST_CASE("GetSegmentLength - mast return a distance between two points")
{
	CPoint point1(1.2, 3.4);
	CPoint point2(5.6, 7.8);
	double length = GetSegmentLength(point1, point2);
	CHECK(round(length * 100) / 100 == 6.22);
}

//----------LINE SEGMENT----------
SCENARIO("User through the command line creates a line segment")
{
	GIVEN("A command line")
	{
		stringstream input, output;
		CCommandHandler commandHandler(input, output);

		WHEN("User enters line segment parameters")
		{
			input << "LineSegment 1.2 3.4 5.6 7.8";
			CHECK(commandHandler.HandleCommand());

			THEN("He get a notification")
			{
				CHECK(output.str() == "Line segment is created\n");
			}
		}
	}
}

SCENARIO("User through the command line can create a line segment with line color")
{
	stringstream input, output;
	CCommandHandler commandHandler(input, output);

	WHEN("User enters line segment parameters with line color")
	{
		input << "LineSegment 1.2 3.4 5.6 7.8 LineColor=#ffffff";
		CHECK(commandHandler.HandleCommand());

		THEN("He get a notification")
		{
			CHECK(output.str() == "Line segment is created\n");
		}
	}
}

SCENARIO("User through the command line can't creates a line segment without params")
{
	GIVEN("A command line")
	{
		stringstream input, output;
		CCommandHandler commandHandler(input, output);

		WHEN("User enters only a figure name")
		{
			input << "LineSegment";

			THEN("He get an error message")
			{
				CHECK_THROWS_WITH(commandHandler.HandleCommand(), "No arguments!\nUsage: LineSegment point1.x point1.y point2.x point2.y [LineColor=#xxxxxx]\n");
			}
		}
	}
}

SCENARIO("User through the command line can't creates a line segment with not all params")
{
	GIVEN("A command line")
	{
		stringstream input, output;
		CCommandHandler commandHandler(input, output);

		WHEN("User enters line segment parameters without 2nd vertex")
		{
			input << "LineSegment 2 3";

			THEN("He get an error message")
			{
				CHECK_THROWS_WITH(commandHandler.HandleCommand(), "Incorrect count of arguments!\nUsage: LineSegment point1.x point1.y point2.x point2.y [LineColor=#xxxxxx]\n");
			}
		}
	}
}

//---------TRIANGLE----------
SCENARIO("User through the command line creates a triangle")
{
	GIVEN("A command line")
	{
		stringstream input, output;
		CCommandHandler commandHandler(input, output);

		WHEN("User enters triangle parameters")
		{
			input << "Triangle 1.2 3.4 5.6 7.8 9.0 1.2";
			CHECK(commandHandler.HandleCommand());

			THEN("He get a notification")
			{
				CHECK(output.str() == "Triangle is created\n");
			}
		}
	}
}

SCENARIO("User through the command line creates a triangle whith lineColor")
{
	GIVEN("A command line")
	{
		stringstream input, output;
		CCommandHandler commandHandler(input, output);

		WHEN("User enters triangle parameters")
		{
			input << "Triangle 1.2 3.4 5.6 7.8 9.0 1.2 LineColor=#ffffff";
			CHECK(commandHandler.HandleCommand());

			THEN("He get a notification")
			{
				CHECK(output.str() == "Triangle is created\n");
			}
		}
	}
}

SCENARIO("User through the command line creates a triangle whith fillColor")
{
	GIVEN("A command line")
	{
		stringstream input, output;
		CCommandHandler commandHandler(input, output);

		WHEN("User enters triangle parameters")
		{
			input << "Triangle 1.2 3.4 5.6 7.8 9.0 1.2 FillColor=#ffffff";
			CHECK(commandHandler.HandleCommand());

			THEN("He get a notification")
			{
				CHECK(output.str() == "Triangle is created\n");
			}
		}
	}
}

SCENARIO("User through the command line can't creates a triangle without params")
{
	GIVEN("A command line")
	{
		stringstream input, output;
		CCommandHandler commandHandler(input, output);

		WHEN("User enters only a figure name")
		{
			input << "Triangle";

			THEN("He get an error message")
			{
				CHECK_THROWS_WITH(commandHandler.HandleCommand(), "No arguments!\nUsage: Triangle vertex1.x vertex1.y vertex2.x vertex2.y vertex3.x vertex3.y [LineColor=#xxxxxx] [FillColor=#xxxxxx]\n");
			}
		}
	}
}

SCENARIO("User through the command line can't creates a triangle with not all params")
{
	GIVEN("A command line")
	{
		stringstream input, output;
		CCommandHandler commandHandler(input, output);

		WHEN("User enters triangle parameters without 3rd vertex")
		{
			input << "Triangle 1.2 3.4 5.6 7.8";

			THEN("He get an error message")
			{
				CHECK_THROWS_WITH(commandHandler.HandleCommand(), "Incorrect quantity of arguments!\nUsage: Triangle vertex1.x vertex1.y vertex2.x vertex2.y vertex3.x vertex3.y [LineColor=#xxxxxx] [FillColor=#xxxxxx]r\n");
			}
		}
	}
}

//----------RECTANGLE----------
SCENARIO("User through the command line creates a rectangle")
{
	GIVEN("A command line")
	{
		stringstream input, output;
		CCommandHandler commandHandler(input, output);

		WHEN("User enters rectangle parameters")
		{
			input << "Rectangle 1.2 3.4 9.2 4.1";
			CHECK(commandHandler.HandleCommand());

			THEN("He get a notification")
			{
				CHECK(output.str() == "Rectangle is created\n");
			}
		}
	}
}

SCENARIO("User through the command line can't creates a rectangle without params")
{
	GIVEN("A command line")
	{
		stringstream input, output;
		CCommandHandler commandHandler(input, output);

		WHEN("User enters only a figure name")
		{
			input << "Rectangle";

			THEN("He get an error message")
			{
				CHECK_THROWS_WITH(commandHandler.HandleCommand(), "No arguments!\nUsage: Rectangle leftTopVertex.x leftTopVertex.y width height [LineColor=#xxxxxx] [FillColor=#xxxxxx]\n");
			}
		}
	}
}

SCENARIO("User through the command line can't creates a rectangle with not all params")
{
	GIVEN("A command line")
	{
		stringstream input, output;
		CCommandHandler commandHandler(input, output);

		WHEN("User enters triangle parameters without height")
		{
			input << "Rectangle 1 2 3";

			THEN("He get an error message")
			{
				CHECK_THROWS_WITH(commandHandler.HandleCommand(), "Incorrect count of arguments!\nUsage: Rectangle leftTopVertex.x leftTopVertex.y width height [LineColor=#xxxxxx] [FillColor=#xxxxxx]\n");
			}
		}
	}
}

//----------CIRCLE----------
SCENARIO("User through the command line creates a circle")
{
	GIVEN("A command line")
	{
		stringstream input, output;
		CCommandHandler commandHandler(input, output);

		WHEN("User enters circle parameters")
		{
			input << "Circle 1.2 3.4 3";
			CHECK(commandHandler.HandleCommand());

			THEN("He get a notification")
			{
				CHECK(output.str() == "Circle is created\n");
			}
		}
	}
}

SCENARIO("User through the command line can't creates a circle without params")
{
	GIVEN("A command line")
	{
		stringstream input, output;
		CCommandHandler commandHandler(input, output);

		WHEN("User enters only a figure name")
		{
			input << "Circle";

			THEN("He get an error message")
			{
				CHECK_THROWS_WITH(commandHandler.HandleCommand(), "No arguments!\nUsage: Circle center.x center.y radius [LineColor=#xxxxxx] [FillColor=#xxxxxx]\n");
			}
		}
	}
}

SCENARIO("User through the command line can't creates a circle with not all params")
{
	GIVEN("A command line")
	{
		stringstream input, output;
		CCommandHandler commandHandler(input, output);

		WHEN("User enters circle parameters without radius")
		{
			input << "Circle 1 3";

			THEN("He get an error message")
			{
				CHECK_THROWS_WITH(commandHandler.HandleCommand(), "Incorrect count of arguments!\nUsage: Circle center.x center.y radius [LineColor=#xxxxxx] [FillColor=#xxxxxx]\n");
			}
		}
	}
}

SCENARIO("When the user finishes entering shapes, information is displayed about the shape with the smallest perimeter and largest area")
{
	GIVEN("A command line")
	{
		stringstream input, output;
		CCommandHandler commandHandler(input, output);

		WHEN("User enters circle parameters")
		{
			input << "Circle 2 2 3";
			CHECK(commandHandler.HandleCommand());

			THEN("He get a notification")
			{
				CHECK(output.str() == "Circle is created\n");
			}

			AND_WHEN("User enters other circle parameters")
			{
				input.str(string());
				output.str(string());
				input.clear();
				output.clear();
				input << "Circle 3 3 4";
				CHECK(commandHandler.HandleCommand());

				THEN("He get a notification")
				{
					CHECK(output.str() == "Circle is created\n");
				}

				AND_WHEN("User finish work whith programm, information is displayed about the shape with the smallest perimeter and largest area")
				{
					input.str(string());
					output.str(string());
					input.clear();
					output.clear();
					input << "exit";
				
					CHECK(!commandHandler.HandleCommand());
					string expectedOutput = string("Min perimeter shape: Circle:\n")
						+ "\tcenter = ( 2 , 2 ), radius = 3\n"
						+ "\tperimeter = 18.85\n"
						+ "\tarea = 28.27\n"
						+ "\tline color = 0\n"
						+ "\tfill color = 0\n"
						+ "\n"
						+ "Max area shape: Circle:\n"
						+ "\tcenter = ( 3 , 3 ), radius = 4\n"
						+ "\tperimeter = 25.13\n"
						+ "\tarea = 50.27\n"
						+ "\tline color = 0\n"
						+ "\tfill color = 0\n\n";

					THEN("He get a notification")
					{
						CHECK(output.str() == expectedOutput);
					}
				}
			}
		}
	}
}