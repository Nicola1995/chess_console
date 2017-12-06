#include "Desk.h"
#include <vector>

using namespace std;

class Validator
{
private:
	Desk & desk;
	vector<pair<int, int>> strike_by_knight[8][8];
	vector<pair<int, int>> strike_by_line[8][8][4];
	vector<pair<int, int>> strike_by_diagonal[8][8][4];
	void precalc_strikes();
	void find_king(int & x, int & y, Desk::Color color);
	bool under_strike(int x, int y);
	bool is_line_figure(Desk::Figure figure);
	bool is_diagonal_figure(Desk::Figure figure);
public:
	enum class Status { NORMAL, STRIKE, INVALID };
	Validator(Desk & desk);
	Status get_status();
};
