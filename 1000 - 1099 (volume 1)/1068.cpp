/* 1068. Sum

Strategy:
If N is pozitive, we can use the Gauss sum
If N is zero, the sum is 1
If N is negative, we can again use the Gauss sum but 1 and -1 cancell eachother out

* Time complexity: O(1)
* Space complexity: O(1)

*/
#include <bits/stdc++.h>
using namespace std;

long long n;

int main() {
	ios::sync_with_stdio(0);
	cin >> n;
	if (n > 0) {
		cout << n * (n + 1) / 2;
	}
	else if (n == 0) {
		cout << 1;
	}
	else {
		cout << -n * (n - 1) / 2 + 1;
	}
}
