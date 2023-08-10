/**
 * Author: Yui Hosaka
 * Date: 2022
 * License: CC0
 * Source: http://eli.thegreenplace.net/2009/03/07/computing-modular-square-roots-in-python/
 * Description: Tonelli-Shanks algorithm for modular square roots. Finds $x$ s.t. $x^2 = a \pmod p$ ($-x$ gives the other solution).
 * Time: O(\log^2 p) worst case, O(\log p) for most $p$
 * Status: Tested for all a,p <= 10000
 */
int jacobi(int64_t a, int64_t m) { // Jacobi symbol (a/m)
	int s = 1;
	if (a < 0) a = a % m + m;
	for (; m > 1; ) {
		a %= m;
		if (a == 0) return 0;
		const int r = __builtin_ctzll(a);
		if ((r & 1) && ((m + 2) & 4)) s = -s;
		a >>= r;
		if (a & m & 2) s = -s;
		swap(a, m);
	}
	return s;
}
vector<int64_t> mod_sqrt(int64_t a, int64_t p) {
	if (p == 2) return {a & 1};
	const int j = jacobi(a, p);
	if (j == 0) return {0};
	if (j == -1) return {};
	int64_t b, d;
	while (true) {
		b = xrand() % p;
		d = (b * b - a) % p;
		if (d < 0) d += p;
		if (jacobi(d, p) == -1) break;
	}
	int64_t f0 = b, f1 = 1, g0 = 1, g1 = 0, tmp;
	for (int64_t e = (p + 1) >> 1; e; e >>= 1) {
		if (e & 1) {
			tmp = (g0 * f0 + d * ((g1 * f1) % p)) % p;
			g1 = (g0 * f1 + g1 * f0) % p;
			g0 = tmp;
		}
		tmp = (f0 * f0 + d * ((f1 * f1) % p)) % p;
		f1 = (2 * f0 * f1) % p;
		f0 = tmp;
	}
	return (g0 < p - g0) ? vector<int64_t>{g0, p - g0} : vector<int64_t>{p - g0, g0};
}
