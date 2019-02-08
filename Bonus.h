#ifndef Bonus_h
#define Bonus_h

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

struct grid_cell;
struct coord;
struct compared_cell;
class EdgeComp2;

class BONUS
{
	void FindNext(coord& current, vector<vector<grid_cell>>*& gridland, vector<priority_queue<compared_cell, vector<compared_cell>, EdgeComp2>>& sorted_cells, int& bin);
public:
	BONUS();
	void GetInfo(int N, int M, int max_diff, vector<vector<grid_cell>>* gridland);
	int FindSolution(int & r1, int & c1, int & r2, int & c2, int N, int M, vector<vector<grid_cell>>*& gridland);
	
};





#endif // !Bonus_h
