#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <chrono>

#include "Case.h"
#include "Bonus.h"

using namespace std;

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



int main(int argc, char* argv[]) {

	auto begin = chrono::high_resolution_clock::now();

	ios_base::sync_with_stdio(false);
	
	if (argc != 3) {
		cout << "Run the code with the following command: ./project4 [input_file] [output_file]" << endl;
		return 1;
	}
	

	
	ifstream infile(argv[1]);

	int N, M;
	infile >> N >> M;

	vector<vector<grid_cell>>* gridland = new vector<vector<grid_cell>>(N, vector<grid_cell>(M));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			infile >> (*gridland)[i][j].height;
			(*gridland)[i][j].row = i;
			(*gridland)[i][j].column = j;
		}
	}

	int max_diff = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			grid_cell& temp = (*gridland)[i][j];
			if (i != N - 1)
				temp.down = (*gridland)[i + 1][j].up = abs(temp.height - (*gridland)[i + 1][j].height);
			if (j != M - 1)
				temp.right = (*gridland)[i][j+1].left = abs(temp.height - (*gridland)[i][j + 1].height);
			int x = max(temp.down, temp.right);
			if (x > max_diff)
				max_diff = x;
		}
	}


	ofstream myfile;
	myfile.open(argv[2]);

	int Q;
	infile >> Q;

	if (Q == 1) {
		int r1, r2, c1, c2;
		infile >> r1 >> c1 >> r2 >> c2;
		r1 = r1 - 1;
		c1 = c1 - 1;
		r2--;
		c2--;
		CASE cas;
		int result = cas.FindSolution(r1, c1, r2, c2, N,M,max_diff, gridland);
		myfile << result << endl;
		return 0;
	}

	else {
		BONUS bon;
		bon.GetInfo(N, M, max_diff, gridland);
		for (int q = 0; q < Q; q++) {
			int r1, r2, c1, c2;
			infile >> r1 >> c1 >> r2 >> c2;
			r1 = r1 - 1;
			c1 = c1 - 1;
			r2--;
			c2--;
			int result = bon.FindSolution(r1, c1, r2, c2, N, M, gridland);
			myfile << result << endl;
		}
	}

	
	myfile.close();

	delete gridland;
	
	auto stop = chrono::high_resolution_clock::now();
	auto duration3 = chrono::duration_cast<chrono::microseconds>(stop - begin);
	//cout << endl << "Run time: " << duration3.count() << endl;

	return 0;

}