#ifndef BASE_GRAPH_H
#define BASE_GRAPH_H

#include <algorithm>
#include "Edge.h"

using namespace std;

class BaseGraph {
public:
	BaseGraph(int _vertex_cnt = 0, bool _weighted = false);
	BaseGraph(int _vertex_cnt, vector<int> from, vector<int> to, vector<int> weight);
	BaseGraph(int _vertex_cnt, vector<int> from, vector<int> to);
	int get_vertex_cnt();
	int get_edge_cnt();
	virtual void add_edge(int a, int b, int w = 1) = 0;
	int add_vertex();
	int shortest_distance(int a, int b); // -1 if path doesn't exist
	vector<int> shortest_path(int a, int b); // empty vector if ...
	bool has_a_cycle();
protected:
	bool weighted;
	int vertex_cnt;
	int edge_cnt;
	vector<vector<Edge>> edges;
private:
	bool has_a_cycle_util(int v, vector<int> &visited);
	void get_shortest_one_to_all_dijkstra(int from, vector<int> &dist, bool backtrack = false);
	void get_shortest_one_to_all_BFS(int from, vector<int> &dist, bool backtrack = false);
};

#endif // BASE_GRAPH_H