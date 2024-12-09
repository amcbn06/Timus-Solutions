/* 1025. Democracy in Danger

Strategy:
We sort the groups increasingly because groups with less people need less voters
to vote "for" in order for the group to vote "for"; we take the first K / 2 + 1 groups
and from each group we take exacly the amount of people we need to make the group vote "for",
namingly for each group of a[i] we need a[i] / 2 + 1 voters from it

Performance:
Sorting => O(KlogK)

* Time complexity: O(KlogK)
* Space complexity: O(K)

*/
#include <bits/stdc++.h>
using namespace std;

const int kmax = 100;
int k;
int a[kmax + 5];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> k;
	for (int i = 1; i <= k; ++i) {
		cin >> a[i];
	}
	sort(a + 1, a + k + 1);
	int answer = 0;
	for (int i = 1; i <= k / 2 + 1; ++i) {
		answer += a[i] / 2 + 1;
	}
	cout << answer;
	sort(a + 1, a + k + 1);
}
