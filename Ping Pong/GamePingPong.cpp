#include <iostream>
#include <gl\glut.h>
#include "GamePingPong.h"

#define RACQUET 1000
#define BALL 1001
#define FIELD 1002
#define BLOCK 1003

using namespace std;

PingPong::GameState game(1000, 500);

void PingPong::GameState::init()
{
	this->Player_1.Position = (this->FieldWidth - this->RaquetWidth) / 2;

	this->Ball.Position_X = this->FieldWidth / 2;
	this->Ball.Position_Y = this->FieldHeight / 2;

	auto theta = ((double)rand() / (RAND_MAX)) * 360;
	this->Ball.Velocity_X = cos(theta);
	this->Ball.Velocity_Y = sin(theta);


	int posx = 0;
	int posy = game.FieldHeight - game.Nheight;
	for (int i = 0; i < game.Nrow; i++)
	{
		for (int j = 0; j < game.Ncolumn; j++)
		{
			game.rectangles.push_back({ 1,posx,posy });
			posx += game.Nwidth;
			cout << posx << endl;
			cout << posy << endl << endl;
		}
		posx = 0;
		posy -= game.Nheight;
	}
}

void PingPong::GameState::change_state(int player, int state)
{
	auto H = glutGet(GLUT_WINDOW_HEIGHT);


	this->Player_1.Position =
	fmax(fmin(state , this->FieldWidth - this->RaquetWidth), 0);
	

	glutPostRedisplay();
}

bool Collision(int x0, int y0, int w0, int h0, int x1, int y1, int w1, int h1)
{
	auto l = fmax(x0, x1);
	auto t = fmin(y0, y1);

	auto r0 = x0 + w0, r1 = x1 + w1;
	auto b0 = y0 - h0, b1 = y1 - h1;

	auto b = fmax(b0, b1);
	auto r = fmin(r0, r1);

	return l <= r && t >= b;
}

void PingPong::GameState::next_state()
{
	Ball.Position_X += Ball.Velocity_X * 10;
	Ball.Position_Y += Ball.Velocity_Y * 10;
	
	if (Ball.Position_X <= 0)
	{
		Ball.Position_X = 0;
		Ball.Velocity_X *= -1;
	}
	else if (Ball.Position_X >= this->FieldWidth)
	{
		Ball.Position_X = this->FieldWidth;
		Ball.Velocity_X *= -1;
	}


	// This must be a loop here for Rectangles
	for (int i = 0; i < game.Nrow * game.Ncolumn; i++)
	{
		
		int x = game.rectangles[i].positionx;
		int y = game.rectangles[i].positiony;


		int x1 = x + game.Nwidth;
		int y1 = y + game.Nheight;

		if (game.rectangles[i].visible == 1) {


			if (Ball.Position_X <= x && Ball.Position_Y <= y1 && Ball.Position_Y >= y) 
			{
				if (Collision(x, y, game.Nwidth, game.Nheight,
					Ball.Position_X - BallSize / 2, Ball.Position_Y - BallSize / 2, BallSize, BallSize))
				{
					game.rectangles[i].visible = 0;
					Ball.Velocity_X *= -1;
				}
			}
			else if (Ball.Position_X >= x1 && Ball.Position_Y <= y1 && Ball.Position_Y >= y)
			{
				if (Collision(x, y, game.Nwidth, game.Nheight,
					Ball.Position_X - BallSize / 2, Ball.Position_Y - BallSize / 2, BallSize, BallSize))
				{
					game.rectangles[i].visible = 0;
					Ball.Velocity_X *= -1;
				}
			}
			else if (Ball.Position_Y >= y1 && Ball.Position_X <= x1 && Ball.Position_X >= x)
			{
				if (Collision(x, y, game.Nwidth, game.Nheight,
					Ball.Position_X - BallSize / 2, Ball.Position_Y - BallSize / 2, BallSize, BallSize))
				{
					game.rectangles[i].visible = 0;
					Ball.Velocity_Y *= -1;
				}
			}
			else if (Ball.Position_Y <= y && Ball.Position_X <= x1 && Ball.Position_X >= x)
			{
				if (Collision(x, y, game.Nwidth, game.Nheight,
					Ball.Position_X - BallSize / 2, Ball.Position_Y - BallSize / 2, BallSize, BallSize))
				{
					game.rectangles[i].visible = 0;
					Ball.Velocity_Y *= -1;
				}
			}

			
		}

	}
	

	if (Collision(Player_1.Position, RaquetMargin, RaquetWidth, RaquetHeight,
		Ball.Position_X - BallSize / 2, Ball.Position_Y - BallSize / 2, BallSize, BallSize))
	{
		Ball.Position_Y = RaquetMargin + RaquetHeight + BallSize;
		Ball.Velocity_Y *= -1;
	}


	if (Ball.Position_Y < -BallSize * 2 )
	{
		init();
	}
	if (Ball.Position_Y > FieldHeight + BallSize * 2) {
		Ball.Position_Y = FieldHeight + BallSize;
		Ball.Velocity_Y *= -1;
	}

	glutPostRedisplay();
	glutTimerFunc(20, PingPong::timer, 0);
}


