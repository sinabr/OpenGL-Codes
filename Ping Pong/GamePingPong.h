#pragma once
#include "Circles.h"
#include "Lines.h"
#include <vector>

#define M_PI 3.14159265358979323846


namespace PingPong
{
	struct Player
	{
		int Position;
	};

	struct Ball
	{
		int Position_X;
		int Position_Y;
		float Velocity_X;
		float Velocity_Y;
	};

	struct Rectangle
	{
		// whether removed or not
		int visible;
		// the left edge of the rectangle
		int positionx;
		int positiony;
	};

	struct GameState
	{
		int FieldWidth;
		int FieldHeight;
		int RaquetWidth;
		int RaquetHeight;
		int RaquetMargin;
		int BallSize;

		//rectangles
		int Nrow;
		int Ncolumn;
		int Nwidth;
		int Nheight;

		Player Player_1;
		std::vector<Rectangle> rectangles;
		Ball Ball;

		GameState(int width, int height) :
			FieldWidth(width), FieldHeight(height)
		{ 
			RaquetWidth = height / 8;
			RaquetHeight = height / 24;
			BallSize = height / 24;
			RaquetMargin = height / 24;

			Nwidth = width / 16;
			Nheight = height / 16;


			rectangles.reserve(Nwidth * Nheight);

			Player_1.Position = width / 2;

			Nrow = 8;
			Ncolumn = 16;

		}

		void init();
		void next_state();
		void change_state(int player, int state);
	};

	void init();
	void render();
	void reshape(int width, int height);
	void mouse(int button, int state, int x, int y);
	void motion(int x, int y);
	void timer(int value);

	void main(int argc, char** argv);
}