/**
 * Author: Chris
 * Description: Find $x$ such that $ax \equiv 1$(mod $m$). The inverse
 * only exist if $a$ and $m$ are coprimes.
 */
template<typename T>
T modinv(T a, T m) {
	assert(m > 0);
	if (m == 1) return 0;
	a %= m;
	if (a < 0) a += m;
	assert(a != 0);
	if (a == 1) return 1;
	return m - modinv(m, a) * m/a;
}
// Iff mod is prime
lint modinv(lint a) { return modpow(a % mod, mod-2); }
// const lint mod = 1000000007, LIM = 200000; ///include-line
lint* inv = new lint[LIM] - 1; inv[1] = 1;
for(int i = 2; i < LIM; ++i) inv[i] = mod - (mod/i) * inv[mod%i] % mod;