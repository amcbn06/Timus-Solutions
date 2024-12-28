/* 2095. Scrum

Strategy:
We can count how many busy days there are from 1 to n:
First every second day is busy, therefore we're left with n' = n - n / 2
Then every third day is busy, therefore we're left with n'' = n' - n' / 3
In the end, x will surpass n, and those will be the quiet days

Performance:
Each time we remove a half, a third, a quarter and so on:

n -> n * 1/2 -> n * 1/2 * 2/3 = n/3 -> ...

Theoretically the time complexity is O(n), but it runs closer to O(sqrt(n))

*/
#include <bits/stdc++.h>
using namespace std;

int quiet(int n) {
	int total = n;
	for (int i = 2; total >= i; ++i) {
		total -= total / i;
	}
	return total;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int l, r;
	cin >> l >> r;
	cout << quiet(r) - quiet(l - 1);
}
