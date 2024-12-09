/* 1098. Questions

Strategy:
This problem can be solved by observing that the process that we use to find
the last caracter resembles the Josephus problem (https://en.wikipedia.org/wiki/Josephus_problem)

Therefore if we have K characters in the current string and N is the number of characters
we skip, we can come up with the following formula:

If f(K) tells us which letter will remain in the end (0-indexed),
then f(K) = (f(K - 1) + N) % K, and initially f(1) = 0

Therefore we just simply compute the index of the last character in linear time

* Time complexity: O(K)
* Space complexity: O(K)

*/
#include <bits/stdc++.h>
using namespace std;

const int N = 1999;
string line, text;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	while (getline(cin, line)) {
		text += line;
	}
	int k = text.size();
	int dead = 0;
	for (int i = 2; i <= k; ++i) {
		dead = (dead + N) % i;
	}
	if (text[dead] == '?') {
		cout << "Yes";
	}
	else if (text[dead] == ' ') {
		cout << "No";
	}
	else {
		cout << "No comments";
	}
}
