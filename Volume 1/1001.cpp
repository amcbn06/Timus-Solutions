/* 1001. Reverse Root

Strategy:
Just read the numbers into an array and from last to first output it's square root

* Time complexity: O(N)
* Space complexity: O(N)

*/
#include <bits/stdc++.h>
using namespace std;

const int nmax = 2e5;
int n = 0;
long long a[nmax + 5];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	while (cin >> a[n + 1]) {
		++n;
	}
	for (int i = n; i >= 1; --i) {
		cout << fixed << setprecision(10) << sqrt(a[i]) << "\n";
	}
}
