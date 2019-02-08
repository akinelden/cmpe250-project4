#ifndef Case_h
#define Case_h

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct grid_cell;


class CASE 
{
public:
	CASE();
	int FindSolution(int& r1, int& c1, int& r2, int&c2, int N, int M, int max_diff, vector<vector<grid_cell>>*& gridland);
};






#endif // !Case_h

