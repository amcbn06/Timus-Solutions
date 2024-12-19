/* 1102. Strange Dialog

Strategy:
For each string, we compute dp[i] = true if prefix i is a valid dialogue
dp[i] = true if dp[j] is true and s[j + 1...i] is "one", "puton", "in", "out", "input" or "output"

Observations:
The time and memory limit are tight, so we have to take that into account in our implementation

*/
#include <bits/stdc++.h>
using namespace std;

const int nmax = 4e6;
int n;
string s;
bool dp[nmax + 5];

const vector<string> words{ "puton", "one", "in", "out", "input", "output" };

void testcase() {
	cin >> s;
	n = s.size();
	s = '$' + s;
	fill_n(dp + 1, n, false);
	dp[0] = true;
	for (int i = 1; i <= n; ++i) {
		for (auto& word : words) {
			if (i + word.size() - 1 <= n && s.substr(i, word.size()) == word) {
				dp[i + word.size() - 1] |= dp[i - 1];
			}
		}
	}
	cout << (dp[n] ? "YES" : "NO") << "\n";
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int tc;
	cin >> tc;
	while (tc--) {
		testcase();
	}
}
