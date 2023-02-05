/**
 * Author: Chris
 * Date: 2016-09-10
 * License: CC0
 * Source: folklore
 * Description:
 * Status: tested
 */
int64_t modpow(int64_t b, int64_t e, int64_t mod) {
	int64_t ret = 1;
	for (int i = 1; i <= e; i *= 2, b = b * b % mod)
		if (i & e) ret = ret * b % mod;
	return ret;
}
