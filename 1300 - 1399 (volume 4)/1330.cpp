/* 1330. Intervals

Strategy:

Partial sums.

Performance:

Linear.

* Time complexity: O(N)
* Space complexity: O(N)

*/
#include <bits/stdc++.h>
using namespace std;

const int nmax = 1e4;
int	N, Q;
int a[nmax + 1];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	for (int i = 1; i <= N; ++i) {
		cin >> a[i];
		a[i] += a[i - 1];
	}
	cin >> Q;
	while (Q--) {
		int l, r;
		cin >> l >> r;
		cout << a[r] - a[l - 1] << "\n";
	}
}