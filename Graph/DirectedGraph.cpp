#include <algorithm>
#include <queue>
#include <cassert>
#include <utility>
#include <stdio.h>
#include <iostream>

#include "DirectedGraph.h"

using namespace std;

void DirectedGraph::add_edge(int from, int to, int weight) {
	edges[from].emplace_back(Edge(from, to, weight));
	edge_cnt++;
}

vector<int> DirectedGraph::topo_sort() {
	if (DirectedGraph::has_a_cycle()) return vector<int>();

	vector<int> current_rSort;
	vector<bool> visited(vertex_cnt, false);

	for (int i = 0; i < vertex_cnt; ++i)
	{
		if (!visited[i]) {
			topo_sort_util(i, current_rSort, visited);
		}
	}

	reverse(current_rSort.begin(), current_rSort.end());

	return current_rSort;
}

void DirectedGraph::topo_sort_util(int v, vector<int> &current_rSort, vector<bool> &visited) {
	visited[v] = true;

	for (Edge ed : edges[v]) {
		if (!visited[ed.to]) {
			DirectedGraph::topo_sort_util(ed.to, current_rSort, visited);
		}
	}

	current_rSort.emplace_back(v);
}

int DirectedGraph::max_flow_BFS(int s, int t, vector<int>& parents, vector<vector<int>> capacities) {
	fill(parents.begin(), parents.end(), -1);
	parents[s] = -2;
	queue<pair<int, int>> q;
	q.push({s, INT32_MAX});

	while(!q.empty()) {
		int current = q.front().first;
		int flow = q.front().second;
		q.pop();
		
		for (Edge next : edges[current]) {
			if(parents[next.to] == -1 && capacities[current][next.to]) {
				parents[next.to] = current;
                int new_flow = min(flow, capacities[current][next.to]);
                if (next.to == t)
                    return new_flow;
                q.push({next.to, new_flow});
			}
		}
	}
	return 0;
}

int DirectedGraph::max_flow(int source, int sink) {
	vector<vector<int>> capacities(vertex_cnt, vector<int>(vertex_cnt, 0));
	for(int i = 0; i < vertex_cnt; i++) {
		for(Edge j : edges[i]) {
			capacities[i][j.to] += j.weight;
		}
	}

	int flow = 0;
	vector<int> parent(vertex_cnt);
	int new_flow;
	while((new_flow = max_flow_BFS(source, sink, parent, capacities))) {
        flow += new_flow;
        int current = sink;
        while (current != source) {
            int previous = parent[current];
            capacities[previous][current] -= new_flow;
            capacities[current][previous] += new_flow;
            current = previous;
        }
    }
    return flow;
}
