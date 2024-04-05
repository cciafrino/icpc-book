/**
 * Author: Chris
 * Description: Find $x$ such that $ax \equiv 1$(mod $m$). The inverse
 * only exist if $a$ and $m$ are coprimes.
 */
template<typename T> T minv(T a, T m) {
	a %= m; assert(a);
	return a == 1 ? 1 : T(m - ll(minv(m, a)) * m / a);
}
