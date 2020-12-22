#include <windows.h>
#include <iostream>
#include <GL/glut.h>
#include <chrono>
#include "Circles.h"

#define M_PI 3.14159265358979323846

using namespace std;

void Circles::setPixel(int x, int y)
{
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

void Circles::DirectEquation(int cx, int cy, int r)
{
	for (int i = -r; i <= r; i++)
	{
		int x = cx + i;
		int y = sqrt(pow(r, 2) - pow(x - cx, 2));
		Circles::setPixel(x, cy + y);
		Circles::setPixel(x, cy - y);
	}
}

void Circles::ParametricEquation(int cx, int cy, int r)
{
	float step = 1.0 / 2;
	for (float t = 0; t < 360; t += step)
	{
		float rad = t / 180 * M_PI;

		int x = cx + r * cos(rad);
		int y = cy + r * sin(rad);

		Circles::setPixel(x, y);
	}
}

void Circles::MidPoint(int cx, int cy, int r)
{
	int x = 0;
	int y = r;

	float P = 5 / 4 - r;
	while (x <= y)
	{
		Circles::setPixel(cx + x, cy + y);
		Circles::setPixel(cx - x, cy + y);
		Circles::setPixel(cx + x, cy - y);
		Circles::setPixel(cx - x, cy - y);
		Circles::setPixel(cy + y, cx + x);
		Circles::setPixel(cy + y, cx - x);
		Circles::setPixel(cy - y, cx + x);
		Circles::setPixel(cy - y, cx - x);

		if (P < 0) 
		{
			P += 2 * (x + 1) + 1;
		}
		else
		{
			P += 2 * (x + 1) - 2 * (y - 1) + 1;
			y--;
		}

		x++;
	}
}

void Circles::Bresenham(int cx, int cy, int r)
{
	int x = 0;
	int y = r;

	float D = 3 - 2 * r;
	while (x <= y)
	{
		Circles::setPixel(cx + x, cy + y);
		Circles::setPixel(cx - x, cy + y);
		Circles::setPixel(cx + x, cy - y);
		Circles::setPixel(cx - x, cy - y);
		Circles::setPixel(cy + y, cx + x);
		Circles::setPixel(cy + y, cx - x);
		Circles::setPixel(cy - y, cx + x);
		Circles::setPixel(cy - y, cx - x);

		if (D < 0)
		{
			D += 4 * x + 6;
		}
		else
		{
			D += 4 * (x - y) + 10;
			y--;
		}

		x++;
	}
}

void Circles::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	Circles::Bresenham(500, 500, 200);
	glFlush();
}

void test()
{
	auto start = std::chrono::system_clock::now();
	for (int i = 0; i < 10000; i++)
		Circles::MidPoint(500, 500, 200);
	auto end = std::chrono::system_clock::now();

	auto midpoint_elapsed_time = end - start;
	cout << "midpoint = " << midpoint_elapsed_time.count() << endl;

	start = std::chrono::system_clock::now();
	for (int i = 0; i < 10000; i++)
		Circles::DirectEquation(500, 500, 200);
	end = std::chrono::system_clock::now();

	auto direct_elapsed_time = end - start;
	cout << "direct = " << direct_elapsed_time.count() << endl;

	start = std::chrono::system_clock::now();
	for (int i = 0; i < 10000; i++)
		Circles::Bresenham(500, 500, 200);
	end = std::chrono::system_clock::now();

	auto bresenham_elapsed_time = end - start;
	cout << "bresenham = " << bresenham_elapsed_time.count() << endl;

	start = std::chrono::system_clock::now();
	for (int i = 0; i < 10000; i++)
		Circles::ParametricEquation(500, 500, 200);
	end = std::chrono::system_clock::now();

	auto parametric_elapsed_time = end - start;
	cout << "parametric = " << parametric_elapsed_time.count() << endl;
}

void Circles::reshape(int width, int height)
{
	//test();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspectRatio = (float)width / height;

	if (width > height)
		gluOrtho2D(0, 1000.0 * aspectRatio, 0, 1000);
	else
		gluOrtho2D(0, 1000.0, 0, 1000.0 / aspectRatio);

	glViewport(0, 0, width, height);
}

//void Circles::main(int argc, char** argv)
//{
//	glutinit(&argc, argv);
//	glutinitdisplaymode(glut_single | glut_rgb);
//
//	glutinitwindowsize(800, 600);
//	glutcreatewindow("test opengl");
//
//	glclearcolor(1.0, 1.0, 1.0, 0.0);
//	glmatrixmode(gl_projection);
//	gluortho2d(0, 1000.0, 0, 1000);
//
//	glutdisplayfunc(circles::render);
//	glutreshapefunc(circles::reshape);
//	glutmainloop();
//}