/* 1056. Centers of the Net

Strategy:
Basically we are asked to find the centers of a tree, meaning the nodes
that are in the middle of some diameter of the tree;
Let's take a moment to think about how many nodes can be centers of a tree:
- 1 node? sure
- 2 nodes? right in the example
- 3 nodes? well, in any way we pick these three nodes in any tree, either one
or two of them will be actual centers and the others won't (intuitively,
there probably is actual proof of this fact)
=> Therefore there are at most 2 centers!

If there is just one center, it's the middle of any diameter of the tree we find;
if there are two, intuitively we can see that there can be only one diameter
Therefore, we find one diameter of the tree, and if it admits one center (the number
of edges is even), then there is one center, otherwise there are two centers

Performance:
We do BFS once from a random node to find an end X of a diameter,
another BFS from this end to find another end Y such that the
path from X to Y is a diameter of the tree, and a third BFS from Y
to the rest of the nodes to be sure that a node is on the diameter => O(N)

* Time complexity: O(N)
* Space complexity: O(N)

*/
#include <bits/stdc++.h>
using namespace std;

const int inf = 0x3f3f3f3f;
const int nmax = 1e4;
int n;
int p[nmax + 5];
vector<int> g[nmax + 5];
int dx[nmax + 5];
int dy[nmax + 5];

void bfs(int src, int dist[]) {
	fill_n(dist + 1, n, inf);
	dist[src] = 0;
	queue<int> q;
	q.push(src);
	while (q.size()) {
		int u = q.front();
		for (auto& v : g[u]) {
			if (dist[v] > dist[u] + 1) {
				dist[v] = dist[u] + 1;
				q.push(v);
			}
		}
		q.pop();
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 2; i <= n; ++i) {
		cin >> p[i];
		g[i].push_back(p[i]);
		g[p[i]].push_back(i);
	}
	bfs(1, dx);
	int x = max_element(dx + 1, dx + n + 1) - dx;
	bfs(x, dx);
	int y = max_element(dx + 1, dx + n + 1) - dx;
	bfs(y, dy);
	for (int u = 1; u <= n; ++u) {
		// is in the diameter and the distance from it to X and to Y are off by at most one
		if (dx[u] + dy[u] == dx[y] && abs(dx[u] - dy[u]) <= 1) {
			cout << u << " ";
		}
	}
}
