/**
 * Author: Chris
 * Description: Find $x$ such that $ax \equiv 1$(mod $m$). The inverse
 * only exist if $a$ and $m$ are coprimes.
 */
 
int modinv(int a, int m) {
	assert(m > 0);
	if (m == 1) return 0;
	a %= m;
	if (a < 0) a += m;
	assert(a != 0);
	if (a == 1) return 1;
	return m - modinv(m, a) * m/a;
}

// Iff mod is prime
int modinv(int a) {
    return modpow(a % Mod, Mod-2);
}
