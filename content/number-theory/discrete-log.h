/**
 * Author: Bjorn Martinsson / Chrs
 * Date: 2022
 * License: CC0
 * Source: own work
 * Description:  Returns the smallest $x >= 0$ s.t. $a^x = b \pmod m$, or
 * $-1$ if no such $x$ exists. modLog(a,1,m) can be used calculate the order
 * of $a$. Assumes that $0^0 = 1$.
 * Time: $O(\sqrt m)$
 * Status: tested on yosupo and stress-tested.
 *
 * Details: This algorithm uses the baby-step giant-step method to
 * find (i,j) such that a^(n * i) = b * a^j (mod m), where n > sqrt(m)
 * and 0 < i, j <= n. If a and m are coprime then a^j has a modular
 * inverse, which means that a^(i * n - j) = b (mod m$).
 *
 * However this particular implementation of baby-step giant-step works even
 * without assuming a and m are coprime, using the following idea:
 *
 * Assume p^x is a prime divisor of m. Then we have 3 cases
 *	 1. b is divisible by p^x
 *	 2. b is divisible only by some p^y, 0<y<x
 *	 3. b is not divisible by p
 * The important thing to note is that in case 2, modLog(a,b,m) (if
 * it exists) cannot be > sqrt(m), (technically it cannot be >= log2(m)). 
 * So once all exponenents of a that are <= sqrt(m) has been checked, you
 * cannot have case 2. Case 2 is the only tricky case.
 *
 * So the modification allowing for non-coprime input invloves checking all
 * exponents of a that are <= n, and then handling the non-tricky cases by
 * a simple gcd(a^n,m) == gcd(b,m) check.
 */
#include "extended-euclid.h"
template<typename T> T modLog(T a, T b, T m) {
	T k = 1, it = 0, g;
	while ((g = gcd(a, m)) != 1) {
		if (b == k) return it;
		if (b % g) return -1;
		b /= g; m /= g; ++it; k = k * a / g % m;
	}
	T n = sqrtl(m) + 1, f = 1, j = 1;
	unordered_map<T, T> A;
	while (j <= n)
		f = f * a % m, A[f * b % m] = j++;
	for(int i = 1; i <= n; ++i) if (A.count(k = k * f % m))
		return n * i - A[k] + it;
	return -1;
}
