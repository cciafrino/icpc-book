/**
 * Author: Chris
 * Date: 
 * Source: 
 * Description: Finds two integers $x$ and $y$, such that $ax+by=\gcd(a,b)$. If
 * you just need gcd, use the built in \texttt{\_\_gcd} instead.
 * If $a$ and $b$ are coprime, then $x$ is the inverse of $a \pmod{b}$.
 */
template<typename T> T gcd(T a, T b) {
	if (a < 0) a = -a; // binary gcd
	if (b < 0) b = -b;
	if (a == 0) return b;
	if (b == 0) return a;
	const int s = __builtin_ctzll(a | b);
	a >>= __builtin_ctzll(a);
	do {
		b >>= __builtin_ctzll(b);
		if (a > b) swap(a, b);
		b -= a;
	} while (b);
	return a << s;
}
template<typename T>
T egcd(T a, T b, T &x, T &y) {
    if (a == 0) {
        x = 0, y = 1;
        return b;
    }
    T p = b/a, g = egcd(b - p * a, a, y, x);
    x -= y * p;
    return g;
}
