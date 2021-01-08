#include "Pacman.h"
#include "SOIL.h"
#include <iostream>

using namespace std;

Pacman::Pacman(Component* parent) : Component(parent)
{
	//init_frame = ((double)rand() / (RAND_MAX)) * 64;
	this->type = pacman;
	this->blocked = false;
}

void Pacman::Load(int time)
{
	Component::Load(time);

	texture_id = SOIL_load_OGL_texture("pacman-sp2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
}

void Pacman::Update(int time)
{
	if (this->is_run)
	{
		this->frame = (time - this->start_move_time) / 100;

		if (is_run == true && blocked == false) {
			switch (this->direction)
			{
			case CharacterDirection::Up:
				this->y += 1;
				break;
			case CharacterDirection::Down:
				this->y -= 1;
				break;
			case CharacterDirection::Left:
				this->x -= 1;
				break;
			case CharacterDirection::Right:
				this->x += 1;
				break;
			}

			if (this->x > 1000) {
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
	else
	{
		this->frame = 0;
	}
}

void Pacman::Render(int time)
{
	auto f = (float)(this->frame % 5);

	auto tx_w = 30;
	auto tx_h = 30;



	auto tx_x = f / 5.0 + f * 0.001;
	auto tx_y = 0;

	float dif = 0.0;
	float dif2 = 0.0;

	if (f != 0) {
		dif2 = 0.01;
	}

	if (f != 4) {
		dif = 0.01;
	}

	std::cout << tx_x << endl;

	glBindTexture(GL_TEXTURE_2D, texture_id);

	glPushMatrix();
	glTranslatef(this->x, this->y, 0);

	glBegin(GL_POLYGON);
	glTexCoord2f(tx_x + dif2, 0); glVertex2f(0, 0);
	glTexCoord2f(tx_x + 1.0 / 5.0 - 0.01 - dif, 0); glVertex2f(tx_w, 0);
	glTexCoord2f(tx_x + 1.0 / 5.0 - 0.01 - dif, 1); glVertex2f(tx_w, tx_h);
	glTexCoord2f(tx_x + dif2, 1); glVertex2f(0, tx_h);
	glEnd();

	glPopMatrix();
}

void Pacman::SetPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

std::pair<float, float> Pacman::GetPosition()
{
	std::pair<float, float> pos;
	pos.first = this->x;
	pos.second = this->y;
	return pos;
}


void Pacman::up(int time)
{
	if (this->is_run && this->direction == CharacterDirection::Up) return;

	this->is_run = true;
	this->start_move_time = time;
	this->direction = CharacterDirection::Up;
}

void Pacman::down(int time)
{
	if (this->is_run && this->direction == CharacterDirection::Down) return;

	this->is_run = true;
	this->start_move_time = time;
	this->direction = CharacterDirection::Down;
}

void Pacman::left(int time)
{
	if (this->is_run && this->direction == CharacterDirection::Left) return;

	this->is_run = true;
	this->start_move_time = time;
	this->direction = CharacterDirection::Left;
}

void Pacman::right(int time)
{
	if (this->is_run && this->direction == CharacterDirection::Right) return;

	this->is_run = true;
	this->start_move_time = time;
	this->direction = CharacterDirection::Right;
}

void Pacman::stop(int time)
{
	this->is_run = false;
}


void Pacman::SetBlock(bool status)
{
	this->blocked = status;
}