/* 1149. Sinus Dances

Strategy:
Just precompute	Ai for 1 <= i <= N and then build N

Performance:
Ai can be computed in O(i), and for Sn we need Ai from i = 1 to N^2,
therefore the time and space complexities will be O(N^2)

*/
#include <bits/stdc++.h>
using namespace std;

const int nmax = 200;
int n;
string A[nmax + 5];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	A[1] = "sin(1";
	for (int i = 2; i <= n; ++i) {
		A[i] = A[i - 1] + (i % 2 ? '+' : '-') + "sin(" + to_string(i);
	}
	for (int i = 1; i <= n; ++i) {
		A[i] += string(i, ')');
	}
	string S = string(n - 1, '(');
	for (int i = 1; i <= n; ++i) {
		S += A[i] + '+' + to_string(n - i + 1) + ')';
	}
	S.pop_back();
	cout << S;
}
