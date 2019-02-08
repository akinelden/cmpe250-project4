#include "Case.h"


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


class EdgeComp1
{
public:
	bool operator() (coord& c1, coord& c2) {
		if (c1.diff > c2.diff)
			return true;
		return false;
	}
};

CASE::CASE()
{
}

int CASE::FindSolution(int & r1, int & c1, int & r2, int & c2, int N, int M, int max_diff, vector<vector<grid_cell>>*& gridland)
{
	int bin = max_diff / (10 * M);
	vector<coord> to_be_opened;
	to_be_opened.reserve(N*M * 4);

	vector<priority_queue<coord, vector<coord>, EdgeComp1>> sorted_cells(max_diff / bin + 1);
	int current_diff = 0;
	int i = r1;
	int j = c1;
	int tb = 0;
	int which_queue = 0;
	while (i != r2 || j != c2) {
		grid_cell& temp = (*gridland)[i][j];
		temp.visited = true;
		if (temp.up != -1) {
			coord z;
			z.r = i - 1;
			z.c = j;
			z.diff = temp.up;
			if (!(*gridland)[z.r][z.c].visited) {
				if (z.diff > current_diff)
					sorted_cells[z.diff / bin].push(z);
				else to_be_opened.push_back(z);
			}
		}

		if (temp.down != -1) {
			coord z;
			z.r = i + 1;
			z.c = j;
			z.diff = temp.down;
			if (!(*gridland)[z.r][z.c].visited) {
				if (z.diff > current_diff)
					sorted_cells[z.diff / bin].push(z);
				else to_be_opened.push_back(z);
			}
		}

		if (temp.left != -1) {
			coord z;
			z.r = i;
			z.c = j - 1;
			z.diff = temp.left;
			if (!(*gridland)[z.r][z.c].visited) {
				if (z.diff > current_diff)
					sorted_cells[z.diff / bin].push(z);
				else to_be_opened.push_back(z);
			}
		}

		if (temp.right != -1) {
			coord z;
			z.r = i;
			z.c = j + 1;
			z.diff = temp.right;
			if (!(*gridland)[z.r][z.c].visited) {
				if (z.diff > current_diff)
					sorted_cells[z.diff / bin].push(z);
				else to_be_opened.push_back(z);
			}
		}

		while (tb < to_be_opened.size() && (*gridland)[to_be_opened[tb].r][to_be_opened[tb].c].visited)
			tb++;

		while (tb == to_be_opened.size()) {
			while (sorted_cells[which_queue].empty())
				which_queue++;
			coord z = sorted_cells[which_queue].top();
			sorted_cells[which_queue].pop();
			current_diff = z.diff;
			if (!(*gridland)[z.r][z.c].visited)
				to_be_opened.push_back(z);
		}

		i = to_be_opened[tb].r;
		j = to_be_opened[tb].c;
		tb++;

	}
	return current_diff;
}
