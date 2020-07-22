#include "../Shapes/CCircle.h"
#include "../Shapes/Util.h"
#include "fakeit.hpp"
#include "../../../catch2/catch.hpp"

using namespace fakeit;

TEST_CASE("The circle when created should have a perimeter, area, center and radius")
{
	CPoint point1(1.2, 3.4);

	WHEN("Created circle of line color #123456 and fillcolor #987654")
	{
		CCircle circle(point1, 3, 123456, 987654);

		THEN("Can get type")
		{
			CHECK(circle.GetType() == "Circle");
		}
		AND_THEN("Can get center point")
		{
			CHECK(circle.GetCenter().GetX() == 1.2);
			CHECK(circle.GetCenter().GetY() == 3.4);
		}
		AND_THEN("Can get radius")
		{
			CHECK(circle.GetRadius() == 3);
		}
		AND_THEN("Can get perimeter")
		{
			CHECK(round(circle.GetPerimeter() * 100) / 100 == 18.85);
		}
		AND_THEN("Can get area")
		{
			CHECK(round(circle.GetArea() * 100) / 100 == 28.27);
		}
		AND_THEN("Can get line color")
		{
			CHECK(circle.GetOutlineColor() == 123456);
		}
		AND_THEN("Can get fill color")
		{
			CHECK(circle.GetFillColor() == 987654);
		}
	}
}

TEST_CASE("CCircle - create a circle")
{
	CPoint center(1.2, 3.4);

	WHEN("Created circle with radius 3, line color #123456 and fill color #987654")
	{
		CCircle circle(center, 3, 123456, 987654);

		THEN("Can get all parameters of segment")
		{
			CHECK(circle.ToString() == "Circle:\n\tcenter = ( 1.2 , 3.4 ), radius = 3\n\tperimeter = 18.85\n\tarea = 28.27\n\tline color = 123456\n\tfill color = 987654\n");
		}
	}
}

TEST_CASE("CCircle - Draw a circle")
{
	CPoint center(1.2, 3.4);
	Mock<ICanvas> fakeCanvas;
	CCircle circle(center, 3, 123456, 987654);

	WHEN("Drawing a circle")
	{
		When(Method(fakeCanvas, DrawCircle)).AlwaysReturn();
		circle.Draw(&fakeCanvas.get());

		THEN("Method DrawCircle called once")
		{
			Verify(Method(fakeCanvas, DrawCircle)).Once();
		}
		AND_THEN("Method DrawCircle got right arguments")
		{
			Verify(Method(fakeCanvas, DrawCircle).Using(center, 3, 123456, 987654));
		}
	}
}