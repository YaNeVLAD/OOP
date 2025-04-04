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
	m_window->clear();
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

void Canvas::FillPolygon(const std::vector<Point>& points, Color fillColor) const
{
	sf::ConvexShape polygon;
	polygon.setPointCount(points.size());
	polygon.setFillColor(sf::Color(fillColor));

	for (size_t i = 0; i < points.size(); ++i)
	{
		auto& [x, y] = points[i];
		polygon.setPoint(i, sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
	}

	m_window->draw(polygon);
}

void Canvas::DrawCircle(Point center, double radius, Color lineColor) const
{
	auto& [x, y] = center;

	sf::CircleShape circle(static_cast<float>(radius), 360);
	circle.setPosition(static_cast<float>(x - radius), static_cast<float>(y - radius));
	circle.setOutlineThickness(2.f);
	circle.setOutlineColor(sf::Color(lineColor));
	circle.setFillColor(sf::Color::Transparent);

	m_window->draw(circle);
}

void Canvas::FillCircle(Point center, double radius, Color fillColor) const
{
	auto& [x, y] = center;

	sf::CircleShape circle(static_cast<float>(radius), 360);
	circle.setPosition(static_cast<float>(x - radius), static_cast<float>(y - radius));
	circle.setFillColor(sf::Color(fillColor));

	m_window->draw(circle);
}
