#pragma once
#include "ICanvas.h"

#include <memory>
#include <string>

namespace sf
{
class RenderWindow;
}

class Canvas : public ICanvas
{
public:
	Canvas(std::string title, unsigned width, unsigned height);

	bool IsOpen();

	void Display();
	void PollEvents();
	void Close();

	void SetBackgroundColor(Color color);

	void DrawLine(Point from, Point to, Color lineColor) const override;
	void DrawPolygon(const std::vector<Point>& points, Color lineColor) const override;
	void FillPolygon(const std::vector<Point>& points, Color fillColor) const override;
	void DrawCircle(Point center, double radius, Color lineColor) const override;
	void FillCircle(Point center, double radius, Color fillColor) const override;

private:
	void DrawPolygonImpl(const std::vector<Point>& points, Color fillColor, Color lineColor) const;
	void DrawCicleImpl(Point center, double radius, Color fillColor, Color lineColor) const;

	Color m_background = Color::Black;

	std::shared_ptr<sf::RenderWindow> m_window;
};
