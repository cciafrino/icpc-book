/**
 * Author: Chris
 * Description: Chinese Remainder Theorem.
 *
 * \texttt{crt(a, m, b, n)} computes $x$ such that $x\equiv a \pmod m$, $x\equiv b \pmod n$.
 * If $|a| < m$ and $|b| < n$, $x$ will obey $0 \le x < \text{lcm}(m, n)$.
 * Assumes $mn < 2^{62}$.
 * Status: Works
 * Time: $O(\log(n)) - O(n\log(LCM(m)))$
 */

template<typename T>
T crt(T a, T m, T b, T n, T &x, T &y) { /// start-hash
	if (n > m) swap(a, b), swap(m, n);
	T g = egcd(m, n, x, y);
	assert((a - b) % g == 0); // else no solution
	x = (b - a) % n * x % n / g * m + a;
	return x < 0 ? x + m*n/g : x;
}/// end-hash
template<typename T> // Solve system up to n congruences
T crt_system(vector<T> &a, vector<T> &m, int n) {
	for (int i = 0; i < n; ++i)
		a[i] = (a[i] % m[i] + m[i]) % m[i];
	T ret = a.front(), lcm = m.front();
	for (int i = 1; i < n; ++i) {
		T x, y;
		ret = crt(ret, lcm, a[i], m[i], x, y);
		T d = egcd(lcm, m[i], x = 0, y = 0);
		lcm = lcm * m[i] / d;
	}
	return ret;
}