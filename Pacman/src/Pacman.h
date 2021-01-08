#pragma once
#include "Component.h"
#include <iostream>

class Pacman : public Component
{
public:

	enum CharacterDirection
	{
		None = 0, Up = 1, Right = 2, Down = 3, Left = 4
	};

	Pacman(Component* parent);
	void Load(int time);
	void Update(int time);
	void Render(int time);
	void SetPosition(int x, int y);

	std::pair<float, float> GetPosition();
	void SetBlock(bool status);

	void up(int time);
	void down(int time);
	void left(int time);
	void right(int time);
	void stop(int time);

	CharacterDirection direction;
	

private:
	float x; float y;
	GLuint texture_id;
	int frame;
	bool blocked;
	int start_move_time;
	
	bool is_run;
};