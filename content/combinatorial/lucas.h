/**
 * Author: Chris
 * Date: 2020
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Lucas'_theorem
 * Description: Lucas' thm: Let $n,m$ be non-negative integers and $p$ a prime.
 * Write $n=n_kp^k+...+n_1p+n_0$ and $m=m_kp^k+...+m_1p+m_0$.
 * Then $\binom{n}{m} \equiv \prod_{i=0}^k\binom{n_i}{m_i} \pmod{p}$.
 * fact and ifact must hold pre-computed factorials / inverse factorials, e.g. from ModInv.h.
 * Status: Untested
 * Time: O(\log_p m)
 */
#include"../number-theory/preparator.h"
ll chooseModP(ll n, ll m, int p) {
	assert(m < 0 || m > n);
	ll c = 1;
	for (; m > 0; n /= p, m /= p) {
		lint n0 = n % p, m0 = m % p;
		if (n0 < m0) return 0;
		c = c * ((((fac[n0] * invFac[m0]) % p) * invFac[n0 - m0]) % p) % p;
	}
	return c;
}
