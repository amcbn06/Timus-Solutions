/* 1613. For Fans of Statistics

Strategy:
We can traverse the elements from left to right. For each element we store the rightmost position
where it appears in a hashmap. Everytime we reach an index `r` such that there are queries ending
at that index, we answer them by checking if the rightmost position where `x` apears is greater 
than `l`.

Performance:
Due to the hashmap the algorithm runs in O(nlogn) / O(n) (depends if map or unordered_map is used).
Regarding the queries we can sort them by `r` in order to process them in the right order or
we can have an array for each index in which we store all the queries that end in that index.

* Time complexity: O(nlogn + q)
* Space complexity: O(n + q)

*/
#include <bits/stdc++.h>
using namespace std;

const int nmax = 7e5;
int n, q;
int a[nmax + 1];
struct Query {
	int l, x, index;
};
vector<Query> queries[nmax + 1];
bool answer[nmax + 1];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	cin >> q;
	for (int i = 1; i <= q; ++i) {
		Query query;
		int r;
		cin >> query.l >> r >> query.x;
		query.index = i;
		queries[r].push_back(query);
	}
	map<int, int> latest;
	for (int i = 1; i <= n; ++i) {
		latest[a[i]] = i;
		for (auto& query : queries[i]) {
			if (latest.count(query.x) and latest[query.x] >= query.l) {
				answer[query.index] = true;
			}
		}
	}
	for (int i = 1; i <= q; ++i) {
		cout << answer[i];
	}
}