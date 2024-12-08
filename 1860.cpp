/* 1860. Fiborial
 *
 * Strategy:
 * Let's look independently at prime numbers from 2 to n;
 * If we define cnt(i, p) = how many times does p appear in the factorization of F_i,
 * and div(i, p) = how many times does p appear in the factorization of i,
 * we can see that cnt(i, p) = cnt(i - 1, p) + cnt(i - 2, p) + div(i, p)
 * This looks pretty much like the Fibonacci sequence, but each time we encounter a multiple of p,
 * we increment a few times the current element of the sequence
 *
 * Therefore what we do is we take each prime number from 2 to n and we simply calculate F_i, but
 * we jump from one multiple to another and in the end we jump to n
 * We can jump between multiples in O(1) by using Fibonacci matricies precomputed beforehand, and in
 * the end we just compute the product of cnt(i, p) for each p from 2 to n
 *
 * Performance:
 * We precompute the sieve of Eratosthenes in O(n) (theoretically nlogn but in practice it runs faster)
 * We precompute the Fibonacci matricies in O(n) (with a small constant from multiplying matricies)
 * We go through all the multiples of prime numbers, therefore we make n/2 + n/3 + n/5 + ... jumps
 * which again is theoretically O(nlogn) but it's closer to O(n) in practice
 * 
 * Observations:
 * I avoided using structs for the matrix multiplication or for the modular arithmetics
 * because they seriously slowed down the solution given the fact that are lots of function calls
 * and the modulus operator is heavily used
 * 
 * Time complexity: O(n)
 * Space complexity: O(n)
 */
#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;
const int nmax = 1e6;
int n;
bool prime[nmax + 5];
int tranz[nmax + 5][2][2];

void precompute() {
    fill_n(prime + 2, n - 1, true);
    // O(2 * N) ish
    for (int i = 2; i * i <= n; ++i) {
        if (prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                prime[j] = false;
            }
        }
    }
    // O(8 * N) ish
    tranz[0][0][0] = tranz[0][1][1] = 1;
    tranz[1][0][0] = tranz[1][0][1] = tranz[1][1][0] = 1;
    for (int w = 2; w <= n; ++w) {
        // tranz[w] = tranz[w - 1] * tranz[1]
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    tranz[w][i][j] += 1ll * tranz[w - 1][i][k] * tranz[1][k][j] % mod;
                    if (tranz[w][i][j] >= mod) {
                        tranz[w][i][j] -= mod;
                    }
                }
            }
        }
    }
}

inline void jump(int& f0, int& f1, int steps) { // O(1)
    int nf1 = (1ll * tranz[steps][0][0] * f1 + 1ll * tranz[steps][0][1] * f0) % mod;
    int nf0 = (1ll * tranz[steps][1][0] * f1 + 1ll * tranz[steps][1][1] * f0) % mod;
    f0 = nf0, f1 = nf1;
}

int main() {
    cin >> n;
    //auto start_time = chrono::high_resolution_clock::now();
    precompute();
    int answer = 1;
    for (int i = 2; i <= n; ++i) {
        if (prime[i]) {
            int f0 = 0, f1 = 1;
            int cur = i;
            while (cur + i <= n) {
                // We jump to the next multiple of i
                jump(f0, f1, i);
                cur += i;
                int x = cur;
                // We increment f1 as many time as there are occurences of i in x's factorization
                while (x % i == 0) {
                    x /= i, ++f1;
                }
                if (f1 >= mod) {
                    f1 -= mod;
                }
            }
            // We jump to n in case the last multiple is smaller than n
            if (cur < n) {
                jump(f0, f1, n - cur);
            }
            answer = 1ll * answer * (f1 + 1) % mod;
        }
    }
    cout << answer << "\n";
    //auto end_time = chrono::high_resolution_clock::now();
    //cerr << "Program took: " << chrono::duration<double>(end_time - start_time).count() << " seconds";
}
