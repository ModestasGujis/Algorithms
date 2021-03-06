#include <algorithm>
#include <queue>
#include <cassert>
#include <utility>
#include <stdio.h>
#include <iostream>

#include "UndirectedGraph.h"
#include "../DSU/DSU.h"

using namespace std;

void UndirectedGraph::add_edge(int from, int to, int weight) {
	edges[from].emplace_back(Edge(from, to, weight));
	edges[to].emplace_back(Edge(to, from, weight));
	edge_cnt++;
}

vector<int> UndirectedGraph::connected_comp(int v) {
	vector<bool> visited(vertex_cnt, false);
	connected_comp_util(v, visited);

	vector<int> components;
	for (int i = 0; i < vertex_cnt; ++i)
	{
		if (visited[i])
			components.emplace_back(i);
	}

	return components;
}

void UndirectedGraph::connected_comp_util(int v, vector<bool> &visited) {
	visited[v] = true;

	for (Edge ed : edges[v])
		if (!visited[ed.to])
			connected_comp_util(ed.to, visited);
}

vector<vector<int>> UndirectedGraph::MST() {
	vector<Edge> all_edges;
	for (int i = 0; i < vertex_cnt; ++i)
	{
		for (Edge u : edges[i]) {
			if (i < u.to) {
				all_edges.emplace_back(u);
			}
		}
	}

	sort(all_edges.begin(), all_edges.end(), [](const Edge & a, const Edge & b) {
		return a.weight < b.weight;
	});

	DSU connected(vertex_cnt);

	vector<vector<int>> result;

	for (Edge e : all_edges) {
		if (connected.isSameSet(e.from, e.to)) continue;

		connected.unionSet(e.from, e.to);
		result.emplace_back(vector<int> {e.from, e.to, e.weight});
	}

	if ((int)result.size() != vertex_cnt - 1) // UndirectedGraph is not connected
		return vector<vector<int>>();

	return result;
}
