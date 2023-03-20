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

Vector2f quartic(Vector2f a, Vector2f b, Vector2f c, Vector2f d, Vector2f e, float t)
{
	Vector2f five, six;
	five = cubic(a, b, c, d, t);
	six = cubic(b, c, d, e, t);

	return Vector2f(lerp(five.x, six.x, t), lerp(five.y, six.y, t));
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

		//Quartic Bezier Curve

		Vertex line[60];
		int sizeOfArr = sizeof(line) / sizeof(line[0]);

		Vector2f p0(10.f, 500.f);					//control point (anchor point)
		Vector2f p1(230.f, -500.f);					//control point
		Vector2f p2(600.f, 1700.f);					//control point
		Vector2f p3(900.f, -500.f);					//control point
		Vector2f p4(Mouse::getPosition(window));	//control point (anchor point)


		for (int i = 0; i < sizeOfArr; ++i)
		{
			double t = static_cast<float>(i) / sizeOfArr;
			line[i] = quartic(p0, p1, p2, p3, p4, t);
			line[i].color = Color::Green;
		}

		window.draw(line, sizeOfArr, sf::LineStrip);

		window.display();
	}

	return EXIT_SUCCESS;
}