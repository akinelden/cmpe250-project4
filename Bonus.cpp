#include "Bonus.h"


struct coord {
	int r;
	int c;
	int diff;
};

struct grid_cell {
	int height = 0;
	int row;
	int column;
	int left = -1;
	int right = -1;
	int up = -1;
	int down = -1;
	bool visited = false;
	coord prev_cell;
	coord prev_corner;
	int group;
	int counter;
	bool corner = false;
	vector<coord> next_cells;
};


struct compared_cell {
	coord current;
	coord prev;
};

class EdgeComp2
{
public:
	bool operator() (compared_cell& c1, compared_cell& c2) {
		if (c1.current.diff > c2.current.diff)
			return true;
		return false;
	}
};


void BONUS::FindNext(coord & current, vector<vector<grid_cell>>*& gridland, vector<priority_queue<compared_cell, vector<compared_cell>, EdgeComp2>>& sorted_cells, int & bin)
{
	(*gridland)[current.r][current.c].visited = true;
	if ((*gridland)[current.r][current.c].up != -1) {
		if ((*gridland)[current.r - 1][current.c].visited != true) {
			compared_cell c;
			c.current.r = current.r - 1;
			c.current.c = current.c;
			c.prev.r = current.r;
			c.prev.c = current.c;
			c.prev.diff = c.current.diff = (*gridland)[current.r][current.c].up;
			sorted_cells[c.current.diff / bin].push(c);
		}
	}
	if ((*gridland)[current.r][current.c].down != -1) {
		if ((*gridland)[current.r + 1][current.c].visited != true) {
			compared_cell c;
			c.current.r = current.r + 1;
			c.current.c = current.c;
			c.prev.r = current.r;
			c.prev.c = current.c;
			c.prev.diff = c.current.diff = (*gridland)[current.r][current.c].down;
			sorted_cells[c.current.diff / bin].push(c);
		}
	}
	if ((*gridland)[current.r][current.c].left != -1) {
		if ((*gridland)[current.r][current.c - 1].visited != true) {
			compared_cell c;
			c.current.r = current.r;
			c.current.c = current.c - 1;
			c.prev.r = current.r;
			c.prev.c = current.c;
			c.prev.diff = c.current.diff = (*gridland)[current.r][current.c].left;
			sorted_cells[c.current.diff / bin].push(c);
		}
	}
	if ((*gridland)[current.r][current.c].right != -1) {
		if ((*gridland)[current.r][current.c + 1].visited != true) {
			compared_cell c;
			c.current.r = current.r;
			c.current.c = current.c + 1;
			c.prev.r = current.r;
			c.prev.c = current.c;
			c.prev.diff = c.current.diff = (*gridland)[current.r][current.c].right;
			sorted_cells[c.current.diff / bin].push(c);
		}
	}
}

BONUS::BONUS()
{
}

void BONUS::GetInfo(int N, int M, int max_diff, vector<vector<grid_cell>>* gridland)
{
	//vector<compared_cell> vect;
	//vect.reserve(10*N);
	vector<priority_queue<compared_cell, vector<compared_cell>, EdgeComp2>> sorted_cells(4);
	int bin = max_diff / 4 + 1;

	int count = 0;
	{
		coord temp;
		temp.c = 0;
		temp.r = 0;
		FindNext(temp, gridland, sorted_cells, bin);
		count++;
	}
	while (count < N*M) {
		compared_cell temp;
		for (int i = 0; i < 4; i++) {
			if (!sorted_cells[i].empty()) {
				temp = sorted_cells[i].top();
				sorted_cells[i].pop();
				break;
			}
		}
		
		if ((*gridland)[temp.current.r][temp.current.c].visited == true)
			continue;
		coord cur = temp.current;
		(*gridland)[temp.prev.r][temp.prev.c].next_cells.push_back(cur);
		(*gridland)[cur.r][cur.c].prev_cell = temp.prev;
		FindNext(temp.current, gridland, sorted_cells, bin);
		count++;
	}

	int ingr = 0;
	int gr_no = 0;
	coord current_corner;

	stack<coord> my_stack;
	{
		coord temp;
		temp.c = 0;
		temp.r = 0;
		temp.diff = 0;
		my_stack.push(temp);
		(*gridland)[0][0].corner = true;
		(*gridland)[0][0].counter = ingr;
		(*gridland)[0][0].prev_cell.diff = 0;
	}

	current_corner.r = 0;
	current_corner.c = 0;
	current_corner.diff = 0;
	count = 1;
	ingr++;

	while (count < N*M && !my_stack.empty()) {

		coord tmp = my_stack.top();
		grid_cell& temp = (*gridland)[tmp.r][tmp.c];
		temp.visited = false;
		count++;
		temp.group = gr_no;
		temp.counter = ingr;
		ingr++;
		current_corner.diff = max(temp.prev_cell.diff, current_corner.diff);
		temp.prev_corner = current_corner;
		if (temp.next_cells.size() > 1 || temp.corner) {
			temp.corner = true;
			gr_no++;
			current_corner.r = tmp.r;
			current_corner.c = tmp.c;
			current_corner.diff = 0;
			ingr = 0;
		}
		for (int i = 0; i < temp.next_cells.size(); i++) {
			coord c = temp.next_cells[i];
			my_stack.push(c);
		}
		if (temp.next_cells.size() == 0) {
			my_stack.pop();
			coord c = my_stack.top();
			while (!my_stack.empty() && !(*gridland)[c.r][c.c].visited) {
				my_stack.pop();
				c = my_stack.top();
			}
			gr_no++;
			ingr = 0;
			current_corner = (*gridland)[c.r][c.c].prev_cell;
			current_corner.diff = 0;
		}

	}
}

int BONUS::FindSolution(int & r1, int & c1, int & r2, int & c2, int N, int M, vector<vector<grid_cell>>*& gridland)
{
	int ladder;
	coord current1, current2;
	current1.r = r1;
	current1.c = c1;
	current1.diff = 0;
	current2.r = r2;
	current2.c = c2;
	current2.diff = 0;
	int gr1, gr2;
	grid_cell& source = (*gridland)[r1][c1];
	grid_cell& target = (*gridland)[r2][c2];
	gr1 = source.group;
	gr2 = target.group;
	while (gr1 != gr2) {
		while (gr1 > gr2) {
			coord& temp = (*gridland)[current1.r][current1.c].prev_corner;
			current1.r = temp.r;
			current1.c = temp.c;
			current1.diff = max(current1.diff, temp.diff);
			gr1 = (*gridland)[temp.r][temp.c].group;
		}
		while (gr2 > gr1) {
			coord& temp = (*gridland)[current2.r][current2.c].prev_corner;
			current2.r = temp.r;
			current2.c = temp.c;
			current2.diff = max(current2.diff, temp.diff);
			gr2 = (*gridland)[temp.r][temp.c].group;
		}
	}
	if (current1.r == current2.r && current1.c == current2.c) {
		ladder = max(current1.diff, current2.diff);
		return ladder;
	}

	coord first;
	coord second;
	if ((*gridland)[current1.r][current1.c].counter > (*gridland)[current2.r][current2.c].counter) {
		first = current1;
		second = current2;
	}
	else {
		first = current2;
		second = current1;
	}

	while (1) {
		coord& temp = (*gridland)[first.r][first.c].prev_cell;
		first.r = temp.r;
		first.c = temp.c;
		first.diff = max(first.diff, temp.diff);
		if (first.r == second.r && first.c == second.c) {
			ladder = max(first.diff, second.diff);
			return ladder;
		}
	}
	return 0;
}
