/* 1104. Don’t Ask Woman about Her Age

Strategy:
Try each base, convert the number to base then and check if it's divisible by base - 1
Because the input is large, we'll keep at each step the remainder to k - 1
Also if there's an A in the input, the base must be at least 11, so keep that in mind

Performance:
Worst case we check each base, so 36 * the size of the string

* Time complexity: O(35N)
* Space complexity: O(N)

*/
#include <bits/stdc++.h>
using namespace std;

int n;
string s;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> s;
	n = s.size();
	int min_base = 2;
	for (auto& ch : s) {
		if (isdigit(ch)) {
			min_base = max(min_base, ch - '0' + 1);
		}
		else {
			min_base = max(min_base, ch - 'A' + 11);
		}
	}
	reverse(s.begin(), s.end());
	for (int k = min_base; k <= 36; ++k) {
		int rem = 0;
		for (auto& ch : s) {
			int value = isdigit(ch) ? ch - '0' : ch - 'A' + 10;
			rem = (rem * k + value) % (k - 1);
		}
		if (rem == 0) {
			cout << k;
			return 0;
		}
	}
	cout << "No solution.";
}
