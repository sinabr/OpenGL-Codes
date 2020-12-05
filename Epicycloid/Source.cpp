#include <iostream>
#include <gl\glut.h>

#define M_PI 3.14156

using namespace std;

int r_big;
int r_small;
int a;
int b;

void setPixel(int x, int y)
{
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}


void Bresenham(int cx, int cy, int r)
{
	int x = 0;
	int y = r;

	float D = 3 - 2 * r;
	while (x <= y)
	{
		setPixel(cx + x, cy + y);
		setPixel(cx - x, cy + y);

		setPixel(cx + x, cy - y);
		setPixel(cx - x, cy - y);

		setPixel(cx + y, cy + x);
		setPixel(cx + y, cy - x);

		setPixel(cx - y, cy + x);
		setPixel(cx - y, cy - x);

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

void Epicycloid(){

	
	float step = 1.0 / 2;

	for (float v = 0;v <= 360;v+=step) {

		float ang = v / 180.0 * M_PI;

		glPushMatrix();
		//cout << ang << endl;
		glTranslatef(b + r_big + r_small , b, 0);
		
		glRotatef(v, 0, 0, 1);

		glTranslatef(-r_big-r_small , 0, 0);

		//float modelview2[16];
		//glGetFloatv(GL_MODELVIEW_MATRIX, modelview2);

		//if (v < 4) {
		//	for (int i = 0; i < 16; i++)
		//	{
		//		cout << modelview2[i];
		//	}

		//	cout << endl;
		//}
		


		glRotatef(v, 0, 0, 1);



		glCallList(1001);

		glPopMatrix();


		glPushMatrix();
		//cout << ang << endl;
		glTranslatef(b + r_big + r_small,b, 0);

		glRotatef(v, 0, 0, 1);

		glCallList(1002);
		glPopMatrix();

	}




	return;
}


void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glPushMatrix();
	glTranslatef(b, b, 0);
	glCallList(1000);
	glPopMatrix();

	Epicycloid();

	//Bresenham(500, 500, 20);
	//Bresenham(530, 500, 10);


	glutSwapBuffers();
}

void init()
{

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1000, 0, 1000);

	glNewList(1000, GL_COMPILE);
	Bresenham(0,0,r_big);
	glEndList();

	glNewList(1001, GL_COMPILE);
	setPixel(r_small,0);
	glEndList();


	glNewList(1002, GL_COMPILE);
	//Bresenham();
	setPixel(r_big, 0);
	glEndList();
}

void reshape(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	auto aspectRatio = (float)width / height;
	gluOrtho2D(0, width, -width / aspectRatio / 2 + height / 2, width / aspectRatio / 2 + height / 2);

	glViewport(5, 5, width - 10, height - 10);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(1000,1000);
	glutCreateWindow("Epicycloid");

	r_big = 40;
	r_small = 40;
	a = 250;
	b = 500;

	init();

	glutDisplayFunc(render);
	glutReshapeFunc(reshape);


	glutMainLoop();
}