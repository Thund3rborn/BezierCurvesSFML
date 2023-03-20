
// Author: Kacper Feister
// Last update: 20/03/2023
// Project: Quadratic Bezier Curve

#include "SFML/Graphics.hpp"
#include <iostream>
#include <assert.h>
#include <math.h>

using namespace sf;

float lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}

Vector2f quadratic(Vector2f a, Vector2f b, Vector2f c, float t)
{
	Vector2f one, two;
	one.x = lerp(a.x, b.x, t);
	one.y = lerp(a.y, b.y, t);
	two.x = lerp(b.x, c.x, t);
	two.y = lerp(b.y, c.y, t);

	return Vector2f(lerp(one.x, two.x, t), lerp(one.y, two.y, t));
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

		//Quadratic Bezier Curve

		const int offset = 1;
		const int sizeOfArr = 20 + offset;
		Vertex line[sizeOfArr];

		Vector2f p0(150.f, 150.f);							//control point (anchor point)
		Vector2f p1(600.f, 900.f);							//control point
		Vector2f p2(Mouse::getPosition(window));			//control point (anchor point)

		for (int i = 0; i < sizeOfArr - offset; ++i)
		{
			double t = (float)i / (float)(sizeOfArr - offset);
			line[i] = quadratic(p0, p1, p2, t);
			line[i].color = Color::Cyan;
		}
		line[sizeOfArr - offset].position = p2;
		line[sizeOfArr - offset].color = Color::Cyan;

		window.draw(line, sizeOfArr, sf::LineStrip);

		window.display();
	}

	return EXIT_SUCCESS;
}