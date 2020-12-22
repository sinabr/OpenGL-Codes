#include <windows.h>
#include <iostream>
#include <gl\glut.h>
#include "Lines.h"

using namespace std;

HWND consoleWindow = GetConsoleWindow();
HDC consoleDC = GetDC(consoleWindow);

void drawSquare()
{
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			SetPixel(consoleDC, 20 + i, 20 + j, RGB(i + j, i + 50, j + 100));
}

void Lines::setPixel(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

void Lines::correct_order(int& x0, int& y0, int& x_end, int& y_end)
{
	if (x0 > x_end)
	{
		int xtemp = x0;
		int ytemp = y0;
		x0 = x_end;
		y0 = y_end;
		x_end = xtemp;
		y_end = ytemp;
	}
}

void Lines::DirectScan(int x0, int y0, int x_end, int y_end)
{
	Lines::correct_order(x0, y0, x_end, y_end);

	float m = (float)(y_end - y0) / (x_end - x0);
	float b = y0 - m*x0;
	int x = x0;

	while (x <= x_end)
	{
		int y = round(m*x + b);
		Lines::setPixel(x++, y);
	}
}

void Lines::DDA(int x0, int y0, int x_end, int y_end)
{
	Lines::correct_order(x0, y0, x_end, y_end);

	int dx = x_end - x0;
	int dy = y_end - y0;
	
	float steps = (dx > dy)  ? dx : dy;
	float xi = dx / steps, yi = dy / steps;
	float x = x0, y = y0;

	for (int k = 0; k < steps; k++) {
		Lines::setPixel(x, round(y));
		x += xi;
		y += yi;
	}
}

void Lines::Bresenham(int x0, int y0, int x_end, int y_end)
{
	Lines::correct_order(x0, y0, x_end, y_end);

	int dx = x_end - x0;
	int dy = y_end - y0;

	bool reverse = false;
	if (dy > dx)
	{
		reverse = true;
		int temp = dx; dx = dy; dy = temp;
		temp = x0; x0 = y0; y0 = temp;
		temp = x_end; x_end = y_end; y_end = temp;
	}

	float x = x0;
	float y = y0;

	int p = 2 * dy - dx;

	while (x <= x_end)
	{
		if (!reverse) Lines::setPixel(x++, y);
		else Lines::setPixel(y, x++);

		if (p < 0)
		{
			p += 2 * dy;
		}
		else
		{
			p += 2 * dy - 2 * dx;
			y += 1;
		}
	}
}

void Lines::Parallel(int x0, int y0, int x_end, int y_end)
{
	Lines::correct_order(x0, y0, x_end, y_end);

	auto dx = x_end - x0;
	auto dy = y_end - y0;

	auto ll = sqrt(pow(dx, 2) + pow(dy, 2));
	auto A = -dy / ll;
	auto B = dx / ll;
	auto C = (x0 * dy - y0*dx) / ll;

	for (int x = x0; x < x_end; x++)
	{
		for (int y = y0; y < y_end; y++)
		{
			auto d = A*x + B*y + C;
			if (abs(d) < 2) Lines::setPixel(x, y);
		}
	}
}

void Lines::Polygon(int xs[], int ys[], int pointCounts)
{
	for (int i = 0; i < pointCounts - 1; i++)
		Lines::DDA(xs[i], ys[i], xs[i + 1], ys[i + 1]);

	Lines::DDA(xs[pointCounts - 1], ys[pointCounts - 1], xs[0], ys[0]);
}

void Lines::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	Lines::DirectScan(300, 500, 700, 600);
	glColor3f(0.0, 0.0, 0.0);
	Lines::DDA(300, 400, 700, 500);
	glColor3f(1.0, 0.0, 0.0);
	Lines::Bresenham(300, 300, 700, 400);
	glColor3f(0.0, 1.0, 0.0);
	Lines::Parallel(300, 200, 700, 300);

	glColor3f(0.0, 0.0, 0.0);
	int xs[] = { 500,600,700,600,500,400 };
	int ys[] = { 500,200,400,700,600,500 };
	Lines::Polygon(xs, ys, 6);

	glFlush();
}

void Lines::reshape(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspectRatio = (float)width / height;

	if (width > height) {
		gluOrtho2D(-1.0 * aspectRatio, 1.0 * aspectRatio, -1.0, 1.0);
	}
	else
	{
		gluOrtho2D(-1.0, 1.0, -1.0 / aspectRatio, 1.0 / aspectRatio);
	}

	glViewport(0, 0, width, height);
}

//void Lines::main(int argc, char** argv)
//{
//	//ReleaseDC(consoleWindow, consoleDC);
//	//cin.ignore();
//
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//	glutInitWindowSize(800, 600);
//	glutCreateWindow("Test OpenGL");
//
//	glClearColor(1.0, 1.0, 1.0, 0.0);
//	glMatrixMode(GL_PROJECTION);
//	gluOrtho2D(0.0, 1000, 0.0, 1000);
//
//	glutDisplayFunc(Lines::render);
//	glutReshapeFunc(Lines::reshape);
//
//	glutMainLoop();
//}