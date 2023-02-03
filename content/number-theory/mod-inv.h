/**
 * Author: Chris
 * Description: Find $x$ such that $ax \equiv 1$(mod $m$). The inverse
 * only exist if $a$ and $m$ are coprimes.
 */

template<typename T>
T modinv(T a) { // a^-1 (mod 2^64)
	assert(a & 1);
	T b = ((a << 1) + a) * ((a << 1) + a);
	b *= 2 - a * b;
	b *= 2 - a * b;
	b *= 2 - a * b;
	b *= 2 - a * b;
	return b;
}
template<typename T>
T modinv(T a, T m) { // a^-1 (mod m)
	assert(m > 0);
	if (m == 1) return 0;
	a %= m;
	if (a < 0) a += m;
	assert(a != 0);
	if (a == 1) return 1;
	return m - modinv(m, a) * m/a;
}
