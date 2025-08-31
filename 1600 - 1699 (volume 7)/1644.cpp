/* 1644. A Whole Lot of Walnuts

Strategy:

We compute the maximum amount of walnuts that don't satisfy him (A) and the minimum number that
satisfy him (B). If A < B, we output B, otherwise we output "Inconsistent"

Performance:
Linear from the reading.

* Time complexity: O(n)
* Space complexity: O(1)

*/
#include <bits/stdc++.h>
using namespace std;

int n;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	// "It is known as a fact, that ten walnuts is always enough
	// and two walnuts are always not enough."
	int max_hungry = 2, min_satisfied = 10;
	while (n--) {
		int amount;
		string outcome;
		cin >> amount >> outcome;
		if (outcome == "hungry") {
			max_hungry = max(max_hungry, amount);
		}
		else {
			min_satisfied = min(min_satisfied, amount);
		}
	}
	if (max_hungry < min_satisfied) {
		cout << min_satisfied;
	}
	else {
		cout << "Inconsistent";
	}
}