/* 1860. Fiborial

Strategy:
Let's look at the first numbers of the sequence:
F_0 = 1
F_1 = 1
F_2 = 2^1
F_3 = 3^1 * 2^1
F_4 = 4^1 * 3^1 * 2^2
F_5 = 5^1 * 4^1 * 3^2 * 2^3
F_6 = 6^1 * 5^1 * 4^2 * 3^3 * 2^5

As we can see, F_i can be decomposed into the product of i^f_0 * (i - 1)^f_1 * (i - 2)^f_2 * ...
Therefore for each prime number from 2 to n we can look through it's multiples and we compute the
sum of the their exponents in F_i

Performance:
We precompute the sieve of Eratosthenes in O(n) (theoretically nlogn but in practice it runs faster)
We precompute the Fibonacci sequence in O(n) as well
We go through all the multiples of prime numbers, and for each multiple we find the the exponent
Let S_p = n/p + n/p^2 + n/p^3 + n/p^4 + ...
=> p * S_p = n + n/p + n/p^2 + n/p^3 + ...
=> (p - 1) * S_p = n => S_p = n / (p - 1) = approx. n / p
Therefore we make S_2 + S_3 + S_5 + S_7 + ... which
again is theoretically O(nlogn) but it's closer to O(n) in practice

* Time complexity: O(n)
* Space complexity: O(n)

*/

#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;
const int nmax = 1e6;
int n;
bool prime[nmax + 5];
int fibo[nmax + 5];

void precompute() {
    fill_n(prime + 2, n - 1, true);
    // Precomputing the sieve of Eratosthenes
    for (int i = 2; i * i <= n; ++i) {
        if (prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                prime[j] = false;
            }
        }
    }
    // Precomputing the fibonacci sequence
    fibo[0] = fibo[1] = 1;
    for (int i = 2; i <= n; ++i) {
        fibo[i] = fibo[i - 1] + fibo[i - 2];
        if (fibo[i] >= mod) {
            fibo[i] -= mod;
        }
    }
}

int main() {
    cin >> n;
    precompute();
    int answer = 1;
    for (int i = 2; i <= n; ++i) {
        if (prime[i]) {
            int exponent = 0;
            for (int j = i; j <= n; j += i) {
                int x = j;
                // We add to the exponent of i the coefficient of j for each appearance of i in j's factorization
                while (x % i == 0) {
                    x /= i, exponent += fibo[n - j];
                    if (exponent >= mod) {
                        exponent -= mod;
                    }
                }
            }
            answer = 1ll * answer * (exponent + 1) % mod;
        }
    }
    cout << answer << "\n";
}
