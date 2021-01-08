#define _CRT_SECURE_NO_WARNINGS

#include "Game.h"
#include "Wall.h"
#include "Point.h"
#include "Ghost.h"
#include <typeinfo>
#include <vector>
#include <iostream>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <soil.h>


#define MAXPOINT 220

using namespace std;

Game::Game() :Component(NULL)
{
	this->game = this;
	this->gameover = false;
	this->win = false;
	srand(122);
}

Game::~Game()
{
}

void Game::Load(int time)
{


	int map[21][21] = 
	{ 
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0},
		{0,1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1,0},
		{0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0},
		{0,1,0,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,0,1,0},
		{0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0},
		{0,1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1,0},
		{0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0},
		{1,1,1,1,1,0,1,0,1,1,0,1,1,0,1,0,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,0,1,0,1,1,0,1,1,0,1,0,1,1,1,1,1},
		{0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0},
		{0,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,0},
		{0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0},
		{0,1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1,0},
		{0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0},
		{0,1,1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,1,0},
		{0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0},
		{0,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,0,1,0},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}
	};

	int bigP[4][2] = 
	{ 
		{2,2},
		{18,2},
		{2,15},
		{18,15}
	};

	int ghosts_[4][2] =
	{
		{7,9},
		{9,11},
		{9,10},
		{9,9}
	};
	
	int pacman[2] = { 15,10 };

	int my = 820;
	int mx = 100;
	mx += 120;

	for (int i = 20; i >= 0; i--)
	{
		for (int j = 0; j < 21; j++)
		{
			if (map[i][j] == 1) {
				Wall* wall = new Wall(this);
				wall->SetPosition(mx, my);
				walls.push_back(wall);
			}
			else {

				if ((bigP[0][0] == j && bigP[0][1] == i) ||
					(bigP[1][0] == j && bigP[1][1] == i) ||
					(bigP[2][0] == j && bigP[2][1] == i) ||
					(bigP[3][0] == j && bigP[3][1] == i) ) 
				{
					Point* point = new Point(this,true);
					point->SetPosition(mx, my);
					points.push_back(point);
				}
				else {
					if (pacman[0] == i && pacman[1] == j)
					{
						this->pacman = new Pacman(this);
						this->pacman->SetPosition(mx, my);
					}
					else {
						if ((ghosts_[0][0] == j && ghosts_[0][1] == i) ||
							(ghosts_[1][0] == j && ghosts_[1][1] == i) ||
							(ghosts_[2][0] == j && ghosts_[2][1] == i) ||
							(ghosts_[3][0] == j && ghosts_[3][1] == i))
						{
							Ghost* gost = new Ghost(this);
							gost->SetPosition(mx, my);
							ghosts.push_back(gost);
						}
						else {
							Point* point = new Point(this,false);
							point->SetPosition(mx, my);
							points.push_back(point);
						}
					}
				}




			}

			mx += 40;
		}
		mx = 100;
		mx += 120;
		my -= 40;
	}

	for (auto iter = walls.begin(); iter != walls.end(); iter++)
		(*iter)->Load(time);
	for (auto iter = points.begin(); iter != points.end(); iter++)
		(*iter)->Load(time);
	for (auto iter = ghosts.begin(); iter != ghosts.end(); iter++)
		(*iter)->Load(time);
	this->pacman->Load(time);
}

void Game::PacmanEat(Point * point) {
	bool fresh = point->Fresh();

	if (fresh == true) {
		std::pair<int, int> ppos = point->GetPosition();
		std::pair<int, int> pacpos = pacman->GetPosition();
		int px = ppos.first + 19; int py = ppos.second + 19;
		int cx = pacpos.first + 19; int cy = pacpos.second + 19;

		int dx = abs(cx - px);
		int dy = abs(cy - py);


		if (dx < 30 && dy < 30) {
			point->Eaten();
			if (point->Big()) {
				this->gains += 9;
			}
			else {
				this->gains += 2;
			}

			if (this->gains >= MAXPOINT) {
				this->win = true;
			}
		}
	}

};

void Game::PacmanWall(Wall* wall) {
	std::pair<float, float> wpos = wall->GetPosition();
	std::pair<float, float> ppos = pacman->GetPosition();
	float wx = wpos.first + 15; float wy = wpos.second + 15;
	float px = ppos.first + 15; float py = ppos.second + 15;

	float dx = abs(wx - px);
	float dy = abs(wy - py);

	Pacman::CharacterDirection dir = pacman->direction;

	if (dx < 38 && dy < 38) {
		if (dx < 20 && py > wy) {
			// Cant Go Down
			if (dir == Pacman::CharacterDirection::Down) {
				pacman->SetBlock(true);
			}
		}
		if (dx < 20 && py < wy) {
			// Cant Go Up
			if (dir == Pacman::CharacterDirection::Up) {
				pacman->SetBlock(true);
			}
		}
		if (dy < 20 && px < wx) {
			// Cant Go Right
			if (dir == Pacman::CharacterDirection::Right) {
				pacman->SetBlock(true);
			}
		}
		if (dy < 20 && px > wx) {
			// Cant Go Left
			if (dir == Pacman::CharacterDirection::Left) {
				pacman->SetBlock(true);
			}
		}
	}

};