void PingPong::mouse(int button, int state, int x, int y)
{
	//cout << x << " , " << y << endl;
}

void PingPong::motion(int x, int y)
{
	game.change_state(1, x);
}

void PingPong::timer(int value)
{
	game.next_state();
}

void PingPong::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glCallList(FIELD);

	glPushMatrix();
	glTranslatef(game.Player_1.Position, game.RaquetMargin, 0);
	glCallList(RACQUET);
	glPopMatrix();

	//cout << game.Player_1.Position << endl;

	glPushMatrix();
	glTranslatef(game.Ball.Position_X, game.Ball.Position_Y, 0);
	glCallList(BALL);
	glPopMatrix();

	for (int i = 0; i < game.Nrow*game.Ncolumn; i++)
	{
		if (game.rectangles[i].visible == 1)
		{
			glPushMatrix();
			int x = game.rectangles[i].positionx;
			int y = game.rectangles[i].positiony;
			glTranslatef(x, y, 0);
			glCallList(BLOCK);
			glPopMatrix();
		}
	}

		//glPushMatrix();
		//glTranslatef(200,200, 0);
		//glCallList(BLOCK);
		//glPopMatrix();

	glutSwapBuffers();
}

void PingPong::init()
{
	game.init();

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1000, 0, 1000);

	glNewList(FIELD, GL_COMPILE);
	Lines::Bresenham(0, 0, game.FieldWidth, 0);
	Lines::Bresenham(game.FieldWidth - 1, 0, game.FieldWidth - 1, game.FieldHeight);
	Lines::Bresenham(0, game.FieldHeight - 1, game.FieldWidth, game.FieldHeight - 1);
	Lines::Bresenham(0, 0, 0, game.FieldHeight);
	glEndList();

	glNewList(BLOCK, GL_COMPILE);
	Lines::Bresenham(0, 0, 0, game.Nheight);
	Lines::Bresenham(0, game.Nheight, game.Nwidth,game.Nheight);
	Lines::Bresenham(0,0,game.Nwidth,0);
	Lines::Bresenham(game.Nwidth, 0,game.Nwidth,game.Nheight);
	glEndList();

	glNewList(RACQUET, GL_COMPILE);
	Lines::Bresenham(0, 0, game.RaquetWidth, 0);
	Lines::Bresenham(game.RaquetWidth, 0, game.RaquetWidth, game.RaquetHeight);
	Lines::Bresenham(game.RaquetWidth, game.RaquetHeight, 0, game.RaquetHeight);
	Lines::Bresenham(0, 0, 0, game.RaquetHeight);
	glEndList();

	glNewList(BALL, GL_COMPILE);
	Circles::ParametricEquation(game.BallSize / 2, game.BallSize / 2, game.BallSize);
	glEndList();
}

void PingPong::reshape(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	auto aspectRatio = (float)game.FieldWidth / game.FieldHeight;
	gluOrtho2D(0, game.FieldWidth, -game.FieldWidth / aspectRatio / 2 + game.FieldHeight / 2, game.FieldWidth / aspectRatio / 2 + game.FieldHeight / 2);

	glViewport(5, 5, width - 10, height - 10);
}

void PingPong::main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(1000,1000);
	glutCreateWindow("Ping Pong");
	//glutFullScreen();

	PingPong::init();

	glutDisplayFunc(PingPong::render);
	glutReshapeFunc(PingPong::reshape);
	glutMouseFunc(PingPong::mouse);
	glutPassiveMotionFunc(PingPong::motion);
	glutTimerFunc(20, PingPong::timer, 0);

	glutMainLoop();
}