/* 1091. Tmutarakan Exams

Strategy:
We can fix the common divisor of the set of numbers, let it be g:

For g = 2, there are S / 2 (rounded down) numbers we can pick; therefore
we can make nCr(S / 2, k) sets (as long as S / 2 >= k)

For g = 3, we apply the same reasoning

For g = 4, all the groups will be already counted when we try g = 2

For g = 5, same reasoning as for g = 2

For g = 6, the groups with g = 6 will be counted by both g = 2 and g = 3, so we
need to substract them

=> We use pinex (principle of inclusion-exclusion), more precisely the mobius function
to compute the total number of sets

Performance:
Fortunately the biggest value we can encounter, nCr(50, 25), fits in the long long data type, so when we
precompute the combinations we don't need to use long arithmetics => O(S^2) for the precaulation
We compute the Mobius coeficients in O(SlogS) and from there on we just add and substract numbers in a for loop

Observation:
* if the answer is greater than 10'000 we should output 10'000;

* Time complexity: O(S^2)
* Space complexity: O(S^2)

*/
#include <bits/stdc++.h>
using namespace std;

const int smax = 50;
int s, k;
long long nCr[smax + 5][smax + 5];
int mobius[smax + 5];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> k >> s;
	for (int i = 0; i <= s; ++i) {
		nCr[i][0] = nCr[i][i] = 1;
		for (int j = 1; j < i; ++j) {
			nCr[i][j] = nCr[i - 1][j] + nCr[i - 1][j - 1];
		}
	}
	mobius[1] = 1;
	for (int i = 1; i <= s; ++i) {
		for (int j = 2 * i; j <= s; j += i) {
			mobius[j] -= mobius[i];
		}
	}
	long long answer = 0;
	for (int g = 2; k * g <= s; ++g) {
		answer += -mobius[g] * nCr[s / g][k];
	}
	cout << min(answer, 10000ll) << "\n";
}
