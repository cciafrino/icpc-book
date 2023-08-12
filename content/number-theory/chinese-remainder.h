/**
 * Author: Chris
 * Description: Chinese Remainder Theorem.
 * \texttt{crt(a, m, b, n)} computes $x$ such that $x\equiv a \pmod m$, $x\equiv b \pmod n$.
 * If $|a| < m$ and $|b| < n$, $x$ will obey $0 \le x < \text{lcm}(m, n)$.
 * Assumes $mn < 2^{62}$.
 * Status: tested on kattis
 * Time: $O(\log(LCM(m)))$
 */
#include "extended-euclid.h"
pair<ll, ll> crt(ll a, ll m, ll b, ll n) {
	if (n > m) swap(a, b), swap(m, n);
	ll x, y, g = egcd(m, n, x, y);
	if ((a - b) % g != 0) return {0, -1};
	x = (b - a) % n * x % n / g * m + a;
	return {x + (x < 0 ? m*n/g : 0), m*n/g};
}
