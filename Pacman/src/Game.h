#pragma once
#include <vector>
#include "Component.h"
#include "Pacman.h"
#include "Wall.h"
#include "Ghost.h"
#include "Point.h"

class Game : public Component
{
public:
	Game();
	~Game();

	void Load(int time);
	void Update(int time);
	void Render(int time);

	void keyboard(int time, int key, int x, int y);
	void keyboard_up(int time, int key, int x, int y);

	void PacmanEat(Point* point);
	void PacmanWall(Wall* wall);
	void PacmanGhost(Ghost* ghost);

	void GhostWall(Ghost* ghost,Wall * wall);

	void GameOver();
	void GameWin();

	void GameOverRender();
	void WinRender();
		
private:

	Pacman* pacman;
	std::vector<Wall*> walls;
	std::vector<Point*> points;
	std::vector<Ghost*> ghosts;
	int gains;
	bool win;
	bool gameover;
};