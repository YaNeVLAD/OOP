#include "Canvas.h"
#include <SFML/Graphics.hpp>

Canvas::Canvas(std::string title, unsigned width, unsigned height)
	: m_window(std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), std::move(title)))
{
}

bool Canvas::IsOpen()
{
	return m_window->isOpen();
}

void Canvas::Display()
{
	m_window->display();
	m_window->clear(sf::Color(m_background));
}

void Canvas::PollEvents()
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window->close();
		}
	}
}

void Canvas::Close()
{
	m_window->close();
}

void Canvas::SetBackgroundColor(Color color)
{
	m_background = color;
}

void Canvas::DrawLine(Point from, Point to, Color lineColor) const
{
	auto& [ax, ay] = from;
	auto& [bx, by] = to;

	sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(static_cast<float>(ax), static_cast<float>(ay)),
			sf::Color(lineColor)),
		sf::Vertex(sf::Vector2f(static_cast<float>(bx), static_cast<float>(by)),
			sf::Color(lineColor))
	};

	m_window->draw(line, std::size(line), sf::Lines);
}

void Canvas::DrawPolygon(const std::vector<Point>& points, Color lineColor) const
{
	DrawPolygonImpl(points, Color::Transparent, lineColor);
}

void Canvas::FillPolygon(const std::vector<Point>& points, Color fillColor) const
{
	DrawPolygonImpl(points, fillColor, Color::Transparent);
}

void Canvas::DrawCircle(Point center, double radius, Color lineColor) const
{
	DrawCicleImpl(center, radius, Color::Transparent, lineColor);
}
void Canvas::FillCircle(Point center, double radius, Color fillColor) const
{
	DrawCicleImpl(center, radius, fillColor, Color::Transparent);
}

void Canvas::DrawPolygonImpl(const std::vector<Point>& points, Color fillColor, Color lineColor) const
{
	sf::ConvexShape polygon;
	polygon.setPointCount(points.size());
	polygon.setFillColor(sf::Color(fillColor));
	polygon.setOutlineThickness(2.f);
	polygon.setOutlineColor(sf::Color(lineColor));
	for (size_t i = 0; i < points.size(); ++i)
	{
		auto& [x, y] = points[i];
		polygon.setPoint(i, sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
	}

	m_window->draw(polygon);
}

void Canvas::DrawCicleImpl(Point center, double radius, Color fillColor, Color lineColor) const
{
	auto& [x, y] = center;

	sf::CircleShape circle(static_cast<float>(radius), 360);
	circle.setPosition(static_cast<float>(x - radius), static_cast<float>(y - radius));
	circle.setFillColor(sf::Color(fillColor));
	circle.setOutlineThickness(2.f);
	circle.setOutlineColor(sf::Color(lineColor));

	m_window->draw(circle);
}
