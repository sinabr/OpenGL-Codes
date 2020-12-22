#pragma once

namespace Circles
{
	void render();
	void reshape(int width, int height);
	void setPixel(int x, int y);

	void DirectEquation(int cx, int cy, int r);
	void ParametricEquation(int cx, int cy, int r);
	void Bresenham(int cx, int cy, int r);
	void MidPoint(int cx, int cy, int r);

	void main(int argc, char** argv);
};