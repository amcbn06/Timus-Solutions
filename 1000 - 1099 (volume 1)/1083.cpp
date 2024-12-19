/* 1083. Factorials!!!

Strategy:
We just compute the value just as presented in the definition

* Time complexity: O(n)
* Space complexity: O(1)

*/
#include <bits/stdc++.h>
using namespace std;

int n;
string str;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> str;
	int k = str.size();
	long long answer = 1;
	while (n > 0) {
		answer *= n;
		n -= k;
	}
	cout << answer;
}
