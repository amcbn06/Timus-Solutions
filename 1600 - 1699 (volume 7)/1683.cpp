/* 1683. Fridge

Strategy:

We just keep halving the strip: n becomes ceil(n / 2)

* Time complexity: O(log(N))
* Space complexity: O(1)

*/
#include <bits/stdc++.h>
using namespace std;

int n;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	vector<int> folds;
	while (n > 1){
		folds.push_back(n / 2);
		n = (n + 1) / 2;
	}
	cout << folds.size() << "\n";
	for (auto& x : folds) {
		cout << x << " ";
	}
}