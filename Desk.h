#pragma once

class Desk
{
public:
	enum class Color : int { EMPTY = 2, WHITE = 0, BLACK = 1 };
	enum class Figure { EMPTY, PIECE, KNIGHT, BISHOP, ROOK, QUEEN, KING };

	Color color[8][8];
	Figure figure[8][8];

	Color turn;

	int fast_x;
	bool can_castle[2];

	void init();
	static Color opposite_color(Color color);
};
