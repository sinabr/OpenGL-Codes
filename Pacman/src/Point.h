#pragma once
#include "Component.h"
#include <iostream>

class Point : public Component
{
public:
	Point(Component* parent,bool big);
	void Load(int time);
	void Update(int time);
	void Render(int time);
	void SetPosition(int x, int y);
	void SetBig();
	std::pair<int, int> GetPosition();
	void Eaten();
	bool Big();
	bool Fresh();
private:
	int x; int y;
	GLuint texture_id;
	int init_frame, frame;
	bool big;
	bool eaten;
};