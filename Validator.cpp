#include "Validator.h"

Validator::Validator(Desk & desk) : desk(desk)
{
	precalc_strikes();	
}

Validator::Status Validator::get_status()
{
	int x, y;
	
	find_king(x, y, Desk::opposite_color(desk.turn));
	if (under_strike(x, y))
		return Status::INVALID;
	
	find_king(x, y, desk.turn);
	if (under_strike(x, y))
		return Status::STRIKE;
		
	return Status::NORMAL;		
}

void Validator::find_king(int & x, int & y, Desk::Color color)
{
	if (desk.can_castle[(int)color]) {
		x = 4;
		y = (color == Desk::Color::WHITE ? 0 : 7);
		return;
	}
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) 
			if (desk.color[i][j] == color && 
					desk.figure[i][j] == Desk::Figure::KING) {
				x = i;
				y = j;
				return;
			}
}

void Validator::precalc_strikes()
{
	auto valid = [] (int x, int y) {
		return x >= 0 && x < 8 && y >= 0 && y < 8;	
	}; 
	int kdx[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
	int kdy[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
	int ldx[4] = { 1, -1, 0, 0 };
	int ldy[4] = { 0, 0, 1, -1 };
	int ddx[4] = { 1, -1, -1, 1 };
	int ddy[4] = { 1, 1, -1, -1 };

	for (int x = 0; x < 8; x++)
		for (int y = 0; y < 8; y++) {
			for (int dir = 0; dir < 8; dir++)
				if (valid(x + kdx[dir], y + kdy[dir]))
					strike_by_knight[x][y].emplace_back(x + kdx[dir], y + kdy[dir]);
			for (int dir = 0; dir < 4; dir++) {
				for (int k = 1; valid(x + ldx[dir] * k, y + ldy[dir] * k); k++)
					strike_by_line[x][y][dir].emplace_back(x + ldx[dir] * k, y + ldy[dir] * k);
				for (int k = 1; valid(x + ddx[dir] * k, y + ddy[dir] * k); k++)
					strike_by_diagonal[x][y][dir].emplace_back(x + ddx[dir] * k, y + ddy[dir] * k);
			}	
		}
}

bool Validator::under_strike(int x, int y)
{
	auto my_color = desk.color[x][y];
	
	for (auto pos : strike_by_knight[x][y]) {
		if (desk.figure[pos.first][pos.second] == Desk::Figure::KNIGHT &&
			desk.color[pos.first][pos.second] != my_color)
			return true;
		if (desk.figure[pos.first][pos.second] != Desk::Figure::EMPTY)
			break;
	}
	
	for (int dir = 0; dir < 4; dir++) {
		for (auto pos : strike_by_line[x][y][dir])
			if (desk.figure[pos.first][pos.second] != Desk::Figure::EMPTY) {
				if (desk.color[pos.first][pos.second] != my_color &&
					is_line_figure(desk.figure[pos.first][pos.second]))
					return true;
				break;	
			}
		for (auto pos : strike_by_diagonal[x][y][dir])
			if (desk.figure[pos.first][pos.second] != Desk::Figure::EMPTY) {
				if (desk.color[pos.first][pos.second] != my_color && 
					is_diagonal_figure(desk.figure[pos.first][pos.second]))
					return true;
				break;	
			}
	}

	if (my_color == Desk::Color::WHITE) {
		if (y >= 6)
			return false;
		if (x > 0 && desk.figure[x-1][y+1] == Desk::Figure::PIECE && 
					desk.color[x-1][y+1] == Desk::Color::BLACK)
			return true;
		if (x < 7 && desk.figure[x+1][y+1] == Desk::Figure::PIECE &&
					desk.color[x+1][y+1] == Desk::Color::BLACK)
			return true;		
	}
	else {	
		if (y <= 1)
			return false;
		if (x > 0 && desk.figure[x-1][y-1] == Desk::Figure::PIECE && 
					desk.color[x-1][y-1] == Desk::Color::WHITE)
			return true;
		if (x < 7 && desk.figure[x+1][y-1] == Desk::Figure::PIECE &&
					desk.color[x+1][y-1] == Desk::Color::WHITE)
			return true;		
	}

	return false;
}

bool Validator::is_line_figure(Desk::Figure figure)
{
	return figure == Desk::Figure::ROOK ||
		figure == Desk::Figure::QUEEN ||
		figure == Desk::Figure::KING;
}

bool Validator::is_diagonal_figure(Desk::Figure figure)
{
	return figure == Desk::Figure::BISHOP ||
		figure == Desk::Figure::QUEEN ||
		figure == Desk::Figure::KING;
}
