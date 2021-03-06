#include <algorithm>
#include <queue>
#include <cassert>
#include <utility>
#include <stdio.h>
#include <iostream>

#include "BaseGraph.h"
#include "Edge.h"

using namespace std;

BaseGraph::BaseGraph(int _vertex_cnt, bool _weighted) {
	vertex_cnt = _vertex_cnt;
	weighted = _weighted;
	edges = vector<vector<Edge>>(_vertex_cnt);
	edge_cnt = 0;
}

BaseGraph::BaseGraph(int _vertex_cnt, vector<int> from, vector<int> to, vector<int> weight) {
	vertex_cnt = _vertex_cnt;
	weighted = true;
	edges = vector<vector<Edge>>(vertex_cnt);
	edge_cnt = 0;

	for (int i = 0; i < (int)from.size(); ++i)
	{
		add_edge(from[i], to[i], weight[i]);
	}
}

BaseGraph::BaseGraph(int _vertex_cnt, vector<int> from, vector<int> to) {
	vertex_cnt = _vertex_cnt;
	weighted = false;
	edges = vector<vector<Edge>>(_vertex_cnt);
	edge_cnt = 0;

	for (int i = 0; i < (int)from.size(); ++i)
	{
		add_edge(from[i], to[i]);
	}
}

int BaseGraph::get_vertex_cnt() { return vertex_cnt; }
int BaseGraph::get_edge_cnt() { return edge_cnt; }

int BaseGraph::add_vertex() {
	edges.emplace_back(vector<Edge>());
	return vertex_cnt++;
}

void BaseGraph::get_shortest_one_to_all_dijkstra(int from, vector<int> &dist, bool backtrack) {
	assert(from >= 0 and from < vertex_cnt);
	dist = vector<int>(vertex_cnt, -1);
	vector<int> origin;
	if (backtrack) origin = vector<int>(vertex_cnt, -1);
	dist[from] = 0;
	priority_queue<pair<int, int>> pq; // {negative distance, vertex}
	pq.push({0, from}); // {max heap}

	while (pq.size()) {
		int c = pq.top().second;
		int d = -pq.top().first;
		pq.pop();

		if (d > dist[c]) continue;

		for (Edge nxt : edges[c]) {
			if (dist[nxt.to] == -1 or dist[c] + nxt.weight < dist[nxt.to]) {
				dist[nxt.to] = dist[c] + nxt.weight;
				if (backtrack) {
					origin[nxt.to] = c;
				}
				pq.push({ -dist[nxt.to], nxt.to});
			}
		}
	}
	if (backtrack) dist = origin;
}

void BaseGraph::get_shortest_one_to_all_BFS(int from, vector<int> &dist, bool backtrack) {
	assert(from >= 0 and from < vertex_cnt);
	dist = vector<int>(vertex_cnt, -1);
	vector<int> origin;
	if (backtrack) origin = vector<int>(vertex_cnt, -1);

	dist[from] = 0;
	queue<int> q;
	q.push(from);

	while (q.size()) {
		int c = q.front(); q.pop();

		for (Edge nxt : edges[c]) {
			if (dist[nxt.to] == -1 or dist[c] + nxt.weight < dist[nxt.to]) {
				dist[nxt.to] = dist[c] + nxt.weight;
				if (backtrack) {
					origin[nxt.to] = c;
				}
				q.push(nxt.to);
			}
		}
	}
	if (backtrack) dist = origin;
}

int BaseGraph::shortest_distance(int a, int b) {
	assert(a >= 0 and a < vertex_cnt and b >= 0 and b < vertex_cnt);
	vector<int> dist;
	if (weighted) get_shortest_one_to_all_dijkstra(a, dist);
	else get_shortest_one_to_all_BFS(a, dist);

	return dist[b];
}

vector<int> BaseGraph::shortest_path(int a, int b) {
	assert(a >= 0 and a < vertex_cnt and b >= 0 and b < vertex_cnt);
	vector<int> backtrack;
	if (weighted) get_shortest_one_to_all_dijkstra(a, backtrack, true);
	else get_shortest_one_to_all_BFS(a, backtrack, true);

	if (backtrack[b] == -1) return vector<int>();

	vector<int> path;
	int c = b;
	while (c != a) {
		path.emplace_back(c);
		c = backtrack[c];
	}
	path.emplace_back(a);
	reverse(path.begin(), path.end());
	return path;
}

bool BaseGraph::has_a_cycle() {
	vector<int> visited(vertex_cnt, 0);

	for (int i = 0; i < vertex_cnt; ++i)
	{
		if (!visited[i]) {
			if (BaseGraph::has_a_cycle_util(i, visited))
				return true;
		}
	}
	return false;
}

bool BaseGraph::has_a_cycle_util(int v, vector<int> &visited) {
	visited[v] = 1;

	for (Edge ed : edges[v]) {
		if (visited[ed.to] == 1) return true;

		if (BaseGraph::has_a_cycle_util(ed.to, visited))
			return true;
	}

	visited[v] = 2;
	return false;
}