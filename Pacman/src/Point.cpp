#include "Point.h"
#include <soil.h>
#include <iostream>


using namespace std;

Point::Point(Component* parent, bool big) : Component(parent)
{
	init_frame = ((double)rand() / (RAND_MAX)) * 64;
	this->type = point;
	this->eaten = false;
	this->big = big;
}

void Point::Load(int time)
{
	Component::Load(time);

	if (this->big) {
		texture_id = SOIL_load_OGL_texture("big_point.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	}
	else {
		texture_id = SOIL_load_OGL_texture("small_point.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	}

}

void Point::Update(int time)
{
	frame = init_frame + (time - created_time) / 50;
}

void Point::Render(int time)
{
	auto w_h = (float)(frame % 8);
	auto w_v = (float)(int)((frame % 64) / 8) + 1;

	auto tx_w = 1024.0 / 8.0;
	auto tx_h = 1024.0 / 8.0;
	auto tx_x = w_h / 8.0;
	auto tx_y = 1 - w_v / 8.0;

	glBindTexture(GL_TEXTURE_2D, texture_id);

	if (this->eaten == false) {
		glPushMatrix();
		glTranslatef(this->x, this->y, 0);

		glBegin(GL_POLYGON);
		glTexCoord2f(0, 0); glVertex2f(0, 0);
		glTexCoord2f(1, 0); glVertex2f(35, 0);
		glTexCoord2f(1, 1); glVertex2f(35, 35);
		glTexCoord2f(0, 1); glVertex2f(0, 35);
		glEnd();

		glPopMatrix();
	}
}

void Point::SetPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

std::pair<int, int> Point::GetPosition() 
{
	std::pair<int, int> pos;
	pos.first = this->x;
	pos.second = this->y;
	return pos;
}

void Point::SetBig()
{
	this->big = true;
}

void Point::Eaten()
{
	this->eaten = true;
}

bool Point::Big()
{
	return this->big;
}

bool Point::Fresh()
{
	if (this->eaten == false)
		return true;
	else
		return false;
}