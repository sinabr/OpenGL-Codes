#pragma once

namespace Lines
{
	void setPixel(int x, int y);
	void correct_order(int& x0, int& y0, int& x_end, int& y_end);
	void render();
	void reshape(int width, int height);
	void main(int argc, char** argv);

	void DirectScan(int x0, int y0, int x_end, int y_end);
	void DDA(int x0, int y0, int x_end, int y_end);
	void Bresenham(int x0, int y0, int x_end, int y_end);
	void Parallel(int x0, int y0, int x_end, int y_end);
	void Polygon(int xs[], int ys[], int pointCounts);
}