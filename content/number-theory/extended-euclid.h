/**
 * Author: Chris
 * Date: 
 * Source: 
 * Description: Finds two integers $x$ and $y$, such that $ax+by=\gcd(a,b)$.
 * If $a$ and $b$ are coprime, then $x$ is the inverse of $a \pmod{b}$.
 */
template<typename T>
T egcd(T a, T b, T &x, T &y) {
	if (!a) { x = 0, y = 1; return b; }
	T g = egcd(b % a, a, y, x);
	x -= y * (b/a); return g;
}
