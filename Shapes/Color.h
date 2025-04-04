#pragma once

#include <cstdint>

struct Color
{
	Color();
	Color(Color&& other) = default;
	Color(const Color& other) noexcept = default;

	Color(uint32_t hex);

	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

	Color& operator=(const Color& other) = default;
	Color& operator=(Color&& other) noexcept = default;

	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color Cyan;
	static const Color Magenda;
	static const Color White;
	static const Color Black;
	static const Color Yellow;
	static const Color Transparent;

	uint32_t ToInt() const;

	operator uint32_t()
	{
		return ToInt();
	}

	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};
