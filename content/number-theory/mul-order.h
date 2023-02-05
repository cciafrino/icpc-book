/**
 * Author: Chris
 * Description: Find the smallest integer $k$ such that $a^k$
 * (mod $m$) $= 1$. $0 < k < m$.
 * Time: $O(log(N))$
 * Status: stress-tested 
 */
#include "prime-factors.h"
#include "mod-pow.h"
template<typename T> T mul_order(T a, T m) {
    if (__gcd(a, m) != 1) return 0;
    auto N = phi(m);
    auto primes = prime_factorize(N);
    T res = 1;
    for (auto &[p, e] : primes) {
		while (N % p == 0 && modpow(a, N/p, m) == 1) {
			N /= p;
		} 
    }
    return N;
}
