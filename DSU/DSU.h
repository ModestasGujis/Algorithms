#ifndef DSU_H
#define DSU_H

#include <algorithm>
#include <vector>

using namespace std;

class DSU {
public:
	DSU(int n);
	int get_size();
	int get_size(int a);
	int find_set(int i);
	bool is_same_set(int i, int j);
	bool union_set(int i, int j); // false if already in union
private:
	vector<int> rank;
	vector<int> sz;
	vector<int> p; // parent
	int size;
};

#endif // DSU_H