void Game::GhostWall(Ghost* ghost,Wall* wall)
{

	std::pair<float, float> wpos = wall->GetPosition();
	std::pair<float, float> ppos = ghost->GetPosition();
	int wx = wpos.first + 19; int wy = wpos.second + 19;
	int px = ppos.first + 19; int py = ppos.second + 19;

	int dx = abs(wx - px);
	int dy = abs(wy - py);

	int a = -1;

	Ghost::GhostDirection dir = ghost->direction;

	if (dx < 38 && dy < 38) {
		if (dx < 20 && py > wy) {
			// Cant Go Down
			if (dir == Ghost::GhostDirection::Down) {
				while (a == -1 || a == Ghost::GhostDirection::Down) {
					a = rand() % 4;
				}
				ghost->SetBlock(true);
				ghost->SetDirection(a);
			}
		}
		if (dx < 20 && py < wy) {
			// Cant Go Up
			if (dir == Ghost::GhostDirection::Up) {
				while (a == -1 || a == Ghost::GhostDirection::Up) {
					a = rand() % 4;
				}
				ghost->SetBlock(true);
				ghost->SetDirection(a);
			}
		}
		if (dy < 20 && px < wx) {
			// Cant Go Right
			if (dir == Ghost::GhostDirection::Right) {
				while (a == -1 || a == Ghost::GhostDirection::Right) {
					a = rand() % 4;
				}
				ghost->SetBlock(true);
				ghost->SetDirection(a);
			}
		}
		if (dy < 20 && px > wx) {
			// Cant Go Left
			if (dir == Ghost::GhostDirection::Left) {
				while (a == -1 || a == Ghost::GhostDirection::Left) {
					a = rand() % 4;
				}
				ghost->SetBlock(true);
				ghost->SetDirection(a);
			}
		}
	}

}

void Game::PacmanGhost(Ghost* ghost)
{
	std::pair<int, int> ppos = ghost->GetPosition();
	std::pair<int, int> pacpos = pacman->GetPosition();
	int px = ppos.first + 19; int py = ppos.second + 19;
	int cx = pacpos.first + 19; int cy = pacpos.second + 19;

	int dx = abs(cx - px);
	int dy = abs(cy - py);


	if (dx < 38 && dy < 38) {
		this->gameover = true;
	}
}

void Game::GameOver()
{

	glPushMatrix();
	glTranslatef(200, 200, 0);

	const char* text = "Game Over";
	glRasterPos2d(700, 500);
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(100, 300, 0);
	glScalef(0.5,0.5,0.5);
	for (int i = 0; i < strlen(text); i++) {
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, text[i]);
	}

	glDisable(GL_BLEND);
	glPopMatrix();

}

void Game::GameWin()
{

	glPushMatrix();
	glTranslatef(200, 200, 0);

	const char* text = "You Won!";
	glRasterPos2d(700, 500);
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(100, 300, 0);
	glScalef(0.5, 0.5, 0.5);
	for (int i = 0; i < strlen(text); i++) {
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, text[i]);
	}

	glDisable(GL_BLEND);
	glPopMatrix();

}

void Game::Update(int time)
{
	for (auto iter = ghosts.begin(); iter != ghosts.end(); iter++)
	{
		this->PacmanGhost(*iter);
		for (auto iter2 = walls.begin(); iter2 != walls.end(); iter2++)
		{
			this->GhostWall(*iter, *iter2);
		}
	}
	for (auto iter = walls.begin(); iter != walls.end(); iter++)
		this->PacmanWall(*iter);
	for (auto iter = points.begin(); iter != points.end(); iter++)
		this->PacmanEat(*iter);

	for (auto iter = walls.begin(); iter != walls.end(); iter++)
		(*iter)->Update(time);
	for (auto iter = points.begin(); iter != points.end(); iter++)
		(*iter)->Update(time);
	for (auto iter = ghosts.begin(); iter != ghosts.end(); iter++)
		(*iter)->Update(time);
	this->pacman->Update(time);
}


void Game::Render(int time)
{
	
	glPushMatrix();
	
	glRasterPos2i(10.0,400.0);
	glTranslatef(10,400,0);

	glDisable(GL_TEXTURE_2D);

	glColor3f(1.0, 0.0, 0.0);
	const std::string& string = "Points : ";
	int a = this->gains;
	char str[12];
	sprintf(str, "%d", a);

	for (int n = 0; n < string.size(); ++n) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[n]);
		cout << string[n] << endl;
	}
	for (int n = 0; n < strlen(str); ++n) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[n]);
		cout << str[n] << endl;
	}

	glEnable(GL_TEXTURE_2D);

	glPopMatrix();


	glPushMatrix();

	glRasterPos2i(10.0, 450.0);
	glTranslatef(10, 450, 0);

	glDisable(GL_TEXTURE_2D);

	glColor3f(1.0, 0.0, 0.0);
	const std::string& string2 = "Max Point : ";
	int a2 = MAXPOINT;
	char str2[12];
	sprintf(str2, "%d", a2);

	for (int n = 0; n < string2.size(); ++n) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string2[n]);
		cout << string2[n] << endl;
	}
	for (int n = 0; n < strlen(str2); ++n) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str2[n]);
		cout << str2[n] << endl;
	}

	glEnable(GL_TEXTURE_2D);

	glPopMatrix();

	
	if(this->gains > MAXPOINT)
	{
		this->GameWin();
	}
	else if (this->gameover) {

		this->GameOver();
	}
	else {
		for (auto iter = walls.begin(); iter != walls.end(); iter++)
			(*iter)->Render(time);
		for (auto iter = points.begin(); iter != points.end(); iter++)
			(*iter)->Render(time);
		for (auto iter = ghosts.begin(); iter != ghosts.end(); iter++)
			(*iter)->Render(time);
		this->pacman->Render(time);
	}


}

void Game::keyboard(int time, int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		this->pacman->up(time);
		break;
	case GLUT_KEY_DOWN:
		this->pacman->down(time);
		break;
	case GLUT_KEY_LEFT:
		this->pacman->left(time);
		break;
	case GLUT_KEY_RIGHT:
		this->pacman->right(time);
		break;
	}
}

void Game::keyboard_up(int time, int key, int x, int y)
{
	this->pacman->stop(time);
}
