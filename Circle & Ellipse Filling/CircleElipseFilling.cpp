#include <iostream>
#include <gl\glut.h>
#include <vector>

#define CIRCLE 1000
#define ELLIPSE 1001
#define HLINE 1002


int r = 100;

int rxe = 50;
int rye = 40;

using namespace std;


void setPixel(int x, int y) 
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

// OUR LINES ARE ALL HORIZOTAL 
void HorizontalLine(int y, int x1, int x2)
{
	int def = x1 - x2;
	for (int i = 1; i < def; i++)
	{
		setPixel(x2 + i, y);
	}
}



vector<vector<int>> BresenhamCircle(int cx, int cy, int r)
{
	vector<vector<int>> points;

		int x = 0;
		int y = r;

		float D = 3 - 2 * r;
		while (x <= y)
		{
			if (x >= 0) {
				vector<int> a;
				a.push_back(x);
				a.push_back(y);
				points.push_back(a);

			}

			setPixel(cx + x, cy + y);
			setPixel(cx - x, cy + y);
			setPixel(cx + x, cy - y);
			setPixel(cx - x, cy - y);
			setPixel(cy + y, cx + x);
			setPixel(cy + y, cx - x);
			setPixel(cy - y, cx + x);
			setPixel(cy - y, cx - x);

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
	

	return points;
}

vector<vector<int>> BresenhamEllipse(int rx,int ry, int cx, int cy) {
	int x = 0;
	int y = ry;

	vector<vector<int>> points;

	float p = ry * ry - rx * rx * ry + float(rx * rx / 4);

	while (ry * ry * x < rx * rx * y) 
	{

			vector<int> a;
			a.push_back(x);
			a.push_back(y);
			points.push_back(a);

		

		setPixel(cx + x, cy + y);
		setPixel(cx - x, cy + y);
		setPixel(cx + x, cy - y);
		setPixel(cx - x, cy - y);


		x++;
		if (p < 0) {
			p += 2 * ry * ry * x + ry * ry;
		}
		else {
			y--;
			p += 2 * ry * ry * x + ry * ry + rx * rx * y;
		}

	}
	while (y > 0)
	{
			vector<int> a;
			a.push_back(x);
			a.push_back(y);
			points.push_back(a);

		

		setPixel(cx + x, cy + y);
		setPixel(cx - x, cy + y);
		setPixel(cx + x, cy - y);
		setPixel(cx - x, cy - y);

		y--;
		if (p < 0) {
			p += 2 * rx * rx * y + rx * rx;
		}
		else {
			x++;
			p += 2 * rx * rx * y + rx * rx + ry * ry * x;
		}

	}


	return points;
}


vector<vector<int>> MidPointEllipse(int cx, int cy, int rx, int ry)
{
	int x = 0;
	int y = ry;

	vector<vector<int>> points;

	float P = ry * ry - rx * rx * ry + rx * rx / 4;
	while (ry * ry * x < rx * rx * y)
	{

		vector<int> a;
		a.push_back(x);
		a.push_back(y);
		points.push_back(a);

		setPixel(cx + x, cy + y);
		setPixel(cx - x, cy + y);
		setPixel(cx + x, cy - y);
		setPixel(cx - x, cy - y);

		x++;
		if (P < 0)
		{
			P += 2 * ry * ry * x + ry * ry;
		}
		else
		{
			y--;
			P += 2 * ry * ry * x + ry * ry - 2 * rx * rx * y;
		}
	}

	while (y > 0)
	{

		vector<int> a;
		a.push_back(x);
		a.push_back(y);
		points.push_back(a);

		setPixel(cx + x, cy + y);
		setPixel(cx - x, cy + y);
		setPixel(cx + x, cy - y);
		setPixel(cx - x, cy - y);



		y--;
		if (P < 0)
		{
			P += 2 * rx * rx * y + rx * rx;
		}
		else
		{
			x++;
			P += 2 * rx * rx * y + rx * rx - 2 * ry * ry * x;
		}
	}

	return points;
}


void init()
{
	glNewList(CIRCLE, GL_COMPILE);
	r = 130;
	vector<vector<int>> a = BresenhamCircle(0,0,r);
	for (int i = 0;i < (int)a.size();i++) {
		HorizontalLine(+a[i][1], a[i][0], -a[i][0]);
		HorizontalLine(-a[i][1], a[i][0], -a[i][0]);
		HorizontalLine(a[i][0], a[i][1], -a[i][1]);
		HorizontalLine(-a[i][0], a[i][1], -a[i][1]);

	}
	glEndList();

	glNewList(ELLIPSE, GL_COMPILE);
	rxe = 90;
	rye = 120;
	vector<vector<int>> b = MidPointEllipse(0,0,rxe,rye);
	for (int i = 0;i < b.size();i++) {
		HorizontalLine(  b[i][1],  b[i][0],  - b[i][0]);
		HorizontalLine( - b[i][1],  b[i][0],  - b[i][0]);
	}
	HorizontalLine(0,  rxe,  - rxe);
	glEndList();
}



void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(250,250,0);
	glCallList(CIRCLE);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(500, 500, 0);
	glCallList(ELLIPSE);
	glPopMatrix();

	glFlush();
}


void reshape(int width, int height)
{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
	
		float aspestRatio = (float)width / height;
		if (width > height)
		{
			gluOrtho2D(0, 800 * aspestRatio, 0, 800);
		}
		else
		{
			gluOrtho2D(0, 800, 0, 800 / aspestRatio);
		}
	
		glViewport(0, 0, width, height);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);

	glutInitWindowSize(800, 800);
	glutCreateWindow("Assignment-4");
	//glutFullScreen();

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 800, 0, 800);

	init();

	glutDisplayFunc(render);
	glutReshapeFunc(reshape);


	glutMainLoop();
}