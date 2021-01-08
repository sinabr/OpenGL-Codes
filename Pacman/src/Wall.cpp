#include "Wall.h"
#include <soil.h>

Wall::Wall(Component* parent) : Component(parent)
{
	init_frame = ((double)rand() / (RAND_MAX)) * 64;
	this->type = wall;
}

void Wall::Load(int time)
{
	Component::Load(time);

	texture_id = SOIL_load_OGL_texture("wall.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	
}

void Wall::Update(int time)
{
	frame = init_frame + (time - created_time) / 50;
}

void Wall::Render(int time)
{


	glBindTexture(GL_TEXTURE_2D, texture_id);

	glPushMatrix();
	glTranslatef(this->x, this->y, 0);
		
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex2f(0, 0);
	glTexCoord2f(1.0, 0); glVertex2f(39, 0);
	glTexCoord2f(1.0, 1.0); glVertex2f(39, 39);
	glTexCoord2f(0, 1.0); glVertex2f(0, 39);
	glEnd();

	glPopMatrix();
}

void Wall::SetPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

std::pair<int,int> Wall::GetPosition()
{
	std::pair<int, int> pos;
	pos.first = this->x;
	pos.second = this->y;
	return pos;
}
