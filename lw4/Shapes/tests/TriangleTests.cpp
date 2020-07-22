#include "../Shapes/CTriangle.h"
#include "../../../catch2/catch.hpp"
#include "fakeit.hpp"

using namespace fakeit;

TEST_CASE("The triangle when created should have a three vertex, perimeter, area, line color and fill color", "[CTriangle]")
{
	CPoint point1(1.2, 3.4);
	CPoint point2(5.6, 7.8);
	CPoint point3(9.0, 1.2);

	WHEN("Created triangle with line color #123456 and fill color #987654")
	{
		CTriangle triangle(point1, point2, point3, 123456, 987654);

		THEN("Can get type")
		{
			CHECK(triangle.GetType() == "Triangle");
		}
		AND_THEN("Can get coordinate of vertex1")
		{
			CHECK(triangle.GetVertex1().GetX() == 1.2);
			CHECK(triangle.GetVertex1().GetY() == 3.4);
		}
		AND_THEN("Can get coordinate of vertex2")
		{
			CHECK(triangle.GetVertex2().GetX() == 5.6);
			CHECK(triangle.GetVertex2().GetY() == 7.8);
		}
		AND_THEN("Can get coordinate of vertex3")
		{
			CHECK(triangle.GetVertex3().GetX() == 9.0);
			CHECK(triangle.GetVertex3().GetY() == 1.2);
		}
		AND_THEN("Can get perimeter")
		{
			CHECK(round(triangle.GetPerimeter() * 100) / 100 == 21.75);
		}
		AND_THEN("Can get area")
		{
			CHECK(round(triangle.GetArea() * 100) / 100 == 22);
		}
		AND_THEN("Can get line color")
		{
			CHECK(triangle.GetOutlineColor() == 123456);
		}
		AND_THEN("Can get fill color")
		{
			CHECK(triangle.GetFillColor() == 987654);
		}
	}
}

TEST_CASE("CTriangle - create a triangle")
{
	CPoint point1(1.2, 3.4);
	CPoint point2(5.6, 7.8);
	CPoint point3(9.0, 1.2);

	WHEN("Created triangle with line color #123456 and fill color #987654")
	{
		CTriangle triangle(point1, point2, point3, 123456, 987654);

		THEN("Can get all parameters of segment")
		{
			CHECK(triangle.ToString() == "Triangle:\n\tfirst vertex = ( 1.2 , 3.4 ), second vertex = ( 5.6 , 7.8 ), third vertex = ( 9 , 1.2 )\n\tperimeter = 21.75\n\tarea = 22\n\tline color = 123456\n\tfill color = 987654\n");
		}
	}
}

TEST_CASE("CTriangle - draw a triangle")
{
	CPoint point1(1.2, 3.4);
	CPoint point2(5.6, 7.8);
	CPoint point3(9.0, 1.2);
	CTriangle triangle(point1, point2, point3, 123456, 987654);
	Mock<ICanvas> fakeCanvas;

	WHEN("Drawing a triangle")
	{
		When(Method(fakeCanvas, DrawPolygon)).AlwaysReturn();
		triangle.Draw(&fakeCanvas.get());

		THEN("Method DrawPolygon called once")
		{
			Verify(Method(fakeCanvas, DrawPolygon)).Once();
		}
	}
}