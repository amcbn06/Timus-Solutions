/* 1114. Boxes

Strategy:
The answer for the blue and the red boxes can be calculated separately as they are independent of each other

For N boxes and X balls, in how many ways can we place them?

If we try to place exactly x boxes, there are nCr(x + N - 1, x),
therefore for <= X balls, we'll place sumf of nCr(x + N - 1, x) for 0 <= x <= X,
which apparently comes out to nCr(N + X, X + 1) * (X + 1) / N;

Fortunately we don't need long arithmetics because the answer fits in a unsigned long long

* Time complexity: O(N + A + B)

*/
#include <bits/stdc++.h>
using namespace std;


int N, A, B;

void update(map<int, int>& fact, int x, int frq) {
    for (int d = 2; d * d <= x; ++d) {
        int e = 0;
        while (x % d == 0) {
            ++e, x /= d;
        }
        if (e) {
            fact[d] += e * frq;
        }
    }
    if (x > 1) {
        fact[x] += frq;
    }
}

unsigned long long f(int N, int X) {
    map<int, int> fact;
    for (int i = N + 1; i <= N + X; ++i) {
        update(fact, i, 1);
    }
    for (int i = 1; i <= X; ++i) {
        update(fact, i, -1);
    }
    unsigned long long ans = 1;
    for (auto& it : fact) {
        while (it.second--) {
            ans *= it.first;
        }
    }
    return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
    cin >> N >> A >> B;
    cout << f(N, A) * f(N, B);
}
