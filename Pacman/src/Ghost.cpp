#include "Ghost.h"
#include <soil.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <iostream>

using namespace std;

Ghost::Ghost(Component* parent) : Component(parent)
{
	init_frame = ((double)rand() / (RAND_MAX)) * 64;
	this->type = ghost;
	this->move_cycle = 0;
	//this->direction = GhostDirection(rand()%4);

	srand(time(NULL));
	this->blocked = false;
}

void Ghost::Load(int time)
{
	Component::Load(time);

	texture_id = SOIL_load_OGL_texture("blue_g.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

}

void Ghost::Update(int time)
{

	this->frame = (time - this->start_move_time) / 50;

	int dx = 0;
	int dy = 0;

	int difx = ((int)this->x -20) % 40;
	int dify = ((int)this->y -20)% 40;

	if (difx < 20)
		dx = -difx;
	else
		dx = 40 - difx;

	if (dify < 20)
		dy = -dify;
	else
		dy = 40 - dify;

	if (this->blocked == false) {
		
		switch (this->direction)
		{
		case GhostDirection::Up:
			this->y += 0.5;
			this->x += dx;
			break;
		case GhostDirection::Down:
			this->y -= 0.5;
			this->x += dx;
			break;
		case GhostDirection::Left:
			this->x -= 0.5;
			this->y += dy;
			break;
		case GhostDirection::Right:
			this->x += 0.5;
			this->y += dy;
			break;
		}

		if (this->x > 1080) {
			this->x = 220;
		}

		if (this->x < 220) {
			this->x = 1080;
		}
	
	}
	else {
		blocked = false;
	}

}

void Ghost::Render(int time)
{


	auto w_h = 40;
	auto w_v = (float)(int)((frame % 8) / 8) + 1;

	auto tx_x = w_h / 8.0;
	auto tx_y = 0;
	

	glBindTexture(GL_TEXTURE_2D, texture_id);

	glPushMatrix();
	glTranslatef(this->x, this->y, 0);

	glBegin(GL_POLYGON);
	glTexCoord2f( 0.01, 0.01); glVertex2f(0, 0);
	glTexCoord2f(1.0 / 8.0 - 0.01,  0.01); glVertex2f(30, 0	);
	glTexCoord2f(1.0 / 8.0 - 0.01,  1.0 - 0.01); glVertex2f(30, 30);
	glTexCoord2f( 0.01,  1.0  - 0.01); glVertex2f(0, 30);
	glEnd();


	glPopMatrix();
}

void Ghost::SetPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

std::pair<float, float> Ghost::GetPosition()
{
	std::pair<float, float > pos;
	pos.first = this->x; pos.second = this->y;
	return pos;
}


void Ghost::SetBlock(bool status)
{
	this->blocked = status;
}

void Ghost::SetDirection(int dir)
{
	this->direction = GhostDirection(dir);
}