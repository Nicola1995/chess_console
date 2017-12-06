#include "Desk.h"

void Desk::init()
{
	for (int x = 0; x < 8; x++)
		for (int y = 0; y < 8; y++) {
			figure[x][y] = Figure::EMPTY;
			color[x][y] = Color::EMPTY;
		}
	
	for (int x = 0; x < 8; x++) {
		color[x][1] = Color::WHITE;
		figure[x][1] = Figure::PIECE;
		color[x][6] = Color::BLACK;
		figure[x][6] = Figure::PIECE;
		color[x][0] = Color::WHITE;
		color[x][6] = Color::BLACK;
	}

	figure[0][0] = figure[0][7] = Figure::ROOK;
	figure[1][0] = figure[1][7] = Figure::KNIGHT;
	figure[2][0] = figure[2][7] = Figure::BISHOP;
	figure[3][0] = figure[3][7] = Figure::QUEEN;
	figure[4][0] = figure[4][7] = Figure::KING;
	figure[5][0] = figure[5][7] = Figure::BISHOP;
	figure[6][0] = figure[6][7] = Figure::KNIGHT;
	figure[7][0] = figure[7][7] = Figure::ROOK;

	can_castle[(int)Color::WHITE] = true;
	can_castle[(int)Color::BLACK] = true;
	
	fast_x = -1;	
	turn = Color::WHITE;
}

Desk::Color Desk::opposite_color(Color color)
{
	switch (color) {
	case Color::WHITE:
		return Color::BLACK;
	case Color::BLACK:	
		return Color::WHITE;
	case Color::EMPTY:
		return Color::EMPTY;	
	}
}
