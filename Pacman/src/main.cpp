#include "Game.h"
#include <gl/glut.h>

Game game;

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	int time = glutGet(GLUT_ELAPSED_TIME);
	game.Update(time);
	game.Render(time);

	glutSwapBuffers();
}

void init()
{
	int time = glutGet(GLUT_ELAPSED_TIME);

	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	game.Load(time);
}

void keyboard(int key, int x, int y)
{
	int time = glutGet(GLUT_ELAPSED_TIME);

	game.keyboard(time, key, x, y);
}

void keyboard_up(int key, int x, int y)
{
	int time = glutGet(GLUT_ELAPSED_TIME);

	game.keyboard_up(time, key, x, y);
}

void reshape(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspestRatio = (float)width / height;
	if (width > height)
	{
		gluOrtho2D(0, 900 * aspestRatio, 0, 900);
	}
	else
	{
		gluOrtho2D(0, 900, 0, 900 / aspestRatio);
	}

	glViewport(0, 0, width, height);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(900, 900);
	glutCreateWindow("Game");

	glClearColor(0.0, 0.0, 0.0, 0.0);
	init();

	glutDisplayFunc(render);
	glutIdleFunc(render);
	glutReshapeFunc(reshape);
	glutSpecialFunc(keyboard);
	glutSpecialUpFunc(keyboard_up);

	glutMainLoop();
}