/* 2100. Wedding Dinner

Strategy:
Just read the strings and increment the answer if "+one" appears in the end to count the number of guests;
then add 2 for Marshall and Lily; if the answer is 13 increment it by one; output the answer multiplied by 100

* Time complexity: O(N)
* Space complexity: O(N)

*/
#include <bits/stdc++.h>
using namespace std;

int n;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	int answer = n + 2;
	for (int i = 1; i <= n; ++i) {
		string str;
		cin >> str;
		if (str.size() >= 4 && str.substr(str.size() - 4) == "+one") {
			++answer;
		}
	}
	if (answer == 13) {
		++answer;
	}
	cout << answer * 100;
}
