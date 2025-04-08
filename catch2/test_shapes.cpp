#include "catch2.h"
#define _USE_MATH_DEFINES
#include <math.h>

std::string GetCanvasOutput(const std::function<void(MockCanvas&)>& drawAction)
{
	std::ostringstream output;
	MockCanvas mock(output);
	drawAction(mock);
	return output.str();
}

TEST_CASE("Rectangle full functionality")
{
	Rectangle rect({ 1, 5 }, { 4, 1 }, 0x00FF00FF, 0xFF0000FF);

	SECTION("Geometric properties")
	{
		REQUIRE(rect.GetLeftTop() == Point(1, 5));
		REQUIRE(rect.GetRightBottom() == Point(4, 1));
		REQUIRE(rect.GetWidth() == 3.0);
		REQUIRE(rect.GetHeight() == 4.0);
		REQUIRE(rect.GetArea() == 12.0);
		REQUIRE(rect.GetPerimeter() == 14.0);
	}

	SECTION("Color properties")
	{
		REQUIRE(rect.GetFillColor().ToInt() == 0x00FF00FF);
		REQUIRE(rect.GetOutlineColor().ToInt() == 0xFF0000FF);
	}

	SECTION("Drawing calls")
	{
		auto output = GetCanvasOutput([&rect](MockCanvas& mock) {
			rect.Draw(mock);
		});

		REQUIRE(output.find("FillPolygon") != std::string::npos);
		REQUIRE(output.find("DrawPolygon") != std::string::npos);
		REQUIRE(output.find("(1.0, 5.0)") != std::string::npos);
		REQUIRE(output.find("(4.0, 1.0)") != std::string::npos);
		REQUIRE(output.find("00FF00FF") != std::string::npos);
		REQUIRE(output.find("FF0000FF") != std::string::npos);
	}
}

TEST_CASE("Circle full functionality")
{
	Circle circle({ 0, 0 }, 1.0, 0x0000FFFF, 0x00FF00FF);

	SECTION("Geometric properties")
	{
		REQUIRE(circle.GetCenter() == Point(0, 0));
		REQUIRE(circle.GetRadius() == 1.0);
		REQUIRE(circle.GetArea() == M_PI);
		REQUIRE(circle.GetPerimeter() == 2 * M_PI);
	}

	SECTION("Drawing calls")
	{
		auto output = GetCanvasOutput([&circle](MockCanvas& mock) {
			circle.Draw(mock);
		});

		REQUIRE(output.find("FillCircle") != std::string::npos);
		REQUIRE(output.find("DrawCircle") != std::string::npos);
		REQUIRE(output.find("(0.0, 0.0)") != std::string::npos);
		REQUIRE(output.find("radius 1.0") != std::string::npos);
		REQUIRE(output.find("0000FFFF") != std::string::npos);
		REQUIRE(output.find("00FF00FF") != std::string::npos);
	}
}

TEST_CASE("LineSegment full functionality")
{
	LineSegment line({ 0, 0 }, { 3, 4 }, 0xFF00FFFF);

	SECTION("Geometric properties")
	{
		REQUIRE(line.GetStartPoint() == Point(0, 0));
		REQUIRE(line.GetEndPoint() == Point(3, 4));
		REQUIRE(line.GetPerimeter() == 5.0);
		REQUIRE(line.GetArea() == 0.0);
	}

	SECTION("Drawing calls")
	{
		auto output = GetCanvasOutput([&line](MockCanvas& mock) {
			line.Draw(mock);
		});

		REQUIRE(output.find("DrawLine") != std::string::npos);
		REQUIRE(output.find("(0.0, 0.0)") != std::string::npos);
		REQUIRE(output.find("(3.0, 4.0)") != std::string::npos);
		REQUIRE(output.find("FF00FFFF") != std::string::npos);
	}
}

TEST_CASE("Triangle full functionality")
{
	Triangle triangle({ 0, 0 }, { 3, 0 }, { 0, 4 }, 0xFF0000FF, 0x00FFFFFF);

	SECTION("Geometric properties")
	{
		REQUIRE(triangle.GetVertex1() == Point(0, 0));
		REQUIRE(triangle.GetVertex2() == Point(3, 0));
		REQUIRE(triangle.GetVertex3() == Point(0, 4));
		REQUIRE(triangle.GetArea() == 6.0);
		REQUIRE(triangle.GetPerimeter() == 12.0);
	}

	SECTION("Drawing calls")
	{
		auto output = GetCanvasOutput([&triangle](MockCanvas& mock) {
			triangle.Draw(mock);
		});

		REQUIRE(output.find("FillPolygon") != std::string::npos);
		REQUIRE(output.find("DrawPolygon") != std::string::npos);
		REQUIRE(output.find("(0.0, 0.0)") != std::string::npos);
		REQUIRE(output.find("(3.0, 0.0)") != std::string::npos);
		REQUIRE(output.find("(0.0, 4.0)") != std::string::npos);
		REQUIRE(output.find("FF0000FF") != std::string::npos);
		REQUIRE(output.find("00FFFFFF") != std::string::npos);
	}
}

TEST_CASE("Edge cases with MockCanvas verification")
{
	SECTION("Degenerate rectangle drawing")
	{
		Rectangle rect({ 1, 1 }, { 1, 1 });

		auto output = GetCanvasOutput([&rect](MockCanvas& mock) {
			rect.Draw(mock);
		});

		REQUIRE(output.find("(1.0, 1.0)") != std::string::npos);
		REQUIRE(output.find("width: 0") == std::string::npos);
	}

	SECTION("Zero radius circle drawing")
	{
		Circle circle({ 0, 0 }, 0.0);

		auto output = GetCanvasOutput([&circle](MockCanvas& mock) {
			circle.Draw(mock);
		});

		REQUIRE(output.find("radius 0.0") != std::string::npos);
	}

	SECTION("Triangle with colinear points")
	{
		Triangle triangle({ 0, 0 }, { 2, 0 }, { 1, 0 });

		auto output = GetCanvasOutput([&triangle](MockCanvas& mock) {
			triangle.Draw(mock);
		});

		REQUIRE(output.find("(1.0, 0.0)") != std::string::npos);
		REQUIRE(triangle.GetArea() == 0.0);
	}
}

TEST_CASE("MockCanvas method coverage")
{
	MockCanvas mock;
	SECTION("All methods are called")
	{
		auto output = GetCanvasOutput([](MockCanvas& mock) {
			mock.DrawLine({ 0, 0 }, { 1, 1 }, 0xFF0000FF);
			mock.FillPolygon({ { 0, 0 }, { 1, 0 }, { 1, 1 } }, 0x00FF00FF);
			mock.DrawCircle({ 0, 0 }, 5.0, 0x0000FFFF);
			mock.FillCircle({ 0, 0 }, 5.0, 0xFFFFFFFF);
			mock.DrawPolygon({ { 0, 0 }, { 1, 0 }, { 1, 1 } }, 0xFF00FFFF);
		});

		REQUIRE(output.find("DrawLine") != std::string::npos);
		REQUIRE(output.find("FillPolygon") != std::string::npos);
		REQUIRE(output.find("DrawCircle") != std::string::npos);
		REQUIRE(output.find("FillCircle") != std::string::npos);
		REQUIRE(output.find("DrawPolygon") != std::string::npos);
	}
}
