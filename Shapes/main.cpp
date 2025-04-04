#include <iostream>

#include "Canvas.h"
#include "ShapeParser.h"
#include "Utility.h"

int main()
{
	ShapeParser parser{ std::cin };
	auto shapes = parser.Parse();

	auto& maxAreaShape = FindShapeWithMaxArea(shapes);
	auto& minPerimeterShape = FindShapeWithMinPerimeter(shapes);

	std::cout << "Max Area: " << std::endl;
	PrintShapeInfo(std::cout, maxAreaShape);

	std::cout << "Min Perimeter: " << std::endl;
	PrintShapeInfo(std::cout, minPerimeterShape);

	Canvas canvas{ "Canvas", 1024, 860 };
	canvas.SetBackgroundColor(Color::White);

	while (canvas.IsOpen())
	{
		canvas.PollEvents();

		for (const auto& shape : shapes)
		{
			if (auto* drawable = dynamic_cast<const ICanvasDrawable*>(shape.get()))
			{
				drawable->Draw(canvas);
			}
		}

		canvas.Display();
	}
}
