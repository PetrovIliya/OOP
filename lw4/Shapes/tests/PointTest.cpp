#include "../Shapes/CPoint.h"
#include "../../../catch2/catch.hpp"

TEST_CASE("CPoint - create a point", "[CPoint]")
{
	CPoint point(1, 2);

	CHECK(point.GetX() == 1);
	CHECK(point.GetY() == 2);
}
