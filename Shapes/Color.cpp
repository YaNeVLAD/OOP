#include "Color.h"
#include <utility>

const Color Color::Red(255, 0, 0);
const Color Color::Green(0, 255, 0);
const Color Color::Blue(0, 0, 255);
const Color Color::Magenda(255, 0, 255);
const Color Color::Cyan(0, 255, 255);
const Color Color::White(255, 255, 255);
const Color Color::Black(0, 0, 0);
const Color Color::Yellow(255, 255, 0);
const Color Color::Transparent(0, 0, 0, 0);

Color::Color(uint32_t hex)
	: red((hex & 0x000000FF) >> 0)
	, green((hex & 0x0000FF00) >> 8)
	, blue((hex & 0x00FF0000) >> 16)
	, alpha((hex & 0xFF000000) >> 24)
{
}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	: red(r)
	, green(g)
	, blue(b)
	, alpha(a)
{
}

Color Color::operator=(const Color& other)
{
	return Color(other);
}

Color Color::operator=(Color&& other) noexcept
{
	return Color(std::move(other));
}

uint32_t Color::ToInt() const
{
	return (red << 24) | (green << 16) | (blue << 8) | alpha;
}
