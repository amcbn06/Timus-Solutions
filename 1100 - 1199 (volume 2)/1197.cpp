/* 1197. Lonesome Knight

Strategy:
For each knight we go through the 8 types of jumps and check if the positions are valid

Performance:
O(1) for a knight, O(N) total

* Time complexity: O(N)
* Space complexity: O(1)

*/
#include <bits/stdc++.h>
using namespace std;

const int dx[8]{ -2, -1, 1, 2, 2, 1, -1, -2 };
const int dy[8]{ 1, 2, 2, 1, -1, -2, -2, -1 };
int n;

bool ok(int i, int j) {
	return 1 <= i && i <= 8 && 1 <= j && j <= 8;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	while (n--) {
		char ch;
		int j;
		cin >> ch >> j;
		int i = ch - 'a' + 1;
		int neighbours = 0;
		for (int k = 0; k < 8; ++k) {
			neighbours += ok(i + dx[k], j + dy[k]);
		}
		cout << neighbours << "\n";
	}
}