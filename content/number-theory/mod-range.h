/**
 * Author: Yui
 * Date: 
 * Source: 
 * Description: min $x \geq 0$ s.t. $l \leq ((a x) \mod m) \leq r$, $m > 0$, $a \geq 0$.
 */
template<typename T> T mod_range(T m, T a, T l, T r) {
	l = max(l, T(0));
	r = min(r, m - 1);
	if (l > r) return -1;
	a %= m;
	if (a == 0) return (l > 0) ? -1 : 0;
	const T k = (l + a - 1) / a;
	if (a * k <= r) return k;
	const T y = mod_range(a, m, a * k - r, a * k - l);
	return (y == -1) ? -1 : ((m * y + r) / a);
}
