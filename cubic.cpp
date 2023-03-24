
// Author: Kacper Feister
// Last update: 24/03/2023
// Project: Cubic Bezier Curve

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

Vector2f cubic(Vector2f a, Vector2f b, Vector2f c, Vector2f d, float t)
{
	Vector2f three, four;
	three = quadratic(a, b, c, t);
	four = quadratic(b, c, d, t);

	return Vector2f(lerp(three.x, four.x, t), lerp(three.y, four.y, t));
}

int main()
{
	RenderWindow window(VideoMode(1400, 700), "Hello Bezier Curves!");

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();

		//Cubic Bezier Curve

		const int offset = 1;
		const int sizeOfArr = 20 + offset;
		Vertex line[sizeOfArr];

		Vector2f p0(10.f, 500.f);					//control point (anchor point)
		Vector2f p1(400, 50);						//control point
		Vector2f p2(600.f, 1250.f);					//control point
		Vector2f p3(Mouse::getPosition(window));	//control point (anchor point)

		for (int i = 0; i < sizeOfArr - offset; ++i)
		{
			double t = (float)i / (float)(sizeOfArr - offset);
			line[i] = cubic(p0, p1, p2, p3, t);
			line[i].color = Color::Red;
		}
		line[sizeOfArr - offset].position = p3;
		line[sizeOfArr - offset].color = Color::Red;

		window.draw(line, sizeOfArr, sf::LineStrip);

		window.display();
	}

	return EXIT_SUCCESS;
}