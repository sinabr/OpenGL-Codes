#pragma once
#include "Component.h"
#include <iostream>

class Ghost : public Component
{
public:

	enum GhostDirection
	{
		 Up = 0, Right = 1, Down = 2, Left = 3
	};

	Ghost(Component* parent);
	void Load(int time);
	void Update(int time);
	void Render(int time);
	void SetPosition(int x, int y);

	std::pair<float, float> GetPosition();
	void SetBlock(bool val);
	void SetDirection(int dir);


	GhostDirection direction;

private:
	float x; float y;
	GLuint texture_id;
	int init_frame, frame;

	bool blocked;
	int start_move_time;

	int move_cycle;
};

