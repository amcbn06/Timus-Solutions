/* 2146. Quiz Show

Strategy:
For a fixed period (p that divides n) we can count the minimum number of operations
needed to actually make the string have period p.

We try each divisors of n and find the smallest one we can have as period
such that the number of changes needed is less than or equal to k.

Performance:
- N has at most sqrt(N) divisors
- during each iteration we add each character of S to a map<char,int> which
will have at most 26 items, therefore each iteration takes O(N * log(26))

* Time complexity: O(N * sqrt(N) * log(26))
* Space complexity: O(N)

*/
#include <bits/stdc++.h>
using namespace std;

int n, k;
string s;

int cost(int p) {
	vector<map<char, int>> aux(p);
	for (int i = 0; i < n; ++i) {
		aux[i % p][s[i]]++;
	}
	int answer = 0;
	for (int i = 0; i < p; ++i) {
		int frq = 0;
		for (auto& it : aux[i]) {
			frq = max(frq, it.second);
		}
		answer += n / p - frq;
	}
	return answer;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> k >> s;
	for (int i = 1; i <= n; ++i) {
		if (n % i == 0 && cost(i) <= k) {
			int period = i;
			vector<map<char, int>> aux(period);
			for (int i = 0; i < n; ++i) {
				aux[i % period][s[i]]++;
			}
			for (int i = 0; i < period; ++i) {
				char ch = aux[i].begin()->first;
				for (auto& it : aux[i]) {
					if (aux[i][ch] < it.second) {
						ch = it.first;
					}
				}
				for (int j = i; j < n; j += period) {
					s[j] = ch;
				}
			}
			cout << period << "\n" << s;
			return 0;
		}
	}
}
