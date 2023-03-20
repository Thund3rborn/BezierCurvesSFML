
// Author: Kacper Feister
// Last update: 20/03/2023
// Project: Linear Bezier Curve

#include "SFML/Graphics.hpp"
#include <iostream>
#include <assert.h>
#include <math.h>

using namespace sf;

float lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}

Vector2f linear(Vector2f a, Vector2f b, float t)
{
	return Vector2f(lerp(a.x, b.x, t),lerp(a.y, b.y, t));
}

int main()
{
	RenderWindow window(VideoMode(1400, 1000), "Hello world!");

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();

		//Linear Bezier Curve

		const int offset = 1;
		const int sizeOfArr = 20 + offset;
		Vertex line[sizeOfArr];

		Vector2f p0(150.f, 150.f);					//control point (anchor point)
		Vector2f p1(Mouse::getPosition(window));	//control point (anchor point)

		for (int i = 0; i < sizeOfArr - offset; ++i)
		{
			double t = (float)i / (float)(sizeOfArr - offset);
			line[i] = linear(p0, p1, t);
			line[i].color = Color::Cyan;
		}
		line[sizeOfArr - offset].position = p1;
		line[sizeOfArr - offset].color = Color::Cyan;

		window.draw(line, sizeOfArr, sf::LineStrip);

		window.display();
	}

	return EXIT_SUCCESS;
}