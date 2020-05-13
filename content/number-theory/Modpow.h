/**
 * Author: Simon Lindholm, Chris
 * Date: 2016-09-10
 * License: CC0
 * Source: folklore
 * Description:
 * Status: tested
 */
lint modpow(lint a, lint e) {
	if (e == 0) return 1;
	lint x = modpow(a * a % mod, e >> 1);
	return e & 1 ? x * a % mod : x;
}
lint modpow(lint b, lint e) {
	lint ret = 1;
	for (int i = 1; i <= e; i *= 2, b = b * b % mod)
		if (i & e) ret = ret * b % mod;
	return ret;
}
