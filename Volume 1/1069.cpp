/* 1069. Prufer Code

Strategy:
Just use the reconstruction technique from https://cp-algorithms.com/graph/pruefer_code.html

Performance:
We use a set to store all the current leaves, therefore it will
run in O(nlogn), and all the other operations are done in linear time

* Time complexity: O(nlogn)
* Space complexity: O(n)

*/
#include <bits/stdc++.h>
using namespace std;

const int nmax = 7500;
int n = 0;
int code[nmax + 5];
int degree[nmax + 5];
vector<int> g[nmax + 5];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	while (cin >> code[++n]);
	fill_n(degree + 1, n, 1);
	for (int i = 1; i < n; ++i) {
		degree[code[i]]++;
	}
	priority_queue<int, vector<int>, greater<int>> leaves;
	for (int u = 1; u <= n; ++u) {
		if (degree[u] == 1) {
			leaves.push(u);
		}
	}
	for (int i = 1; i < n; ++i) {
		int u = leaves.top(), v = code[i];
		leaves.pop();
		g[u].push_back(v);
		g[v].push_back(u);
		if (--degree[v] == 1) {
			leaves.push(v);
		}
	}
	for (int u = 1; u <= n; ++u) {
		sort(g[u].begin(), g[u].end());
		cout << u << ": ";
		for (auto& v : g[u]) {
			cout << v << " ";
		}
		cout << "\n";
	}
}
