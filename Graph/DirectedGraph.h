#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include <algorithm>
#include <vector>
#include "BaseGraph.h"

using namespace std;

class DirectedGraph: public BaseGraph {
public:
	using BaseGraph::BaseGraph;
	void add_edge(int a, int b, int w = 1);
	vector<int> topo_sort();
	int max_flow(int source, int sink);
private:
	void topo_sort_util(int v, vector<int> &currSort, vector<bool> &visited);
	int max_flow_BFS(int s, int t, vector<int>& parent, vector<vector<int>> capacities);
};

#endif // DIRECTED_GRAPH_H