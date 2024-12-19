/* 1031. Railway Tickets

Strategy:
We compute cost[i] = smallest cost needed to reach a station
We use Dijkstra's algorithm, each time we encounter a node we go to all the other
nodes and add them plus a certain cost depending on the distance between them

Performance:
For each node in the Djikstra we'll add at most N - 1 other nodes,
so the time complexity is N^2logN (logN from the heap)

* Time complexity: O(N^2logN)
* Space complexity: O(N)

*/
#include <bits/stdc++.h>
using namespace std;

const int nmax = 1e4;
int L1, L2, L3, C1, C2, C3;
int n, src, dst;
int a[nmax + 5];
long long cost[nmax + 5];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> L1 >> L2 >> L3 >> C1 >> C2 >> C3;
	cin >> n >> src >> dst;
	for (int i = 2; i <= n; ++i) {
		cin >> a[i];
	}
	fill_n(cost + 1, n, 1e18);
	priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
	cost[src] = 0;
	pq.push({ 0, src });
	while (pq.size()) {
		long long cur = pq.top().first;
		int u = pq.top().second;
		pq.pop();
		if (cost[u] != cur) {
			continue;
		}
		for (int v = 1; v <= n; ++v) {
			if (u == v) {
				continue;
			}
			int distance = abs(a[u] - a[v]);
			long long nxt = cost[u];
			if (distance <= L1) {
				nxt += C1;
			}
			else if (distance <= L2) {
				nxt += C2;
			}
			else if (distance <= L3) {
				nxt += C3;
			}
			else {
				continue;
			}
			if (nxt < cost[v]) {
				cost[v] = nxt;
				pq.push({ nxt, v });
			}
		}
	}
	cout << cost[dst] << "\n";
}
