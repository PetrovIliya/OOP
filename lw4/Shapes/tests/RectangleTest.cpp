#include "../Shapes/CRectangle.h"
#include "../../../catch2/catch.hpp"
#include "fakeit.hpp"

using namespace fakeit;
using namespace std;

TEST_CASE("The rectangle when created should have a coordinate of left top point, width, height, perimeter, area, line color and fill color")
{
	CPoint leftTopPoint(1.2, 3.4);

	WHEN("Created rectangle with width = 9.2, height = 4.1, line color #123456 and fill color #987654")
	{
		CRectangle rectangle(leftTopPoint, 9.2, 4.1, 123456, 987654);

		THEN("Can get type")
		{
			CHECK(rectangle.GetType() == "Rectangle");
		}
		AND_THEN("Can get coordinate of left top point")
		{
			CHECK(rectangle.GetLeftTop().GetX() == 1.2);
			CHECK(rectangle.GetLeftTop().GetY() == 3.4);
		}
		AND_THEN("Can get coordinate of right bottom point")
		{
			CHECK(round(rectangle.GetRightBottom().GetX() * 100) / 100 == 10.4);
			CHECK(round(rectangle.GetRightBottom().GetY() * 100) / 100 == -0.7);
		}
		AND_THEN("Can get width")
		{
			CHECK(rectangle.GetWidth() == 9.2);
		}
		AND_THEN("Can get height")
		{
			CHECK(rectangle.GetHeight() == 4.1);
		}
		AND_THEN("Can get perimeter")
		{
			CHECK(round(rectangle.GetPerimeter() * 100) / 100 == 26.6);
		}
		AND_THEN("Can get area")
		{
			CHECK(round(rectangle.GetArea() * 100) / 100 == 37.72);
		}
		AND_THEN("Can get line color")
		{
			CHECK(rectangle.GetOutlineColor() == 123456);
		}
		AND_THEN("Can get fill color")
		{
			CHECK(rectangle.GetFillColor() == 987654);
		}
	}
}

TEST_CASE("CRectangle - create a rectangle")
{
	CPoint leftTopPoint(1.2, 3.4);

	WHEN("Created rectangle with width = 9.2, height = 4.1, line color #123456 and fill color #987654")
	{
		CRectangle rectangle(leftTopPoint, 9.2, 4.1, 123456, 987654);

		AND_THEN("Can get all parameters of segment")
		{
			CHECK(rectangle.ToString() == "Rectangle:\n\tleft top vertex = ( 1.2 , 3.4 ), width = 9.2, height = 4.1\n\tperimeter = 26.6\n\tarea = 37.72\n\tline color = 123456\n\tfill color = 987654\n");
		}
	}
}

TEST_CASE("CRectangle - Draw a rectangle")
{
	CPoint leftTopPoint(1.2, 3.4);
	Mock<ICanvas> fakeCanvas;
	double width = 9.2;
	double height = 4.1;
	CRectangle rectangle(leftTopPoint, width, height, 0, 0);

	WHEN("Drawing a rectangle")
	{
		When(Method(fakeCanvas, DrawPolygon)).AlwaysReturn();
		rectangle.Draw(&fakeCanvas.get());

		THEN("Method DrawPolygon called once")
		{
			Verify(Method(fakeCanvas, DrawPolygon)).Once();
		}
	}
}