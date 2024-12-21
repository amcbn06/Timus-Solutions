/* 1196. History Exam

Strategy:
Just use a set to store the Professor's list

* Time complexity: O((N + M)logN)
* Space complexity: O(N)

*/
#include <bits/stdc++.h>
using namespace std;

int n, m;
set<int> s;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		int x;
		cin >> x;
		s.insert(x);
	}
	cin >> m;
	int answer = 0;
	for (int i = 1; i <= m; ++i) {
		int x;
		cin >> x;
		answer += s.count(x);
	}
	cout << answer;
}
