/**
 * Author: Chris
 * Description: Find $x$ such that $ax \equiv 1$(mod $m$). The inverse
 * only exist if $a$ and $m$ are coprimes.
 */
int minv(int a, int m) {
	a %= m; assert(a);
	return a == 1 ? 1 : int(m - int64_t(minv(m, a)) * m / a);
}
