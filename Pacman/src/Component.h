#pragma once
#include <GL/glut.h>

class Game;

class Component
{
public:

	enum Type {
		wall = 0,
		ghost = 1,
		point = 2,
		pacman = 3
	};

	Component(Component* parent);
	// Virtual
	void virtual Load(int time);
	// Abstarct
	void virtual Update(int time) = 0;
	void virtual Render(int time) = 0;
	Type type;

private:
	int u;
	

protected:

	int created_time;
	Game* game;
	Component* parent_component;

	friend class Game;

};