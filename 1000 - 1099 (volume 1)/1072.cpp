/* 1072. Routing

Strategy:
Create a graph with edges between computers and subnets and run BFS on it

Performance:
There are N computers and at most NK subnets, and at most NK edges between them
=> O(NKlogN) for the BFS because we use a map to store the subnets

* Time complexity: O(NK)
* Space complexity: O(NK)

*/
#include <bits/stdc++.h>
using namespace std;

const int nmax = 90;
const int kmax = 90;
int n, src, dst;
map<long long, vector<long long>> g;
map<long long, int> dist;
map<long long, long long> prv;

long long toMask(string adress) {
	int pos = 0;
	long long mask = 0;
	while (pos < adress.size()) {
		int nxt = adress.find('.', pos);
		if (nxt == -1) {
			nxt = adress.size();
		}
		mask = mask << 8 | stoi(adress.substr(pos, nxt - pos));
		pos = nxt + 1;
	}
	return mask;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		int sz;
		cin >> sz;
		for (int j = 0; j < sz; ++j) {
			string IP_adress, subnet_adress;
			cin >> IP_adress >> subnet_adress;
			long long subnet = toMask(IP_adress) & toMask(subnet_adress);
			g[i].push_back(nmax + 1 + subnet);
			g[nmax + 1 + subnet].push_back(i);
		}
	}
	cin >> src >> dst;
	queue<long long> q;
	dist[src] = 0, prv[src] = src;
	q.push(src);
	while (q.size()) {
		long long u = q.front();
		for (auto& v : g[u]) {
			if (!dist.count(v)) {
				dist[v] = dist[u] + 1;
				prv[v] = u;
				q.push(v);
			}
		}
		q.pop();
	}
	if (dist.count(dst)) {
		cout << "Yes\n";
		vector<long long> path{ dst };
		while (prv[path.back()] != path.back()) {
			path.push_back(prv[path.back()]);
		}
		reverse(path.begin(), path.end());
		for (int i = 0; i < path.size(); i += 2) {
			cout << path[i] << " ";
		}
	}
	else {
		cout << "No";
	}
}
