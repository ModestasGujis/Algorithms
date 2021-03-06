#ifndef UNDIRECTED_GRAPH_H
#define UNDIRECTED_GRAPH_H

#include <algorithm>
#include <vector>
#include "BaseGraph.h"

using namespace std;

class UndirectedGraph : public BaseGraph {
public:
	void add_edge(int a, int b, int w = 1);
	vector<int> connected_comp(int v);
	vector<vector<int>> MST();
private:
	void connected_comp_util(int v, vector<bool> &visited);
};

#endif // UNDIRECTED_GRAPH_H