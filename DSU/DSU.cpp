#include <algorithm>
#include <numeric>

#include "DSU.h"

using namespace std;

DSU::DSU(int n) {
	size = n;
	rank = vector<int>(n, 1);
	sz = vector<int>(n, 1);
	p = vector<int>(n);
	iota(p.begin(), p.end(), 0);
}

int DSU::get_size() {
	return size;
}

int DSU::get_size(int i) {
	return sz[find_set(i)];
}

int DSU::find_set(int i) {
	return (p[i] == i) ? i : (p[i] = find_set(p[i]));
}

bool DSU::is_same_set(int i, int j) {
	return find_set(i) == find_set(j);
}

bool DSU::union_set(int i, int j) {
	if (is_same_set(i, j)) return false;

	int x = find_set(i), y = find_set(j);

	if (rank[x] < rank[y]) swap(x, y);

	sz[x] += sz[y];
	p[y] = x;
	if (rank[x] == rank[y]) rank[x]++;
	return true;
}