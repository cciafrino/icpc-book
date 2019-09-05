/**
 * Author: Lukas Polacek
 * Date: 2010-01-26
 * License: CC0
 * Source: TopCoder tutorial
 * Description: Calculate $a\cdot b\bmod c$ (or $a^b \bmod c$) for large $c$.
 * Time: O(64/bits \cdot \log b), where $bits = 64-k$, if we want to deal with
 * $k$-bit numbers.
 */
#pragma once

typedef unsigned long long ull;

const int bits = 10;
// if all numbers are less than 2^k, set bits = 64-k
const ull po = 1 << bits;
ull mod_mul(ull a, ull b, ull &c) { /// start-hash
	ull x = a * (b & (po - 1)) % c;
	while ((b >>= bits) > 0) {
		a = (a << bits) % c;
		x += (a * (b & (po - 1))) % c;
	}
	return x % c;
} /// end-hash
ull mod_pow(ull a, ull b, ull Mod) { /// start-hash
	if (b == 0) return 1;
	ull res = mod_pow(a, b / 2, Mod);
	res = mod_mul(res, res, Mod);
	if (b & 1) return mod_mul(res, a, Mod);
	return res;
}/// end-hash
// Other option
typedef long double ld;
ull mod_mul(ull a, ull b, ull m) {/// start-hash
	ull q = (ld) a * (ld) b / (ld) m;
	ull r = a * b - q * m;
	return (r + m) % m;
}/// end-hash
ull mod_pow(ull x, ull e, ull m) { /// start-hash
	ull ans = 1;
	x = x % m;
	for(; e; e >>= 1) {
		if(e & 1) {
			ans = mod_mul(ans, x, m);
		}
		x = mod_mul(x, x, m);
	}
	return ans;
}/// end-hash
