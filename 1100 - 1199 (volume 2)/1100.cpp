/* 1100. Final Standings

Strategy:
Just sort the pairs from the input

Performance:
std::stable_sort => O(NlogN)

* Time complexity: O(NlogN)
* Space complexity: O(N)

*/
#include <bits/stdc++.h>
using namespace std;

const int nmax = 1.5e5;
int n;
pair<int, int> a[nmax + 5];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i].first >> a[i].second;
	}
	stable_sort(a + 1, a + n + 1, [&](const pair<int, int>& lhs, const pair<int, int>& rhs) {
		return lhs.second > rhs.second;
		});
	for (int i = 1; i <= n; ++i) {
		cout << a[i].first << " " << a[i].second << "\n";
	}
}