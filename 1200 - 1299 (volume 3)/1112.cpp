/* 1112. Cover

Strategy:
Remove a minimum amount of segments is equivalent to keeping a maximum number of segments
Therefore we greedily try to keep as many non-intersection segments as possible
We sort the segments increasingly based on their right end-point, and in case of equality
based on their left-endpoint. At every step if we can pick a segment we do it

Performance:
We sort the segments beforehand (O(NlogN)) and then we just iterate through them (O(N))

* Time complexity: O(NlogN)
* Space complexity: O(N)

*/
#include <bits/stdc++.h>
using namespace std;

const int nmax = 99;
int n;
pair<int, int> seg[nmax + 5];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> seg[i].first >> seg[i].second;
	}
	sort(seg + 1, seg + n + 1, [&](const pair<int, int>& lhs, const pair<int, int>& rhs) {
		return lhs.second == rhs.second ? lhs.first < rhs.first : lhs.second < rhs.second;
		});
	vector<pair<int, int>> answer;
	for (int i = 1; i <= n; ++i) {
		if (answer.empty() || seg[i].first >= answer.back().second) {
			answer.push_back(seg[i]);
		}
	}
	cout << answer.size() << "\n";
	for (auto& it : answer) {
		cout << it.first << " " << it.second << "\n";
	}
}
