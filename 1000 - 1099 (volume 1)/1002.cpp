/* 1002. Phone Numbers

Strategy:
Let N = length of the call number, M = number of words,
l_i = length of word i, L = sum of length of words

N <= 100, M <= 50'000, l_i <= 50, L <= 300'000

KMP solution:
Find for each word (M) the number of occurences: worst case N * M occurences.
For each occurence [l, r] found we store it as ok[l][r] = true; using ok[][]
we compute dp[i] = minimum number of words needed for prefix i

* Time complexity: O(N * M + L + N^2) -> KMP + dynamic programming
* Space complexity: O(N + L + N^2)

*/
#include <bits/stdc++.h>
using namespace std;

const int maxN = 100;
const int maxM = 50'000;
const int maxl = 50;
const int maxL = 300'000;

int digit[26 + 5];

int N, M;
string number;
string word[maxM + 5];
int ok[maxN + 5][maxN + 5];
int dp[maxN + 5];
int pi[maxl + maxN + 5];

void testcase() {
    N = number.size();
    number = '$' + number;
    for (int i = 1; i <= N; ++i) {
        for (int j = i; j <= N; ++j) {
            ok[i][j] = 0; 
        }
    }
    cin >> M;
    for (int k = 1; k <= M; ++k) {
        cin >> word[k];
        int m = word[k].size();
        string encoded = word[k];
        for (auto& ch : encoded) {
            ch = digit[ch - 'a'] + '0';
        }
        string concat = '$' + encoded + number;
        for (int i = 2, j = 0; i < concat.size(); ++i) {
            while (j > 0 and concat[i] != concat[j + 1]) {
                j = pi[j];
            }
            if (concat[i] == concat[j + 1]) {
                ++j;
            }
            pi[i] = j;
        }
        for (int l = 1, r = m; r <= N; ++l, ++r) {
            if (pi[r + m + 1] == m) {
                ok[l][r] = k;
            }
        }
    }
    dp[N + 1] = 0;
    for (int l = N; l >= 1; --l) {
        dp[l] = N + 1;
        for (int r = l; r <= N; ++r) {
            if (ok[l][r]) {
                dp[l] = min(dp[l], 1 + dp[r + 1]);
            }
        }
    }
    if (dp[1] > N) {
        cout << "No solution.\n";
    }
    else {
        for (int l = 1; l <= N; ++l) {
            for (int r = l; r <= N; ++r) {
                if (ok[l][r] and dp[l] == 1 + dp[r + 1]) {
                    cout << word[ok[l][r]] << " ";
                    l = r;
                    break;
                }
            }
        }
        cout << "\n";
    }
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
    map<int, string> corr { { 1, "ij" }, 
        { 2, "abc" }, 
        { 3, "def" }, 
        { 4, "gh" }, 
        { 5, "kl" }, 
        { 6, "mn" }, 
        { 7, "prs" }, 
        { 8, "tuv" }, 
        { 9, "wxy" }, 
        { 0, "oqz" }
    };
    for (auto& it : corr) {
        for (auto& ch : it.second) {
            digit[ch - 'a'] = it.first;
        }
    }
    while ((cin >> number) and number[0] != '-') {
        testcase();
    }
}