/* 1528. Sequence

Strategy:
We can compute f(i) and g(i) up to n in linear time

Performance:
Every testcase can be solved in O(n), therefore:

* Time complexity: O(n * p)
* Space complexity: O(max n)

*/
#include <bits/stdc++.h>
using namespace std;

const int nmax = 1e4;
int n, p;
long long f[nmax + 5];
long long g[nmax + 5];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	while (cin >> n >> p && !(n == 0 && p == 0)) {
		f[1] = g[1] = 1;
		for (int i = 2; i <= n; ++i) {
			f[i] = f[i - 1] * (1 + g[i - 1]) % p;
			g[i] = (g[i - 1] * (3 - g[i - 1]) % p + g[i - 2] * g[i - 2] % p + p) % p;
		}
		cout << f[n] << "\n";
	}
}
