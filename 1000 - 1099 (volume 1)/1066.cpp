/* 1066. Garland

Strategy:
After some painful calculations on paper you can figure out that:

I. For n = 2k+1, the middle element is 

H[k + 1] = (H[1] + H[n]) / 2 - k^2

II. For n = 2k, the middle elements are 

H[k] = (k * H[1] + (k - 1) * H[n]) / (n - 1) - (k - 1) * k
H[k + 1] = ((k - 1) * H[1] + k * H[n]) / (n - 1) + (k - 1) * k

For a fixed B, we can compute the heights recusively; from there on we can binary search the optimal B

Performance:
During each stage of the binary search we recurively compute the heights in O(n),
therefore the complexity is O(n * itermax) (due to the fact that the binary search
is on real numbers, instead of doing it using some epsilon value, i just repeat the
process of halving the interval for a fixed number of iterations)

* Time complexity: O(n * itermax)
* Space complexity: O(n)

*/
#include <bits/stdc++.h>
using namespace std;

const int nmax = 1e3;
const int itermax = 50;
int n;
double A;
double H[nmax + 5];

// H[l], H[r] are known, compute the unknown numbers in the range
void solve(int l, int r) {
	int len = r - l + 1;
	if (len <= 2) {
		return;
	}
	int k = len / 2, mid = (l + r) / 2;
	if (len % 2 == 1) {
		H[mid] = (H[l] + H[r]) / 2 - 1.0 * k * k;
		solve(l, mid);
		solve(mid, r);
	}
	else {
		H[mid] = (k * H[l] + (k - 1) * H[r]) / (len - 1) - (k - 1) * k;
		H[mid + 1] = ((k - 1) * H[l] + k * H[r]) / (len - 1) - (k - 1) * k;
		solve(l, mid);
		solve(mid + 1, r);
	}
}

double solveForB(double B) {
	H[1] = A, H[n] = B;
	solve(1, n);
	return *min_element(H + 1, H + n + 1);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> A;
	double l = 0, r = 1e9, bestB = 1e9;
	for (int iter = 0; iter < itermax; ++iter) {
		double mid = (l + r) / 2;
		double min_height = solveForB(mid);
		if (min_height < 0) {
			l = mid;
		}
		else {
			bestB = r = mid;
		}
	}
	cout << fixed << setprecision(6) << bestB << "\n";
}
