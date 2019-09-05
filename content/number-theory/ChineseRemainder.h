/**
 * Author: Chris
 * Description: Chinese Remainder Theorem.
 *
 * \texttt{crt(a, m, b, n)} computes $x$ such that $x\equiv a \pmod m$, $x\equiv b \pmod n$.
 * If $|a| < m$ and $|b| < n$, $x$ will obey $0 \le x < \text{lcm}(m, n)$.
 * Assumes $mn < 2^{62}$.
 * Status: Works
 * Time: $\log(n)$
 */
 
template<typename T>
T crt(T a, T m, T b, T n, T &x, T &y) { /// start-hash
	if (n > m) swap(a, b), swap(m, n);
	T g = egcd(m, n, x, y);
	assert((a - b) % g == 0); // else no solution
	x = (b - a) % n * x % n / g * m + a;
	return x < 0 ? x + m*n/g : x;
}/// end-hash
