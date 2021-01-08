#pragma once
#include "Component.h"
#include <iostream>

class Wall : public Component
{
public:
	Wall(Component* parent);
	void Load(int time);
	void Update(int time);
	void Render(int time);
	void SetPosition(int x, int y);
	std::pair<int, int> GetPosition();
private:
	int x; int y;
	GLuint texture_id;
	int init_frame, frame;
	int w, h = 40;
};