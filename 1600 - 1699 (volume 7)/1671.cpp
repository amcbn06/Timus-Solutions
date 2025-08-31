/* 1671. Anansi's Cobweb

Strategy:

Process the queries in reverse order and use Disjoint Set Union to keep up with the number 
of connected components.

* Time complexity: O(N + M + Q)
* Space complexity: O(N + Q)

*/
#include <bits/stdc++.h>
using namespace std;

// Source: https://github.com/amcbn06/dsa/
// Works with nodes in range [0, __size)
struct UnionFind {
	vector<int> parent, size;
	int components;
	UnionFind(int __size) : components(__size) {
		parent.resize(__size);
		size.resize(__size);
		for (int i = 0; i < __size; ++i) {
			parent[i] = i;
			size[i] = 1;
		}
	}
	int find(int x) {
		return parent[x] == x ? x : (parent[x] = find(parent[x]));
	}
	void merge(int x, int y) {
		x = find(x);
		y = find(y);
		if (x == y) {
			return;
		}
		--components;
		if (size[x] < size[y]) {
			swap(x, y);
		}
		parent[y] = x;
		size[x] += size[y];
	}
	bool connected(int x, int y) {
		return find(x) == find(y);
	}
};

const int nmax = 1e5;
int N, M, Q;
pair<int, int> edges[nmax];
int order[nmax];
int answer[nmax];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M;
	UnionFind dsu(N);
	for (int i = 0; i < M; ++i) {
		cin >> edges[i].first >> edges[i].second;
		edges[i].first--, edges[i].second--;
	}
	vector<bool> del(M);
	cin >> Q;
	for (int i = 0; i < Q; ++i) {
		cin >> order[i];
		order[i]--;
		del[order[i]] = true;
	}
	for (int i = 0; i < M; ++i) {
		if (!del[i]) {
			dsu.merge(edges[i].first, edges[i].second);
		}
	}
	for (int i = Q - 1; i >= 0; --i) {
		answer[i] = dsu.components;
		int j = order[i];
		dsu.merge(edges[j].first, edges[j].second);
	}
	for (int i = 0; i < Q; ++i) {
		cout << answer[i] << " ";
	}
}