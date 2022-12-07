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
	// Create the main window
	RenderWindow window(VideoMode(1400, 1000), "Hello world!");

	// Start the game loop
	while (window.isOpen())
	{
		//use the texture on sprites or shapes
		/*Sprite spr(texture);
		window.draw(spr);*/

		// Process events
		Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == Event::Closed)
				window.close();
		}

		//Game update


		window.clear();

		//

		Vertex line[80];
		int sizeOfArr = sizeof(line) / sizeof(line[0]);

		//Linear Bezier Curve

		//Vector2f p0(150.f, 150.f);	//Anchor point
		//Vector2f p1(Mouse::getPosition(window).x, Mouse::getPosition(window).y);	//Anchor point

		//for (int i = 0; i < sizeOfArr; i++)
		//{
		//	double t = static_cast<float>(i) / sizeOfArr;
		//	line[i] = linear(p0,p1,t);
		//}

		//Quadratic Bezier Curve

		//Vector2f p0(150.f, 150.f);	//Anchor point
		//Vector2f p1(600.f, 900.f);	//Control point
		//Vector2f p2(Mouse::getPosition(window).x, Mouse::getPosition(window).y);	//Anchor point

		//for (int i = 0; i < sizeOfArr; ++i)
		//{
		//	double t = static_cast<float>(i) / sizeOfArr;
		//	line[i] = quadratic(p0, p1, p2, t);
		//	
		//}

		//Cubic Bezier Curve

		//Vector2f p0(0.f, 500.f);	//Anchor point
		//Vector2f p1(Mouse::getPosition(window).x, Mouse::getPosition(window).y);	//Control point
		//Vector2f p2(300.f, 1250.f);	//Control point
		//Vector2f p3(1400.f, 500.f);	//Anchor point

		//for (int i = 0; i < sizeOfArr; ++i)
		//{
		//	double t = static_cast<float>(i) / sizeOfArr;
		//	line[i] = cubic(p0,p1,p2,p3,t);
		//}

		//Quartic Bezier Curve

		Vector2f p0(30.f, 500.f);	//Anchor point
		Vector2f p1(230.f, 700.f);	//Control point
		Vector2f p2(600.f, -500.f);	//Control point
		Vector2f p3(800.f, 900.f);	//Control point
		Vector2f p4(Mouse::getPosition(window).x, 500.f);	//Anchor point
		

		for (int i = 0; i < sizeOfArr; ++i)
		{
			double t = static_cast<float>(i) / sizeOfArr;
			line[i] = quartic(p0, p1, p2, p3, p4, t);
		}

		//

		window.draw(line, sizeOfArr, Points);

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
}